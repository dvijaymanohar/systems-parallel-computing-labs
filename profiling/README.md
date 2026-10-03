# Profiling

Useful Linux tools: `perf stat`, `perf record`, flame graphs, `numactl`, `taskset`, and hardware PMU counters.

Start broad:
```bash
perf stat -e cycles,instructions,cache-misses,context-switches ./build/systems_lab sum 50000000 8
```

Do not infer the bottleneck from wall-clock time alone. Compare scaling efficiency, CPU utilization, cache misses, scheduler activity, and memory bandwidth where available.
