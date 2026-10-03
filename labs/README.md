# Hands-on labs

Build individual examples directly:

```bash
g++ -O3 -std=c++20 -pthread examples/amdahl_scaling.cpp -o amdahl_scaling
./amdahl_scaling 20000000 8 0.10

g++ -O2 -std=c++20 -pthread examples/race_vs_mutex_atomic.cpp -o race_vs_mutex_atomic
./race_vs_mutex_atomic 8 1000000

g++ -O3 -std=c++20 examples/locality_stride.cpp -o locality_stride
./locality_stride

g++ -O2 -std=c++20 -pthread mini-projects/bounded_queue.cpp -o bounded_queue
./bounded_queue
```

For every run, predict the result first. Then collect timings repeatedly and explain the mechanism—not just which number is smaller.
