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

#include <immintrin.h>

// /////////////////////////////////////////////////////////////////
// Wrapper for avx 256 double
// /////////////////////////////////////////////////////////////////

struct simd_double
{
    __m256d xmm;
    simd_double(void) : xmm( _mm256_setzero_pd() ) {}
    simd_double(__m256d x) : xmm(x) {}
    double operator [] (std::size_t i) const { return reinterpret_cast<const double *>(&xmm)[i]; }
};

// /////////////////////////////////////////////////////////////////
// Operations
// /////////////////////////////////////////////////////////////////

inline simd_double operator + (const simd_double& a, const simd_double& b)
{
    return _mm256_add_pd(a.xmm, b.xmm);
}

inline simd_double operator - (const simd_double& a, const simd_double& b)
{
    return _mm256_sub_pd(a.xmm, b.xmm);
}

inline simd_double operator * (const simd_double& a, const simd_double& b)
{
    return _mm256_mul_pd(a.xmm, b.xmm);
}

inline simd_double operator / (const simd_double& a, const simd_double& b)
{
    return _mm256_div_pd(a.xmm, b.xmm);
}

// /////////////////////////////////////////////////////////////////
// Setters
// /////////////////////////////////////////////////////////////////

inline simd_double set(double value)
{
    return _mm256_set1_pd(value);
}

inline void setZero(simd_double& value)
{
    value.xmm = _mm256_setzero_pd();
}

// /////////////////////////////////////////////////////////////////
// Reduction via sum
// /////////////////////////////////////////////////////////////////

inline double sum(const simd_double& a)
{
    const simd_double b( _mm256_hadd_pd(a.xmm, a.xmm) );
    const __m128d c = _mm_add_pd( _mm256_extractf128_pd(b.xmm, 1), _mm256_castpd256_pd128(b.xmm) );
    return *reinterpret_cast<const double *>(&c);
}

// /////////////////////////////////////////////////////////////////
// Load, store and stream
// /////////////////////////////////////////////////////////////////

inline simd_double load(const double *address)
{
    return _mm256_load_pd(address);
}

inline simd_double loadu(const double *address)
{
    return _mm256_loadu_pd(address);
}

inline void store(double *address, const simd_double& value)
{
    _mm256_store_pd(address, value.xmm);
}

inline void storeu(double *address, const simd_double& value)
{
    _mm256_storeu_pd(address, value.xmm);
}

inline void stream(double *address, const simd_double& value)
{
    _mm256_stream_pd(address, value.xmm);
}

//
// simd_double.h ends here
