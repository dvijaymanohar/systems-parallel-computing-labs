#!/usr/bin/env python3
import csv, statistics, subprocess, sys, time

binary = sys.argv[1] if len(sys.argv) > 1 else "./build/systems_lab"
n = int(sys.argv[2]) if len(sys.argv) > 2 else 20_000_000
thread_counts = [1,2,4,8]
rows=[]
for threads in thread_counts:
    samples=[]
    for _ in range(7):
        t0=time.perf_counter()
        subprocess.run([binary,"sum",str(n),str(threads)],check=True,capture_output=True,text=True)
        samples.append((time.perf_counter()-t0)*1000)
    rows.append((threads,statistics.median(samples),min(samples),max(samples)))
print("threads,median_ms,min_ms,max_ms")
for r in rows: print(",".join(map(str,r)))
