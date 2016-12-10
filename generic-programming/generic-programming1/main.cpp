#include <iostream>

int multiply0(const int n, const int a)
{
    if (n == 1) return a;
    return multiply0(n - 1, a) + a;
}

int half(const int n)
{
    return n >> 1;
}

bool is_odd(const int n)
{
    return n & 0x1;
}

int multiply1(const int n, const int a)
{
    if (n == 1) return a;
    int result = multiply1(half(n), a + a);
    if (is_odd(n)) result += a;
    return multiply0(n - 1, a) + a;
}

int mult_acc0(int r, const int n, const int a)
{
    if (is_odd(n)) {
        r += a;
        if (n == 1) {
            return r;
        }
    }
    return mult_acc0(r, half(n), a + a);
}

int main(int argc, char** argv)
{
    const int n = 11;
    const int value = 5;

    std::cout << mult_acc0(0, n, value) << std::endl;
    return 0;
}