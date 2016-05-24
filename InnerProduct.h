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
//
// /////////////////////////////////////////////////////////////////

inline double innerProduct(const double *lhs, const double *rhs, std::size_t size)
{
    double res(lhs[0] * rhs[0]);

    for (std::size_t i = 1UL; i < size; ++i) {
        res += lhs[i] * rhs[i];
    }

    return res;
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

#include <vector>

inline double innerProduct(const std::vector<double>& lhs, const std::vector<double>& rhs)
{
    const std::size_t size(lhs.size());

    double res(lhs[0] * rhs[0]);

    for (std::size_t i = 1UL; i < size; ++i) {
        res += lhs[i] * rhs[i];
    }

    return res;
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

#include <array>

template < std::size_t N >
inline double innerProduct(const std::array<double, N>& lhs, const std::array<double, N>& rhs)
{
    double res = 0;

    for (std::size_t i = 0UL; i < N; ++i) {
        res += lhs[i] * rhs[i];
    }

    return res;
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

#include "AlignedArray.h"
#include "simd_double.h"

template < std::size_t N >
inline double innerProductSimd(const AlignedArray<N>& lhs, const AlignedArray<N>& rhs)
{
    simd_double xmm1, xmm2, xmm3, xmm4;

   const size_t iend(N - N % (4UL * 4UL));

   for( size_t i = 0UL; i < iend; i += 4UL * 4UL ) {
       xmm1 = xmm1 + ( load(&lhs[i        ]) * load(&rhs[i        ]) );
       xmm2 = xmm2 + ( load(&lhs[i+4UL    ]) * load(&rhs[i+4UL    ]) );
       xmm3 = xmm3 + ( load(&lhs[i+4UL*2UL]) * load(&rhs[i+4UL*2UL]) );
       xmm4 = xmm4 + ( load(&lhs[i+4UL*3UL]) * load(&rhs[i+4UL*3UL]) );
   }

   double res(sum(xmm1 + xmm2 + xmm3 + xmm4));

   for( size_t i = iend; i < N; ++i)
       res += lhs[i] * rhs[i];

   return res;
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

#include <omp.h>

template < std::size_t N >
inline double innerProductOmp(const AlignedArray<N>& lhs, const AlignedArray<N>& rhs)
{
    double res = 0;
    const double *l(lhs.data());
    const double *r(rhs.data());

#pragma omp simd reduction(+:res) aligned(l,r:32)
    for (std::size_t i = 0UL; i < N; ++i) {
        res += l[i] * r[i];
    }

    return res;
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

#include <dtkContainers>

template < std::size_t N, std::size_t Alignment >
inline double innerProduct(const dtkStaticArray<double, N, Alignment>& lhs, const dtkStaticArray<double, N, Alignment>& rhs)
{
    double res = 0;

    for (std::size_t i = 0UL; i < N; ++i) {
        res += lhs[i] * rhs[i];
    }

    return res;
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

inline double innerProduct(const dtk::Array<double>& lhs, const dtk::Array<double>& rhs)
{
    dtk::Array<double>::size_type N(lhs.size());
    double res = 0;

    for (std::size_t i = 0UL; i < N; ++i) {
        res += lhs[i] * rhs[i];
    }

    return res;
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

template < std::size_t N, std::size_t Alignment >
inline double innerProductOmp(const dtkStaticArray<double, N, Alignment>& lhs, const dtkStaticArray<double, N, Alignment>& rhs)
{
    double res = 0;
    const double *l(lhs.data());
    const double *r(rhs.data());

#pragma omp simd reduction(+:res) aligned(l, r:32)
    for (std::size_t i = 0UL; i < N; i += 4UL) {
        res += l[i] * r[i];
    }

    return res;
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

inline double innerProductOmp(const dtk::Array<double>& lhs, const dtk::Array<double>& rhs)
{
    dtk::Array<double>::size_type N(lhs.size());

    double res = 0;
    const double *l(lhs.data());
    const double *r(rhs.data());

#pragma omp simd reduction(+:res) aligned(l, r:32)
    for (std::size_t i = 0UL; i < N; i += 4UL) {
        res += l[i] * r[i];
    }

    return res;
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

inline double innerProductOmp(const double *l, const double *r, const std::size_t N)
{
    double res = 0;

#pragma omp simd reduction(+:res) aligned(l,r:32)
    for (std::size_t i = 0UL; i < N; ++i) {
        res += l[i] * r[i];
    }

    return res;
}

//
// dtkInnerProduct.h ends here
