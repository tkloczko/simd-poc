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
#include <algorithm>
#include <initializer_list>

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

template < std::size_t N > class AlignedArray
{
    enum { NN = N + (4UL - (N % 4UL)) % 4UL };

    alignas(32) double m_array[NN];

public:
    inline AlignedArray() {;}
    inline AlignedArray(std::initializer_list<double> init)
    {
        std::size_t i = 0UL;
        std::size_t MIN = std::min(N, init.size());
        auto it = init.begin();
        for (; i < MIN; ++it, ++i) {
            m_array[i] = *it;
        }
        for (; i < NN; ++i) {
            m_array[i] = 0.;
        }
    }

    inline AlignedArray& operator = (std::initializer_list<double> init)
    {
        std::size_t i = 0UL;
        std::size_t MIN = std::min(N, init.size());
        auto it = init.begin();
        for (; i < MIN; ++it, ++i) {
            m_array[i] = *it;
        }
        for (; i < NN; ++i) {
            m_array[i] = 0.;
        }
    }

public:
    inline std::size_t     size(void) const { return  N; }
    inline std::size_t capacity(void) const { return NN; }

public:
    inline operator       double *()       { return m_array; }
    inline operator const double *() const { return m_array; }

    inline       double& operator [] (std::size_t i)       { return m_array[i]; }
    inline const double& operator [] (std::size_t i) const { return m_array[i]; }

    inline       double *data()       { return m_array; }
    inline const double *data() const { return m_array; }
};

//
// AlignedArray.h ends here
