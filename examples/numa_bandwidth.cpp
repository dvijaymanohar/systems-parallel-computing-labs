// Build (Linux): g++ -O3 -std=c++20 -pthread examples/numa_bandwidth.cpp -lnuma -o numa_bandwidth
#include <numa.h>
#include <sched.h>
#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>
static void pin_cpu(int cpu){cpu_set_t set;CPU_ZERO(&set);CPU_SET(cpu,&set);if(sched_setaffinity(0,sizeof(set),&set)!=0)perror("sched_setaffinity");}
int main(int argc,char**argv){
    if(numa_available()<0){std::cerr<<"NUMA unavailable\n";return 77;}
    int alloc_node=argc>1?std::stoi(argv[1]):0;
    int cpu=argc>2?std::stoi(argv[2]):0;
    std::size_t bytes=argc>3?std::stoull(argv[3]):512ull*1024*1024;
    auto*p=(char*)numa_alloc_onnode(bytes,alloc_node);if(!p)return 2;
    std::memset(p,1,bytes);pin_cpu(cpu);
    volatile std::uint64_t sum=0;auto t0=std::chrono::steady_clock::now();
    for(std::size_t i=0;i<bytes;i+=64)sum+=p[i];
    auto sec=std::chrono::duration<double>(std::chrono::steady_clock::now()-t0).count();
    std::cout<<"alloc_node="<<alloc_node<<" cpu="<<cpu<<" seconds="<<sec
             <<" touched_GBps="<<(bytes/1e9/sec)<<" checksum="<<sum<<"\n";
    numa_free(p,bytes);
}
