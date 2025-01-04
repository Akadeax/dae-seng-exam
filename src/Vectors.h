#pragma once

#include <cstdint>
#include <iostream>
#include <concepts>

template <typename T>
concept Arithmetic = requires(T a, T b) {
    // check if arithmetic operators are supported
    { a + b } -> std::same_as<T>;
    { a - b } -> std::same_as<T>;
    { a * b } -> std::same_as<T>;
    { a / b } -> std::same_as<T>;
};

template <Arithmetic T>
struct Vector2
{
    T x{};
    T y{};

    Vector2() {}
    Vector2(T x, T y) : x{ x }, y{ y } {}

    void Print()
    {
        tcout << "(" << x << ", " << y << ")\n";
    }

    double Distance2(Vector2<T> other)
    {
        Vector2<T> sub{ std::abs(x - other.x), std::abs(y - other.y) };
        return sub.x * sub.x + sub.y * sub.y;
    }
};

typedef int32_t Vector2i_t;
typedef Vector2<Vector2i_t> Vector2i;

typedef int64_t Vector2l_t;
typedef Vector2<Vector2l_t> Vector2l;

typedef float Vector2f_t;
typedef Vector2<Vector2f_t> Vector2f;
