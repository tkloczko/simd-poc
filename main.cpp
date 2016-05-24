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
    std::cout << "Res= " << res << ". C-like with AlignedArray time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
}

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
    std::cout << "Res= " << res << ". C-like with  std::vector time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
}

int dotClikeDtkArray()
{
    dtk::Array<double> a(N);
    dtk::Array<double> b(N);

    for (std::size_t i = 0UL; i < N; ++i) {
        a[i] = i * 0.5;
        b[i] = i * 0.2;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    res = innerProduct(a.data(), b.data(), a.size());

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Res= " << res << ". C-like with   dtk::Array time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
}

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
    std::cout << "Res= " << res << ". C++    with  std::vector time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
}

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
    std::cout << "Res= " << res << ". C++    with   std::array time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
}

int dotCppDtkArray()
{
    dtk::Array<double> a(N);
    dtk::Array<double> b(N);

    for (std::size_t i = 0UL; i < N; ++i) {
        a[i] = i * 0.5;
        b[i] = i * 0.2;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    res = innerProduct(a, b);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Res= " << res << ". C++    with   dtk::Array time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
}

int dotCppDtkStaticArray()
{
    dtkStaticArray<double, N, 32> a;
    dtkStaticArray<double, N, 32> b;

    for (std::size_t i = 0UL; i < N; ++i) {
        a[i] = i * 0.5;
        b[i] = i * 0.2;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    res = innerProduct(a, b);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

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
    std::cout << "Res= " << res << ". SIMD   with AlignedArray time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
}

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
    std::cout << "Res= " << res << ". OpenMP with AlignedArray time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
}

int dotOmpDtkArray()
{
    dtk::Array<double> a(N);
    dtk::Array<double> b(N);

    for (std::size_t i = 0UL; i < N; ++i) {
        a[i] = i * 0.5;
        b[i] = i * 0.2;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    res = innerProductOmp(a, b);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int dotOmpDtkStaticArray()
{
    dtkStaticArray<double, N, 32UL> a;
    dtkStaticArray<double, N, 32UL> b;

    for (std::size_t i = 0UL; i < N; ++i) {
        a[i] = i * 0.5;
        b[i] = i * 0.2;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    res = innerProductOmp(a, b);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int dotOmpCLikeDtkArray()
{
    dtk::Array<double> a(N);
    dtk::Array<double> b(N);

    for (std::size_t i = 0UL; i < N; ++i) {
        a[i] = i * 0.5;
        b[i] = i * 0.2;
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    res = innerProductOmp(a.data(), b.data(), a.size());

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

int main(int, char **)
{
    std::map<std::string, std::function<int()> > f_list;
    f_list["C-like  |  AlignedArray  | "] = dotClikeAlignedArray;
    f_list["C-like  |   std::vector  | "] = dotClikeStdVector;
    f_list["C-like  |    dtk::Array  | "] = dotClikeDtkArray;
    f_list["Cpp     |   std::vector  | "] = dotCppStdVector;
    f_list["Cpp     |    std::array  | "] = dotCppStdArray;
    f_list["Cpp     |    dtk::array  | "] = dotCppDtkArray;
    f_list["Cpp     | dtkStaticArray | "] = dotCppDtkStaticArray;
    f_list["SIMD    |  AlignedArray  | "] = dotSimdAlignedArray;
    f_list["OpenMP  |  AlignedArray  | "] = dotOmpAlignedArray;
    f_list["OpenMP  |    dtk::Array  | "] = dotOmpDtkArray;
    f_list["OpenMP  | dtkStaticArray | "] = dotOmpDtkStaticArray;
    f_list["OMP C   |    dtk::Array  | "] = dotOmpCLikeDtkArray;


    std::vector<double> times(f_list.size());

    int rep = 1000023;

    for (int i = 0; i < rep; ++i) {
        int count = 0;
        for (auto func : f_list) {
            times[count++] += func.second();
        }
    }

    for (int i = 0; i < f_list.size(); ++i) {
        times[i] /= rep * 1.;
    }

    int i = 0;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Method  |     Container  |   Time"    << std::endl;
    std::cout << "------------------------------------" << std::endl;
    for (auto it : f_list) {
        std::cout << it.first << times[i++] << std::endl;
    }
    std::cout << "------------------------------------" << std::endl;
}

//
// main.cpp ends here
