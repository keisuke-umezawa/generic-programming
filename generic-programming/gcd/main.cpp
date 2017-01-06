#include <iostream>
#include <vector>

#define InputIterator typename
#define Semiring typename
#define Real typename

template <typename T> inline
bool equal(const std::vector<T>& a, const std::vector<T>& b)
{
    if (a.size() != b.size()) return false;
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

template <Real T>
class polynomial {
public:
    polynomial(const std::vector<T>& c)
        : _c(c)
    {
    }
    const T& operator()(const std::size_t i) const
    {
        return _c[i];
    }
    bool operator==(const polynomial& other) const
    {
        return 
    }
private:
    std::vector<T> _c;
};

template <Real R> inline
polynomial<R> gcd(polynomial<R> a, polynomial<R> b)
{
    while (b != polynomial<R>(0)) {
    }
}

template <InputIterator I, Semiring R> inline
R polynomial_value(I first, I last, R x) {
    if (first == last) {
        return R(0);
    }
    R sum(*first);
    while (++first != last) {
        sum *= x;
        sum += *first;
    }
    return sum;
}



int main(int argc, char** argv)
{
    const int x = 10;
    const std::vector<int> c1 = { 1, 2, 3, 4 };
    const std::vector<int> c2 = { 1, 2, 3, 4 };
    std::cout << equal(c1, c2) << std::endl;

    std::cin;
    return 0;
}