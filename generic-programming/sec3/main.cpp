#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

#define Integer typename
#define RandomAccessIterator typename

std::size_t index_to_value(const std::size_t index)
{
    return 2 * index + 3;
}

template <RandomAccessIterator I, Integer N>
inline void mark_sieve(I first, I last, N factor) {
    assert(first != last);
    *first = false;
    while (last - first > factor) {
        first += factor;
        *first = false;
    }
}

template <RandomAccessIterator I, Integer N>
inline void sift0(I first, N n) {
    std::fill(first, first + n, true);
    N i = 0;
    N index_square = 3; 
    while (index_square < n) {
        // 不変条件: index_square = 2i^2 + 6i + 3
        if (first[i]) {
            mark_sieve(first + index_square, first + n, i + i + 3);
        }
        ++i;
        index_square = 2 * i * (i + 3) + 3;
    }
}

template <RandomAccessIterator I, Integer N>
inline void sift1(I first, N n) {
    I last = first + n;
    std::fill(first, last, true);
    N i(0);
    N index_square(3); 
    N factor(3);
    while (index_square < n) {
        // 不変条件: index_square = 2i^2 + 6i + 3
        if (first[i]) {
            mark_sieve(first + index_square, last, factor);
        }
        ++i;
        factor = i + i + 3;
        index_square = 2 * i * (i + 3) + 3;
    }
}

template <RandomAccessIterator I, Integer N>
inline void sift(I first, N n) {
    I last = first + n;
    std::fill(first, last, true);
    N i(0);
    N index_square(3); 
    N factor(3);
    while (index_square < n) {
        // 不変条件: index_square = 2i^2 + 6i + 3
        if (first[i]) {
            mark_sieve(first + index_square, last, factor);
        }
        ++i;
        index_square += factor;
        factor += N(2);
        index_square += factor;
    }
}
template <RandomAccessIterator I, Integer N>
inline void print(I first, N n) {
    for (std::size_t i = 0; i < n; ++i) {
        if (*first) {
            std::cout << index_to_value(i) << " ";
        }
        ++first;
    }
    std::cout << std::endl;
}

template <RandomAccessIterator I, Integer N>
inline std::size_t count(I first, N n) {
    I last = first + n;
    return std::count(first, last, true);
}

typedef std::size_t line_segment;

line_segment gcm(line_segment a, line_segment b)
{
    if (a == b) {
        return a;
    }
    if (b < a) {
        return gcm(a - b, b);
    }
    return gcm(a, b - a);
}

int main(int argc, char* argv)
{
    //for (std::size_t i = 10; i <= 10000000; i *= 10) {
    //    std::vector<bool> bools(i);
    //    sift(bools.begin(), i);
    //    std::cout << i << " " << count(bools.begin(), i) << std::endl;
    //}
    std::cout << gcm(22, 121) << std::endl;

    return 0;
}
