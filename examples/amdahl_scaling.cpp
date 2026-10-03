// Build: g++ -O3 -std=c++20 -pthread examples/amdahl_scaling.cpp -o amdahl_scaling
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

static double work(std::uint64_t begin,std::uint64_t end){
    double s=0;
    for(auto i=begin;i<end;++i) s += std::sin(double(i)*1e-6)*std::cos(double(i)*1e-7);
    return s;
}
int main(int argc,char**argv){
    std::uint64_t n=argc>1?std::strtoull(argv[1],nullptr,10):20'000'000;
    unsigned threads=argc>2?std::stoul(argv[2]):4;
    double serial_fraction=argc>3?std::stod(argv[3]):0.10;
    std::uint64_t serial_n=std::uint64_t(n*serial_fraction), parallel_n=n-serial_n;
    auto t0=std::chrono::steady_clock::now();
    volatile double serial=work(0,serial_n);
    std::vector<double> partial(threads);
    std::vector<std::thread> ws;
    auto chunk=(parallel_n+threads-1)/threads;
    for(unsigned t=0;t<threads;++t){
        auto b=serial_n+t*chunk, e=std::min(n,b+chunk);
        ws.emplace_back([&,t,b,e]{partial[t]=work(b,e);});
    }
    for(auto& w:ws)w.join();
    double total=serial; for(double x:partial) total+=x;
    auto ms=std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-t0).count();
    double ideal_speedup=1.0/(serial_fraction+(1.0-serial_fraction)/threads);
    std::cout<<"threads="<<threads<<" serial_fraction="<<serial_fraction
             <<" amdahl_ideal_speedup="<<ideal_speedup<<" elapsed_ms="<<ms
             <<" checksum="<<total<<"\n";
}
