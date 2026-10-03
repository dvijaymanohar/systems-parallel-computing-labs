#!/usr/bin/env bash
set -euo pipefail
echo "== OS =="; uname -a || true
echo "== CPU =="; lscpu 2>/dev/null | sed -n '1,20p' || true
echo "== Compiler =="; (g++ --version || clang++ --version) 2>/dev/null | head -n 2 || true
echo "== Python =="; python3 --version 2>/dev/null || true
echo "== NVIDIA GPU =="; nvidia-smi --query-gpu=name,driver_version,memory.total --format=csv 2>/dev/null || echo "nvidia-smi unavailable"
echo "== CUDA compiler =="; nvcc --version 2>/dev/null | tail -n 4 || echo "nvcc unavailable"
