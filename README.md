# systems-parallel-computing-labs

Build systems foundations for performance engineering: parallel decomposition, synchronization, locality, false sharing, affinity, and NUMA.

This repository follows a **learn-by-example** progression:

> concept → runnable example → correctness → measurement → profiling → diagnosis → optimization → validation → project

## Basics coverage
Performance fundamentals; CPU & memory; Amdahl's Law; concurrency; synchronization; cache locality; NUMA; evidence-driven diagnosis.

## Learning order
1. CPU serial vs parallel sum
2. Amdahl scaling
3. race condition
4. mutex vs atomic
5. false sharing
6. NUMA first-touch
7. CPU affinity/locality

## Repository layout
- `fundamentals/` — concise mechanism notes and tiny demonstrations
- `examples/` — runnable examples in learning order
- `tests/` — deterministic and randomized correctness checks
- `benchmarks/` — repeatable measurement harnesses
- `profiling/` — profiler commands and evidence instructions
- `optimizations/` — baseline → hypothesis → change → re-measure studies
- `exercises/` — beginner through challenge tasks
- `mini-projects/` — integrated practice
- `advanced-projects/` — portfolio-grade work
- `docs/` — deeper explanations and decision records
- `scripts/` — setup/environment helpers
- `references/` — primary-source references

## Working rules
1. Establish correctness before performance work.
2. Define the measurement boundary.
3. Warm up before steady-state measurements.
4. Repeat measurements and report median plus spread.
5. Profile before optimizing.
6. Change one major variable at a time.
7. Re-run correctness checks after every optimization.
8. Never commit invented benchmark numbers; record actual environment metadata.

## Environment
```bash
bash scripts/check_environment.sh
```

GPU examples require compatible NVIDIA hardware/software. Hardware-dependent work is explicitly marked rather than simulated.

## Completion standard
A topic is complete only when you can explain the mechanism, run/build the example, validate correctness, measure it correctly, interpret relevant profiler evidence, and explain the trade-offs.
