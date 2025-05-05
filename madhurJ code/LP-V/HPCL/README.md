# High Performance Computing Laboratory

This repository contains implementations of parallel computing algorithms using OpenMP, Python's multiprocessing, and CUDA. Each implementation demonstrates the performance benefits of parallel processing compared to sequential execution.

## Programs List and Instructions

### 1. Parallel Graph Search (BFS and DFS)

**Files**: 
- [`HPCL_Exp_01.cpp`](HPCL_Exp_01.cpp) (OpenMP implementation)
- [`HPCL_Exp_01.py`](HPCL_Exp_01.py) (Python multiprocessing implementation)

**Algorithms**:
- Breadth-First Search (BFS): Level-wise traversal of graph
- Depth-First Search (DFS): Branch-wise traversal of graph

**Parallelization Strategy**:
- BFS: Process nodes at each level in parallel
- DFS: Process independent branches in parallel
- Uses OpenMP parallel for and critical sections in C++
- Uses multiprocessing Pool in Python

**Compilation and Execution**:
```bash
# C++ version
g++ -fopenmp HPCL_Exp_01.cpp -o parallel_graph_search
./parallel_graph_search

# Python version
python HPCL_Exp_01.py
```

### 2. Parallel Sorting Algorithms

**Files**:
- [`HPCL_Exp_02.cpp`](HPCL_Exp_02.cpp) (OpenMP implementation)
- [`HPCL_Exp_02.py`](HPCL_Exp_02.py) (Python multiprocessing implementation)

**Algorithms**:
- Bubble Sort: O(n²) comparison-based sorting
- Merge Sort: O(n log n) divide-and-conquer sorting

**Parallelization Strategy**:
- Bubble Sort: Parallel comparison and swapping of adjacent elements
- Merge Sort: Parallel division and sorting of subarrays
- Performance improvement most noticeable for large arrays

**Compilation and Execution**:
```bash
# C++ version
g++ -fopenmp HPCL_Exp_02.cpp -o parallel_sorting
./parallel_sorting

# Python version
python HPCL_Exp_02.py
```

### 3. Parallel Reduction Operations

**Files**:
- [`HPCL_Exp_03.cpp`](HPCL_Exp_03.cpp) (OpenMP implementation)
- [`HPCL_Exp_03.py`](HPCL_Exp_03.py) (Python multiprocessing implementation)

**Operations**:
- Minimum value finding
- Maximum value finding
- Sum calculation
- Average calculation

**Parallelization Strategy**:
- Data divided into chunks processed in parallel
- Uses OpenMP reduction clauses in C++
- Uses multiprocessing Pool in Python
- Near-linear speedup with number of cores

**Compilation and Execution**:
```bash
# C++ version
g++ -fopenmp HPCL_Exp_03.cpp -o parallel_reduction
./parallel_reduction

# Python version
python HPCL_Exp_03.py
```

### 4. CUDA Programs

#### Vector Addition

**File**: [`HPCL_Exp_04_vector_addition.cu`](HPCL_Exp_04_vector_addition.cu)

**Features**:
- Element-wise addition of two vectors
- Coalesced memory access pattern
- Block size optimization for GPU architecture
- Handles large vectors efficiently

**Compilation and Execution**:
```bash
nvcc HPCL_Exp_04_vector_addition.cu -o vector_addition
./vector_addition
```

#### Matrix Multiplication

**File**: [`HPCL_Exp_04_matrix_multiplication.cu`](HPCL_Exp_04_matrix_multiplication.cu)

**Features**:
- Dense matrix multiplication
- Optimized thread block size (32x32)
- Efficient memory access patterns
- Handles large matrices (default 1024x1024)

**Compilation and Execution**:
```bash
nvcc HPCL_Exp_04_matrix_multiplication.cu -o matrix_multiplication
./matrix_multiplication
```

## Requirements

### 1. For C++ Programs:
- GCC compiler 7.0 or later with OpenMP support
- C++11 or later
- OpenMP 4.5 or later
- Compilation flag: `-fopenmp`

### 2. For Python Programs:
- Python 3.6 or later
- NumPy 1.19 or later
- multiprocessing module (built into Python)
- Install dependencies:
  ```bash
  pip install numpy
  ```

### 3. For CUDA Programs:
- NVIDIA CUDA Toolkit 10.0 or later
- NVIDIA GPU with compute capability 3.0 or higher
- CUDA-capable driver (460.x or later recommended)
- Check CUDA installation:
  ```bash
  nvcc --version
  nvidia-smi
  ```

## Performance Notes

1. **OpenMP Programs**:
   - Default to 4 threads (can be modified via `OMP_NUM_THREADS`)
   - Best performance on multi-core CPUs
   - Thread affinity matters for optimal performance

2. **Python Parallel Programs**:
   - Utilize available CPU cores automatically
   - Limited by Global Interpreter Lock (GIL) for some operations
   - Best for CPU-bound tasks

3. **CUDA Programs**:
   - Optimized for GPUs with compute capability 3.0 or higher
   - Performance scales with GPU capabilities
   - Memory transfers can be a bottleneck

## Best Practices

1. **Data Size Considerations**:
   - Small datasets: Sequential might be faster due to overhead
   - Large datasets: Parallel versions show significant speedup
   - CUDA: Best for very large datasets (millions of elements)

2. **Memory Management**:
   - OpenMP: Be careful with shared vs private variables
   - CUDA: Optimize memory transfers between host and device
   - Python: Consider using numpy arrays for better performance

3. **Thread Safety**:
   - Use critical sections only when necessary
   - Minimize thread contention
   - Be aware of race conditions

## Troubleshooting

1. **OpenMP Issues**:
   - Check if OpenMP is enabled: `echo |cpp -fopenmp -dM |grep -i open`
   - Set number of threads: `export OMP_NUM_THREADS=4`

2. **CUDA Issues**:
   - Verify GPU availability: `nvidia-smi`
   - Check CUDA path: `echo $PATH | grep cuda`
   - Ensure correct compute capability
