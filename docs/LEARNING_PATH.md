# Learning path

The repository specification is implemented as a sequence of controlled experiments.

## Progression

- [ ] 01 — CPU serial vs parallel sum
- [ ] 02 — Amdahl scaling
- [ ] 03 — race condition
- [ ] 04 — mutex vs atomic
- [ ] 05 — false sharing
- [ ] 06 — NUMA first-touch
- [ ] 07 — CPU affinity/locality

## Evidence template

For every performance experiment, record:

- objective
- hypothesis
- workload and input shape
- independent variable
- controlled variables
- hardware/software environment
- correctness criterion
- timing methodology
- median and spread
- profiler evidence
- interpretation
- trade-off
- next experiment

Do not optimize a workload until the baseline is correct and the bottleneck hypothesis is supported by evidence.
