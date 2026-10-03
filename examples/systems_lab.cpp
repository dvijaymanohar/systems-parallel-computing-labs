#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <thread>
#include <vector>

using Clock = std::chrono::steady_clock;

static std::uint64_t serial_sum(std::uint64_t n) {
    std::uint64_t s = 0;
    for (std::uint64_t i = 1; i <= n; ++i) s += i;
    return s;
}

static std::uint64_t parallel_sum(std::uint64_t n, unsigned threads) {
    std::vector<std::uint64_t> partial(threads, 0);
    std::vector<std::thread> workers;
    const std::uint64_t chunk = (n + threads - 1) / threads;
    for (unsigned t = 0; t < threads; ++t) {
        const auto begin = t * chunk + 1;
        const auto end = std::min<std::uint64_t>(n + 1, begin + chunk);
        workers.emplace_back([&, t, begin, end] {
            std::uint64_t s = 0;
            for (auto i = begin; i < end; ++i) s += i;
            partial[t] = s;
        });
    }
    for (auto& w : workers) w.join();
    return std::accumulate(partial.begin(), partial.end(), std::uint64_t{0});
}

static int run_sum(std::uint64_t n, unsigned threads) {
    const auto expected = n * (n + 1) / 2;
    const auto t0 = Clock::now();
    const auto got = threads == 1 ? serial_sum(n) : parallel_sum(n, threads);
    const auto t1 = Clock::now();
    const double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
    std::cout << "sum=" << got << " expected=" << expected
              << " threads=" << threads << " ms=" << std::fixed << std::setprecision(3) << ms << "\n";
    return got == expected ? 0 : 2;
}

static int run_counter(unsigned threads, std::uint64_t iters) {
    std::atomic<std::uint64_t> counter{0};
    std::vector<std::thread> workers;
    const auto t0 = Clock::now();
    for (unsigned t = 0; t < threads; ++t)
        workers.emplace_back([&]{ for (std::uint64_t i=0;i<iters;++i) counter.fetch_add(1, std::memory_order_relaxed); });
    for (auto& w: workers) w.join();
    const auto t1 = Clock::now();
    const auto expected = std::uint64_t(threads) * iters;
    std::cout << "counter=" << counter.load() << " expected=" << expected
              << " ms=" << std::chrono::duration<double,std::milli>(t1-t0).count() << "\n";
    return counter == expected ? 0 : 2;
}

struct alignas(64) PaddedCounter { std::uint64_t value = 0; };

static int run_false_sharing(unsigned threads, std::uint64_t iters) {
    std::vector<std::uint64_t> packed(threads, 0);
    std::vector<PaddedCounter> padded(threads);
    auto measure = [&](auto&& body) {
        const auto t0=Clock::now(); body(); const auto t1=Clock::now();
        return std::chrono::duration<double,std::milli>(t1-t0).count();
    };
    const double packed_ms = measure([&]{
        std::vector<std::thread> ws;
        for(unsigned t=0;t<threads;++t) ws.emplace_back([&,t]{ for(std::uint64_t i=0;i<iters;++i) ++packed[t]; });
        for(auto& w:ws) w.join();
    });
    const double padded_ms = measure([&]{
        std::vector<std::thread> ws;
        for(unsigned t=0;t<threads;++t) ws.emplace_back([&,t]{ for(std::uint64_t i=0;i<iters;++i) ++padded[t].value; });
        for(auto& w:ws) w.join();
    });
    std::cout << "packed_ms=" << packed_ms << " padded_ms=" << padded_ms
              << " (interpret only after repeated runs and profiling)\n";
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "usage: systems_lab {sum|counter|false-sharing} ...\n";
        return 1;
    }
    const std::string mode=argv[1];
    if(mode=="sum" && argc==4) return run_sum(std::strtoull(argv[2],nullptr,10), std::stoul(argv[3]));
    if(mode=="counter" && argc==4) return run_counter(std::stoul(argv[2]), std::strtoull(argv[3],nullptr,10));
    if(mode=="false-sharing" && argc==4) return run_false_sharing(std::stoul(argv[2]), std::strtoull(argv[3],nullptr,10));
    std::cerr << "invalid arguments\n";
    return 1;
}
