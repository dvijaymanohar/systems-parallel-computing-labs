// Build: g++ -O3 -std=c++20 examples/locality_stride.cpp -o locality_stride
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

int main(int argc,char**argv){
    std::size_t n=argc>1?std::strtoull(argv[1],nullptr,10):(1ull<<26);
    std::vector<std::uint64_t>a(n,1);
    for(std::size_t stride: {1,2,4,8,16,32,64,128,256}){
        volatile std::uint64_t sum=0;
        auto t0=std::chrono::steady_clock::now();
        for(std::size_t i=0;i<n;i+=stride) sum += a[i];
        auto ms=std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-t0).count();
        auto bytes=(n+stride-1)/stride*sizeof(std::uint64_t);
        std::cout<<"stride="<<stride<<" accesses="<<(n+stride-1)/stride
                 <<" ms="<<ms<<" requested_GBps="<<(bytes/1e6/ms)<<" checksum="<<sum<<"\n";
    }
}
