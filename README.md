# Summary

The goal of this code snippet is to investigate the performance gain
resulting from the use of SIMD features provided by openMP 4.5.

Two cases are studied:
- the inner product of two double floating point vectors
- the matrix-vector multiplication still with double precision.

These two cases are applied to small size of vectors and matrices,
typically for sizes between 8 and 64 elements per row (or column).

Such cases are relevant when dealing with Discontinuous-Galerkin
methods applied to either Maxwell equations or Navier-Stokes problems.

# Benchmark setup

The hardware is Intel with 4 Cores i7-5600U CPU @ 2.60GHz featuring
AVX2.

For both cases, three kinds of strategy are followed:
- pure c or c++ for loop code
- use of openMP SIMD pragma
- use of intel intrinsecs

In the case of the inner product, different containers are tested
(std::vector, std::array, custom static aligned array).

In the case of the matrix-vector multiplication, the extern loop is
blocked in some functions. Moreover, only custom aligned array is
used.

Two compilers are tested:
- GCC 6.1.0
- Intel ICC 16.0.3

# Results

## Inner Product

The inner product is performed 1000023 times, the vector size is 256.

### GCC 6.1.0

| Method  |     Container  |   Time (us) |
|---------|----------------|-------------|
| C-loop  |   std::vector  | 0.00132797  |
| C-loop  |  AlignedArray  | 0.00103898  |
| Cpp     |    std::array  | 0.00140897  |
| Cpp     |   std::vector  | 0.00123997  |
| OpenMP  |  AlignedArray  | 0.000403991 |
| SIMD    |  AlignedArray  | 0.000212995 |

### Intel 16.0.3


## Matrix-Vector Multiplication

The inner product is performed 1000023 times.

-------------------------------------------
| Matrix size (M,N) = (64,64)             |
-------------------------------------------
Method       |  Container     | Time
-------------------------------------------
C-blocked    |  AlignedArray  | 1.01194
C-pure       |  AlignedArray  | 3.02451
omp-blocked  |  AlignedArray  | 0.0128367
omp-pure     |  AlignedArray  | 1.01515
simd-pure    |  AlignedArray  | 0.00412391
-------------------------------------------
