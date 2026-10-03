# Performance, CPU, and memory foundations

## Concepts to be able to explain
- latency vs throughput
- bandwidth vs latency
- utilization vs useful work
- bottleneck and critical path
- compute-bound vs memory-bound behavior
- Amdahl's Law
- cache locality and false sharing
- memory latency vs sustainable bandwidth
- virtual-memory effects such as page faults and TLB pressure
- concurrency vs parallelism
- synchronization overhead
- oversubscription and task granularity
- NUMA first-touch and local vs remote memory

## Required experiments
1. Serial vs threaded sum with a thread-count sweep.
2. Controlled Amdahl experiment: introduce a serial fraction and compare measured scaling with the model.
3. Locality experiment: sequential vs strided/random access.
4. False-sharing experiment: packed vs cache-line-padded per-thread state.
5. NUMA first-touch experiment on a multi-node host.
6. Affinity experiment: scheduler-default vs pinned workers.
7. Latency-oriented pointer chasing vs bandwidth-oriented streaming.

For every experiment, preserve correctness and record hardware, compiler flags, repetitions, median/spread, and profiler/counter evidence.
