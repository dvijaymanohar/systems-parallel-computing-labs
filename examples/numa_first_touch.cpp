// Linux/libnuma extension.
// Build: g++ -O3 -std=c++20 examples/numa_first_touch.cpp -lnuma -o numa_first_touch
#include <numa.h>
#include <iostream>
#include <thread>
#include <vector>

int main() {
    if (numa_available() < 0) {
        std::cerr << "NUMA unavailable on this machine\n";
        return 77;
    }
    std::cout << "max_node=" << numa_max_node() << " configured_cpus=" << numa_num_configured_cpus() << "\n";
    std::cout << "Experiment: allocate/touch on one node, then bind compute to same vs remote node. "
                 "Record bandwidth/latency and perf counters.\n";
    return 0;
}
