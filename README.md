# Systems & Parallel Computing Labs

Hands-on systems performance labs for concurrency, scaling, synchronization, cache locality, false sharing, CPU affinity, and NUMA.

## Learn by example

`concept → runnable example → correctness → benchmark → profile → diagnose → optimize → validate`

### Practical sequence
1. Serial vs parallel sum
2. Amdahl's Law scaling
3. Intentional race condition
4. Mutex vs atomic counter
5. False sharing vs padded counters
6. NUMA first-touch
7. CPU affinity and locality

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/systems_lab sum 50000000 1
./build/systems_lab sum 50000000 8
./build/systems_lab counter 8 1000000
./build/systems_lab false-sharing 8 10000000
```

Run correctness smoke tests with `ctest --test-dir build --output-on-failure`.

NUMA-specific work is in `examples/numa_first_touch.cpp` and requires Linux/libnuma. See `docs/performance-cpu-memory-foundations.md`.

## Evidence rules

Record CPU model, core/thread topology, compiler/version, build flags, input size, thread count, warm-up policy, repetitions, median/spread, and profiler evidence. Do not commit invented performance numbers.
