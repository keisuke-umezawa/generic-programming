#include <iostream>

#define NoncommutativeAdditiveSemigroup typename
#define Integer typename

template <Integer N> inline
N half(N n)
{
    return n >> 1;
}

template <Integer N> inline
bool is_odd(N n)
{
    return static_cast<bool>(n & 0x1);
}

template <NoncommutativeAdditiveSemigroup A, Integer N>
inline A multiply_accumulate_semigroup(A r, N n, A a) {
    // precondition : n >= 0
    if (n == 0) {
        return r;
    }
    while (true) {
        if (is_odd(n)) {
            r = r + a;
            if (n == 1) {
                return r;
            }
        }
        n = half(n);
        a = a + a;
    }

}

template <NoncommutativeAdditiveSemigroup A, Integer N>
inline A multiply_semigroup(N n, A a) {
    // precondition : n >= 0
    while (!is_odd(n)) {
        a = a + a;
        n = half(n);
    }
    if (n == 1) {
        return a;
    }
    return multiply_accumulate_semigroup(a, half(n - 1), a + a);

}

int main(int argc, char** argv)
{
    const int n = 11;
    const int value = 5;

    std::cout << multiply_semigroup(n, value) << std::endl;
    return 0;
}