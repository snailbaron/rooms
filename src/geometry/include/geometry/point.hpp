#pragma once

#include "geometry/vector.hpp"

#include <ostream>
#include <type_traits>
#include <utility>

template <class T>
struct Point {
    Point() : x(), y() {}
    Point(T x, T y) : x(std::move(x)), y(std::move(y)) {}

    template <class U, class = std::enable_if_t<std::is_convertible_v<U, T>>>
    Point& operator+=(const Vector<U>& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    T x;
    T y;
};

template <class T>
std::ostream& operator<<(std::ostream& output, const Point<T>& point)
{
    return output << "(" << point.x << ", " << point.y << ")";
}
