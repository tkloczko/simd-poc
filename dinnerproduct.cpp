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

#include "InnerProduct.h"
#include "AlignedArray.h"
#include "simd_double.h"

#include <chrono>
#include <iostream>
#include <map>
#include <functional>

#define N 256UL

double res;

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

int dotClikeAlignedArray()
{
    AlignedArray<N> a;
    AlignedArray<N> b;

    for (std::size_t i = 0UL; i < N; ++i) {
        a[i] = i * 0.5;
        b[i] = i * 0.2;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    res = innerProduct(a.data(), b.data(), a.size());

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

int dotClikeStdVector()
{
    std::vector<double> va(N);
    std::vector<double> vb(N);

    for (std::size_t i = 0UL; i < N; ++i) {
        va[i] = i * 0.5;
        vb[i] = i * 0.2;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    res = innerProduct(va.data(), vb.data(), va.size());

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

int dotCppStdVector()
{
    std::vector<double> va(N);
    std::vector<double> vb(N);

    for (std::size_t i = 0UL; i < N; ++i) {
        va[i] = i * 0.5;
        vb[i] = i * 0.2;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    res = innerProduct(va, vb);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

int dotCppStdArray()
{
    std::array<double, N> aa;
    std::array<double, N> bb;

    for (std::size_t i = 0UL; i < N; ++i) {
        aa[i] = i * 0.5;
        bb[i] = i * 0.2;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    res = innerProduct(aa, bb);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

int dotSimdAlignedArray()
{
    AlignedArray<N> a;
    AlignedArray<N> b;

    for (std::size_t i = 0UL; i < N; ++i) {
        a[i] = i * 0.5;
        b[i] = i * 0.2;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    res = innerProductSimd(a, b);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

int dotOmpAlignedArray()
{
    AlignedArray<N> a;
    AlignedArray<N> b;

    for (std::size_t i = 0UL; i < N; ++i) {
        a[i] = i * 0.5;
        b[i] = i * 0.2;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    res = innerProductOmp(a, b);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

int main(int, char **)
{
    std::cout << "------------------------------------" << std::endl;
    std::cout << " Vector size = " << N << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Method  |     Container  |   Time"    << std::endl;
    std::cout << "------------------------------------" << std::endl;

    std::map<std::string, std::function<int()> > f_list;
    f_list["C-loop  |  AlignedArray  | "] = dotClikeAlignedArray;
    f_list["C-loop  |   std::vector  | "] = dotClikeStdVector;
    f_list["Cpp     |   std::vector  | "] = dotCppStdVector;
    f_list["Cpp     |    std::array  | "] = dotCppStdArray;
    f_list["SIMD    |  AlignedArray  | "] = dotSimdAlignedArray;
    f_list["OpenMP  |  AlignedArray  | "] = dotOmpAlignedArray;


    std::vector<double> times(f_list.size());

    int rep = 1000023;

    for (int i = 0; i < rep; ++i) {
        int count = 0;
        for (auto func : f_list) {
            times[count++] += func.second();
        }
    }

    for (std::size_t i = 0; i < f_list.size(); ++i) {
        times[i] /= rep * 1.;
    }

    int i = 0;
    for (auto it : f_list) {
        std::cout << it.first << times[i++] << std::endl;
    }
    std::cout << "------------------------------------" << std::endl;
}

//
// main.cpp ends here
