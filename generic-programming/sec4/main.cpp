#include <iostream>
#include <utility>

typedef std::size_t line_segment;

inline line_segment half(line_segment n)
{
    return n >> 1;
}

inline line_segment segment_remainder(line_segment a, line_segment b)
{
    while (b < a) a -= b;
    return a;
}

inline line_segment fast_segment_remainder(line_segment a, line_segment b)
{
    if (a <= b) return a;
    if (a - b <= b) return a - b;
    a = fast_segment_remainder(a, b + b);
    if (a <= b) return a;
    return a - b;
}

inline line_segment fast_segment_remainder1(line_segment a, line_segment b)
{
    // 事前条件: b != 0
    if (a < b) return a;
    if (a - b < b) return a - b;
    a = fast_segment_remainder(a, b + b);
    if (a < b) return a;
    return a - b;
}

line_segment largest_doubling(line_segment a, line_segment b)
{
    // 事前条件: b != 0
    while (a - b >= b) b = b + b;
    return b;
}

line_segment remainder(line_segment a, line_segment b)
{
    // 事前条件: b != 0
    if (a < b) return a;
    line_segment c = largest_doubling(a, b);
    a = a - c;
    while (c != b) {
        c = half(c);
        if (c <= a) a -= c;
    }
    return a;
}

line_segment gcm0(line_segment a, line_segment b)
{
    while (a != b) {
        a = fast_segment_remainder1(a, b);
        std::swap(a, b);
    }
    return a;
}

typedef std::size_t integer;

integer quotient(line_segment a, line_segment b)
{
    // 事前条件: b != 0
    if (a < b) return integer(a);
    line_segment c = largest_doubling(a, b);
    integer n(1);
    a -= c;
    while (c != b) {
        c = half(c); n = n + n;
        if (c <= a) {
            a -= c; n = n + 1;
        }
    }
    return n;

}

std::pair<integer, line_segment> quotient_remainder(line_segment a, line_segment b)
{
    // 事前条件: b != 0
    if (a < b) return {integer(a), a};
    line_segment c = largest_doubling(a, b);
    integer n(1);
    a -= c;
    while (c != b) {
        c = half(c); n = n + n;
        if (c <= a) {
            a -= c; n = n + 1;
        }
    }
    return { n, a };

}

int main(int argc, char* argv)
{
    const line_segment a = 45;
    const line_segment b = 6;
    const auto p = quotient_remainder(a, b);

    std::cout << p.first << std::endl;
    std::cout << p.second << std::endl;
    return 0;
}
