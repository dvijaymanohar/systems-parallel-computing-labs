// Build: g++ -O2 -std=c++20 -pthread examples/race_vs_mutex_atomic.cpp -o race_vs_mutex_atomic
#include <atomic>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

template<class F> double timed(F&& f){
    auto a=std::chrono::steady_clock::now(); f();
    return std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-a).count();
}
int main(int argc,char**argv){
    int threads=argc>1?std::stoi(argv[1]):8;
    std::uint64_t iters=argc>2?std::stoull(argv[2]):1'000'000;
    std::uint64_t expected=std::uint64_t(threads)*iters;

    std::uint64_t racy=0;
    double race_ms=timed([&]{std::vector<std::thread>w; for(int t=0;t<threads;++t)w.emplace_back([&]{for(std::uint64_t i=0;i<iters;++i)++racy;}); for(auto&x:w)x.join();});

    std::uint64_t guarded=0; std::mutex m;
    double mutex_ms=timed([&]{std::vector<std::thread>w; for(int t=0;t<threads;++t)w.emplace_back([&]{for(std::uint64_t i=0;i<iters;++i){std::lock_guard<std::mutex>g(m);++guarded;}}); for(auto&x:w)x.join();});

    std::atomic<std::uint64_t> atomic{0};
    double atomic_ms=timed([&]{std::vector<std::thread>w; for(int t=0;t<threads;++t)w.emplace_back([&]{for(std::uint64_t i=0;i<iters;++i)atomic.fetch_add(1,std::memory_order_relaxed);}); for(auto&x:w)x.join();});

    std::cout<<"expected="<<expected<<"\n"
             <<"race="<<racy<<" ms="<<race_ms<<" (undefined behavior; demonstration only)\n"
             <<"mutex="<<guarded<<" ms="<<mutex_ms<<"\n"
             <<"atomic="<<atomic.load()<<" ms="<<atomic_ms<<"\n";
    return (guarded==expected && atomic==expected)?0:2;
}
