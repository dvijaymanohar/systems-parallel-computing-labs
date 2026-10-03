# Advanced project: topology-aware preprocessing pipeline

Create a CPU preprocessing pipeline intended to feed one or more accelerators.

Required evidence:
- throughput vs thread count
- p50/p95 stage latency
- local vs remote NUMA placement
- scheduler-default vs pinned affinity
- false-sharing fix
- bounded queue/backpressure behavior
- a discussion of how host starvation would reduce GPU utilization
