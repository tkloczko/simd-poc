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

#include "MatVecMult.h"
#include "AlignedArray.h"
#include "simd_double.h"

#include <chrono>
#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <cmath>

#define N 64UL
#define M 64UL

double res = 0;
double res0 = 0;

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

int CLikeTest()
{
    AlignedArray<M*N> A;
    AlignedArray<N> x;
    AlignedArray<M> y;

    for (std::size_t i = 0UL; i < N*M; ++i) {
        A[i] = i * 0.5;
    }
    for (std::size_t i = 0UL; i < N; ++i) {
        x[i] = i * 0.1414;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    matVecMult(y, A, x, M, N);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    res += y[0];
    res0 = y[0];

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

int CLikeHelpedTest()
{
    AlignedArray<M*N> A;
    AlignedArray<N> x;
    AlignedArray<M> y;

    for (std::size_t i = 0UL; i < N*M; ++i) {
        A[i] = i * 0.5;
    }
    for (std::size_t i = 0UL; i < N; ++i) {
        x[i] = i * 0.1414;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    matVecMultHelped(y, A, x, M, N);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    res += y[0];
    res0 = y[0];

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

int COmpTest()
{
    AlignedArray<M*N> A;
    AlignedArray<N> x;
    AlignedArray<M> y;

    for (std::size_t i = 0UL; i < N*M; ++i) {
        A[i] = i * 0.5;
    }
    for (std::size_t i = 0UL; i < N; ++i) {
        x[i] = i * 0.1414;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    matVecMultOmp(y, A, x, M, N);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    res += y[0];

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

int COmpHelpedTest()
{
    AlignedArray<M*N> A;
    AlignedArray<N> x;
    AlignedArray<M> y;

    for (std::size_t i = 0UL; i < N*M; ++i) {
        A[i] = i * 0.5;
    }
    for (std::size_t i = 0UL; i < N; ++i) {
        x[i] = i * 0.1414;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    matVecMultOmpHelped(y, A, x, M, N);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    res += y[0];

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

int CSimdTest()
{
    AlignedArray<M*N> A;
    AlignedArray<N> x;
    AlignedArray<M> y;

    for (std::size_t i = 0UL; i < N*M; ++i) {
        A[i] = i * 0.5;
    }
    for (std::size_t i = 0UL; i < N; ++i) {
        x[i] = i * 0.1414;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    matVecMultSimd(y, A, x, M, N);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    res += y[0];

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

int main(int, char **)
{
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << " Matrix size (M,N) = (" << M << "," << N << ")" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Method       |  Container     | Time       " << std::endl;
    std::cout << "-------------------------------------------" << std::endl;

    std::map<std::string, std::function<int()> > f_list;
    f_list["C-pure       |  AlignedArray  | "] = CLikeTest;
    f_list["C-blocked    |  AlignedArray  | "] = CLikeHelpedTest;
    f_list["omp-pure     |  AlignedArray  | "] = COmpTest;
    f_list["omp-blocked  |  AlignedArray  | "] = COmpHelpedTest;
    f_list["simd-pure    |  AlignedArray  | "] = CSimdTest;


    std::vector<double> times(f_list.size());

    int rep = 1000023;

    for (int i = 0; i < rep; ++i) {
        int count = 0;
        for (auto func : f_list) {
            double resu = res;
            times[count++] += func.second();
            if (std::fabs(res0 - (res- resu)) > 1.e-4)
                std::cout << res - resu << " " << res0  << std::endl;
        }
    }

    for (std::size_t i = 0; i < f_list.size(); ++i) {
        times[i] /= rep * 1.;
    }

    int i = 0;
    for (auto it : f_list) {
        std::cout << it.first << times[i++] << std::endl;
    }
    std::cout << "-------------------------------------------" << std::endl;
}

//
// dmatvecmult.cpp ends here
