// Build: g++ -O3 -std=c++20 examples/pointer_chase_latency.cpp -o pointer_chase_latency
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
int main(int argc,char**argv){
    std::size_t n=argc>1?std::stoull(argv[1]):(1ull<<24);
    std::vector<std::uint32_t> order(n);std::iota(order.begin(),order.end(),0);
    std::mt19937 g(1);std::shuffle(order.begin(),order.end(),g);
    std::vector<std::uint32_t> next(n);
    for(std::size_t i=0;i<n;++i)next[order[i]]=order[(i+1)%n];
    std::uint32_t p=0;auto t0=std::chrono::steady_clock::now();
    for(std::size_t i=0;i<n;++i)p=next[p];
    auto ns=std::chrono::duration<double,std::nano>(std::chrono::steady_clock::now()-t0).count()/n;
    std::cout<<"elements="<<n<<" ns_per_dependent_load="<<ns<<" final="<<p<<"\n";
    std::cout<<"Compare with streaming bandwidth: pointer chasing exposes latency because dependencies limit memory-level parallelism.\n";
}
