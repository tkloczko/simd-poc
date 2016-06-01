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

# Results
