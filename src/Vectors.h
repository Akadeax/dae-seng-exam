#pragma once

#include <cstdint>
#include <iostream>

template <typename T>
struct Vector2
{
    T x{};
    T y{};

    Vector2() {}
    Vector2(T x, T y) : x{ x }, y{ y } {}

    void Print()
    {
        std::cout << "(" << x << ", " << y << ")\n";
    }
};

typedef int32_t Vector2i_t;
typedef int64_t Vector2l_t;
typedef float Vector2f_t;
typedef Vector2<Vector2i_t> Vector2i;
typedef Vector2<Vector2l_t> Vector2l;
typedef Vector2<Vector2f_t> Vector2f;
