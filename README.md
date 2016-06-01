# Summary
<p>
The goal of this code snippet is to investigate the performance gain resulting from the use of SIMD features provided by openMP 4.5.
</p>

Two cases are studied:
- the inner product of two double floating point vectors
- the matrix-vector multiplication still with double precision.

These two cases are applied to small size of vectors and matrices, typically for sizes between 8 and 64 elements per row (or column).

Such cases are relevant when dealing with Discontinuous-Galerkin methods applied to either Maxwell equations or Navier-Stokes problems.

# Benchmark setup

The hardware is Intel with 4 Cores i7-5600U CPU @ 2.60GHz featuring AVX2.

For both cases, three kinds of strategy are followed:
- pure c or c++ for loop code
- use of openMP SIMD pragma
- use of intel intrinsics (credits to [blaze-lib developers] (https://bitbucket.org/blaze-lib/blaze))

In the case of the inner product, different containers are tested (std::vector, std::array, custom static aligned array).

In the case of the matrix-vector multiplication, the extern loop is blocked in some functions. Moreover, only custom aligned array is used.

Two compilers are tested:
- GCC **6.1.0** with following options **-O3 -mavx2 -fopenmp** (one just needs to add `-DCMAKE_CXX_FLAGS=-mavx2` when configuring the project using cmake)
- Intel ICC **16.0.3** with following options **-O3 -xHOST -qopenmp** (one just needs to add `-DCMAKE_CXX_FLAGS=-xHOST` when configuring the project using cmake)

# Results

## Inner Product

The operation is performed **1,000,023 times**, the vector size is **256**.

### GCC 6.1.0

| Method         |     Container  |   Time (us) |
|----------------|----------------|-------------|
| C-loop         |   std::vector  | 0.00132797  |
| C-loop         |  AlignedArray  | 0.00103898  |
| Cpp            |    std::array  | 0.00140897  |
| Cpp            |   std::vector  | 0.00123997  |
| OpenMP         |  AlignedArray  | 0.000403991 |
| simd intrinsic |  AlignedArray  | 0.000212995 |

### Intel 16.0.3

| Method         |     Container  |   Time (us) |
|----------------|----------------|-------------|
| C-loop         |   std::vector  | 0.000319993 |
| C-loop         |  AlignedArray  | 0.000551987 |
| Cpp            |    std::array  | 0.000229995 |
| Cpp            |   std::vector  | 0.000408991 |
| OpenMP         |  AlignedArray  | 0.000268994 |
| simd intrinsic |  AlignedArray  | 0.000283993 |


## Matrix-Vector Multiplication

The operation is performed **1,000,023 times** and the matrix size is **(M,N) = (64,64)**.

### GCC 6.1.0

| Method         |     Container  |   Time (us) |
|----------------|----------------|-------------|
| C-blocked      |  AlignedArray  | 1.01194     |
| C-pure         |  AlignedArray  | 3.02451     |
| omp-blocked    |  AlignedArray  | 0.0128367   |
| omp-pure       |  AlignedArray  | 1.01515     |
| simd intrinsic |  AlignedArray  | 0.00412391  |

### Intel 16.0.3

| Method         |     Container  |   Time (us) |
|----------------|----------------|-------------|
| C-blocked      |  AlignedArray  | 0.00334492  |
| C-pure         |  AlignedArray  | 0.0042179   |
| omp-blocked    |  AlignedArray  | 0.00343892  |
| omp-pure       |  AlignedArray  | 0.00653285  |
| simd intrinsic |  AlignedArray  | 0.0042989   |

# Comments

As one can see, for both cases Intel compiler with the **-xHOST** option enables to vectorize the loops quite perfectly.

On the other hand, GCC does not behave so well especially when dealing with nested loops. Adding the line `#pragma omp simd` enables to recover good performance for the inner product but for the matrix vector product, even after blocking the main loop, the gain remains poor compared to the code using intel intrinsics.

Of course, such results need more investigations. We do not really know whether it is a bad use of GCC options (-Ofast works but as its edge effects make it irrelevant in our context) or just a lack of performance of the compiler. It may also depend on the cpu architecture.

Let us also notice that without the -fopenmp option, pure C code provides better performance than with it. It seems that such a behaviour has already been identified for previous versions ([see here] (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=60117)).

Eventually, it is tricky to draw clear conclusions about the gain brought by OpenMP simd diretives. Using Intel compiler with -xHOST option provides very good results without any change in the original code. Using GCC provides some good gains but theses latter require some code modifications and they are far from the optimal ones.

Comments and other tests are welcomed :-) !
