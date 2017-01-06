#include <iostream>
#include <vector>

#define InputIterator typename
#define Semiring typename
#define Real typename

namespace {
    template <typename T> inline
        T half(T n)
    {
        return n >> 1;
    }
}

template <typename T> inline
bool equal(const std::vector<T>& a, const std::vector<T>& b)
{
    if (a.size() != b.size()) return false;
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

template <typename T> inline
void print(const std::vector<T>& a)
{
    for (std::size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T> inline
std::vector<T> reduce(const std::vector<T>& a)
{
    std::size_t start = a.size();
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (a[i] != 0) {
            start = i;
            break;
        }
    }
    if (start == a.size()) return std::vector<T>(1, 0);
    std::vector<T> c;
    for (std::size_t i = start; i < a.size(); ++i) {
        c.push_back(a[i]);
    }
    return c;
}

template <Real T>
class polynomial {
public:
    polynomial()
        : _c(1, 0)
    {
    }
    explicit polynomial(const T& t)
        : _c(1, t)
    {
    }
    polynomial(const std::vector<T>& c)
        : _c(c)
    {
    }
    std::size_t order() const
    {
        return _c.size() - 1;
    }
    const T& operator()(const std::size_t i) const
    {
        return _c[i];
    }
    polynomial<T> operator -() const
    {
        auto a = *this;
        for (std::size_t i = 0; i < a._c.size(); ++i) {
            a._c[i] *= T(-1);
        }
        return a;
    }
    polynomial<T> operator -(const polynomial& other) const
    {
        return *this + (-other);
    }
    polynomial<T> operator +(const polynomial& other) const
    {
        auto bigger = this->order() > other.order() ? this->_c : other._c;
        auto smaller = this->order() > other.order() ? other._c : this->_c;
        for (std::size_t i = 0; i < smaller.size(); ++i) {
            *(bigger.rbegin() + i) += *(smaller.rbegin() + i);
        }
        return polynomial(reduce(bigger));
    }
    polynomial<T> half() const
    {
        std::vector<T> c(_c.size());
        for (std::size_t i = 0; i < c.size(); ++i) {
            c.push_back(::half(_c[i]));
        }
        return polynomial(reduce(c));
    }
    bool operator==(const polynomial& other) const
    {
        return equal(_c, other._c);
    }
    bool operator!=(const polynomial& other) const
    {
        return !(*this == other);
    }
    bool operator <(const polynomial& other) const
    {
        if (this->order() < other.order()) return true;
        if (this->order() > other.order()) return false;
        for (std::size_t i = 0; i < this->order(); ++i) {
            if (_c[i] < other._c[i]) return true;
            if (_c[i] > other._c[i]) return false;
        }
        return false;
    }
    bool operator >(const polynomial& other) const
    {
        if (this->order() > other.order()) return true;
        if (this->order() < other.order()) return false;
        for (std::size_t i = 0; i < this->order(); ++i) {
            if (_c[i] > other._c[i]) return true;
            if (_c[i] < other._c[i]) return false;
        }
        return false;
    }
    bool operator>=(const polynomial& other) const
    {
        return !(*this < other);
    }
    bool operator<=(const polynomial& other) const
    {
        return !(*this > other);
    }
    void p() const
    {
        print(_c);
    }
private:
    std::vector<T> _c;
};

template <Real R>
void swap(polynomial<R>& a, polynomial<R>& b)
{
    polynomial<R> c = a;
    a = b;
    b = c;
}

template <Real R> inline
R largest_doubling(R a, R b)
{
    // 事前条件: b != 0
    while (a - b >= b) b = b + b;
    return b;
}

template <Real R> inline
R remainder(R a, R b)
{
    // 事前条件: b != 0
    if (a < b) return a;
    R c = largest_doubling(a, b);
    a = a - c;
    while (c != b) {
        c = c.half();
        if (c <= a) a = a - c;
    }
    return a;
}

template <Real R> inline
polynomial<R> gcd(polynomial<R> a, polynomial<R> b)
{
    while (b != polynomial<R>(0)) {
        using std::swap;
        a = remainder(a, b);
        swap(a, b);
    }
    return polynomial<R>(a);
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
    std::vector<int> c1 = { 16, -56, -88, 278, 105};
    std::vector<int> c2 = { 16, -64, -44, 232, 70};
    polynomial<int> p1(c1);
    polynomial<int> p2(c2);
    auto p3 = gcd(p1, p2);
    p3.p();

    return 0;
}