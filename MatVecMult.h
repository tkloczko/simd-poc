// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include <cstddef>

// /////////////////////////////////////////////////////////////////
// C-like functions
// /////////////////////////////////////////////////////////////////

inline void matVecMult(double *y, const double *A, const double *x, std::size_t row_count, std::size_t col_count)
{
    for (std::size_t i = 0; i < row_count; ++i) {
        const std::size_t N = i * col_count;
        double res = 0;
        for (std::size_t j = 0; j < col_count; ++j) {
            res += A[N+j] * x[j];
        }
        y[i] = res;
    }
}

inline void matVecMultHelped(double * __restrict__ y, const double *__restrict__ A, const double *__restrict__ x, std::size_t row_count, std::size_t col_count)
{
    const std::size_t jend (col_count);
    double res0, res1, res2, res3;
    double res4, res5, res6, res7;

    for (std::size_t i = 0; i < row_count; i+=8UL) {
        res0 = res1 = res2 = res3 = 0;
        res4 = res5 = res6 = res7 = 0;
        const std::size_t N0 = i * col_count;
        const std::size_t N1 = (i+1UL) * col_count;
        const std::size_t N2 = (i+2UL) * col_count;
        const std::size_t N3 = (i+3UL) * col_count;
        const std::size_t N4 = (i+4UL) * col_count;
        const std::size_t N5 = (i+5UL) * col_count;
        const std::size_t N6 = (i+6UL) * col_count;
        const std::size_t N7 = (i+7UL) * col_count;

        for (std::size_t j = 0UL; j < jend; ++j) {
            res0 += A[N0+j] * x[j];
            res1 += A[N1+j] * x[j];
            res2 += A[N2+j] * x[j];
            res3 += A[N3+j] * x[j];
            res4 += A[N4+j] * x[j];
            res5 += A[N5+j] * x[j];
            res6 += A[N6+j] * x[j];
            res7 += A[N7+j] * x[j];
        }
        y[i    ] = res0;
        y[i+1UL] = res1;
        y[i+2UL] = res2;
        y[i+3UL] = res3;
        y[i+4UL] = res4;
        y[i+5UL] = res5;
        y[i+6UL] = res6;
        y[i+7UL] = res7;
    }
}

// /////////////////////////////////////////////////////////////////
// OpenMP like functions
// /////////////////////////////////////////////////////////////////

#include <omp.h>

inline void matVecMultOmp(double * __restrict__ y, const double *__restrict__ A, const double *__restrict__ x, std::size_t row_count, std::size_t col_count)
{
    const std::size_t jend (col_count);
    double res;
    for (std::size_t i = 0; i < row_count; ++i) {
        res = 0;
        const std::size_t N = i * col_count;
#pragma omp simd reduction(+:res) aligned(A, x, y:32)
        for (std::size_t j = 0UL; j < jend; ++j) {
            res += A[N+j] * x[j];
        }
        y[i] = res;
    }
}

inline void matVecMultOmpHelped(double * __restrict__ y, const double *__restrict__ A, const double *__restrict__ x, std::size_t row_count, std::size_t col_count)
{
    const std::size_t jend (col_count);
    double res0, res1, res2, res3;
    double res4, res5, res6, res7;

    for (std::size_t i = 0; i < row_count; i+=8UL) {
        res0 = res1 = res2 = res3 = 0;
        res4 = res5 = res6 = res7 = 0;
        const std::size_t N0 = i * col_count;
        const std::size_t N1 = (i+1UL) * col_count;
        const std::size_t N2 = (i+2UL) * col_count;
        const std::size_t N3 = (i+3UL) * col_count;
        const std::size_t N4 = (i+4UL) * col_count;
        const std::size_t N5 = (i+5UL) * col_count;
        const std::size_t N6 = (i+6UL) * col_count;
        const std::size_t N7 = (i+7UL) * col_count;

#pragma omp simd reduction(+:res0, res1, res2, res3, res4, res5, res6, res7) aligned(A, y, x:32)
        for (std::size_t j = 0UL; j < jend; ++j) {
            res0 += A[N0+j] * x[j];
            res1 += A[N1+j] * x[j];
            res2 += A[N2+j] * x[j];
            res3 += A[N3+j] * x[j];
            res4 += A[N4+j] * x[j];
            res5 += A[N5+j] * x[j];
            res6 += A[N6+j] * x[j];
            res7 += A[N7+j] * x[j];
        }
        y[i    ] = res0;
        y[i+1UL] = res1;
        y[i+2UL] = res2;
        y[i+3UL] = res3;
        y[i+4UL] = res4;
        y[i+5UL] = res5;
        y[i+6UL] = res6;
        y[i+7UL] = res7;
    }
}

// /////////////////////////////////////////////////////////////////
// Intel Simd Intrinsec function
// /////////////////////////////////////////////////////////////////

#include "simd_double.h"

inline void matVecMultSimd(double *y, const double *A, const double *x, std::size_t row_count, std::size_t col_count)
{
    const std::size_t M(row_count);
    const std::size_t N(col_count);

    std::size_t i(0UL);

    for (; (i+8UL) <= M; i+=8UL) {
        std::size_t j(0UL);
        const std::size_t jend(N);

        simd_double xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7, xmm8;

        for (; j < jend; j += 4UL ) {
            const simd_double x1(load(&x[j]));
            xmm1 = xmm1 + load(&A[(i    ) * N + j]) * x1;
            xmm2 = xmm2 + load(&A[(i+1UL) * N + j]) * x1;
            xmm3 = xmm3 + load(&A[(i+2UL) * N + j]) * x1;
            xmm4 = xmm4 + load(&A[(i+3UL) * N + j]) * x1;
            xmm5 = xmm5 + load(&A[(i+4UL) * N + j]) * x1;
            xmm6 = xmm6 + load(&A[(i+5UL) * N + j]) * x1;
            xmm7 = xmm7 + load(&A[(i+6UL) * N + j]) * x1;
            xmm8 = xmm8 + load(&A[(i+7UL) * N + j]) * x1;
        }

        y[i    ] = sum( xmm1 );
        y[i+1UL] = sum( xmm2 );
        y[i+2UL] = sum( xmm3 );
        y[i+3UL] = sum( xmm4 );
        y[i+4UL] = sum( xmm5 );
        y[i+5UL] = sum( xmm6 );
        y[i+6UL] = sum( xmm7 );
        y[i+7UL] = sum( xmm8 );
    }

    for (; (i+4UL) <= M; i+=4UL) {
        std::size_t j(0UL);
        const std::size_t jend(N);

        simd_double xmm1, xmm2, xmm3, xmm4;

        for (; j < jend; j += 4UL ) {
            const simd_double x1(load(&x[j]));
            xmm1 = xmm1 + load(&A[(i    ) * N + j]) * x1;
            xmm2 = xmm2 + load(&A[(i+1UL) * N + j]) * x1;
            xmm3 = xmm3 + load(&A[(i+2UL) * N + j]) * x1;
            xmm4 = xmm4 + load(&A[(i+3UL) * N + j]) * x1;
        }

        y[i    ] = sum( xmm1 );
        y[i+1UL] = sum( xmm2 );
        y[i+2UL] = sum( xmm3 );
        y[i+3UL] = sum( xmm4 );
    }

    for (; (i+3UL) <= M; i+=3UL) {
        std::size_t j(0UL);
        const std::size_t jend(N);

        simd_double xmm1, xmm2, xmm3;

        for (; j < jend; j += 4UL ) {
            const simd_double x1(load(&x[j]));
            xmm1 = xmm1 + load(&A[(i    ) * N + j]) * x1;
            xmm2 = xmm2 + load(&A[(i+1UL) * N + j]) * x1;
            xmm3 = xmm3 + load(&A[(i+2UL) * N + j]) * x1;
        }

        y[i    ] = sum( xmm1 );
        y[i+1UL] = sum( xmm2 );
        y[i+2UL] = sum( xmm3 );
    }

    for (; (i+2UL) <= M; i+=2UL) {
        std::size_t j(0UL);
        const std::size_t jend(N);

        simd_double xmm1, xmm2;

        for (; j < jend; j += 4UL ) {
            const simd_double x1(load(&x[j]));
            xmm1 = xmm1 + load(&A[(i    ) * N + j]) * x1;
            xmm2 = xmm2 + load(&A[(i+1UL) * N + j]) * x1;
        }

        y[i    ] = sum( xmm1 );
        y[i+1UL] = sum( xmm2 );
    }

    if ( i < M ) {
        std::size_t j(0UL);
        const std::size_t jend(N);

        simd_double xmm1;

        for (; j < jend; j += 4UL ) {
            const simd_double x1(load(&x[j]));
            xmm1 = xmm1 + load(&A[i * N + j]) * x1;
        }

        y[i] = sum( xmm1 );
    }
}

//
// MatVecMult.h ends here
