#pragma once

#include "geometry/internals/util.hpp"

#include <cmath>
#include <ostream>
#include <type_traits>
#include <utility>

namespace geometry {

template <class T>
struct Vector {
    constexpr Vector() : x(), y() {}

    template <class U, class V, class = std::enable_if_t<
        std::is_convertible_v<U, T> && std::is_convertible_v<V, T>>>
    constexpr Vector(U x, V y)
        : x(std::move(x))
        , y(std::move(y))
    { }

    template <class U, class = internals::enable_if_convertible_t<U, T>>
    constexpr Vector(const Vector<U>& other)
        : x(other.x)
        , y(other.y)
    { }

    template <class U, class = internals::enable_if_convertible_t<U, T>>
    constexpr Vector(Vector<U>&& other)
        : x(std::move(other.x))
        , y(std::move(other.y))
    { }

    template <class U, class = internals::enable_if_convertible_t<U, T>>
    Vector& operator+=(const Vector<U>& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    template <class U, class = internals::enable_if_convertible_t<U, T>>
    Vector& operator-=(const Vector<U>& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    template <class S, class = internals::enable_if_convertible_t<S, T>>
    Vector& operator*=(const S& scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    template <class S, class = internals::enable_if_convertible_t<S, T>>
    Vector& operator/=(const S& scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    void normalize()
    {
        auto norm = sqrt(x * x + y * y);
        if (norm != 0) {
            x /= norm;
            y /= norm;
        }
    }

    void clip(const T& maxValue)
    {
        auto norm = sqrt(x * x + y * y);
        if (norm != 0 && maxValue < norm) {
            auto k = maxValue / norm;
            x *= k;
            y *= k;
        }
    }

    T x;
    T y;
};

template <class U, class V,
    class = internals::enable_if_have_common_type_t<U, V>>
constexpr auto operator+(const Vector<U>& lhs, const Vector<V>& rhs)
{
    return Vector<std::common_type_t<U, V>>{lhs.x + rhs.x, lhs.y + rhs.y};
}

template <class U, class V,
    class = internals::enable_if_have_common_type_t<U, V>>
constexpr auto operator-(const Vector<U>& lhs, const Vector<V>& rhs)
{
    return Vector<std::common_type_t<U, V>>{lhs.x - rhs.x, lhs.y - rhs.y};
}

template <class T, class S,
    class = internals::enable_if_have_common_type_t<T, S>>
constexpr auto operator*(const Vector<T>& vector, const S& scalar)
{
    Vector<std::common_type_t<T, S>> result = vector;
    result *= scalar;
    return result;
}

template <class T, class S,
    class = internals::enable_if_have_common_type_t<T, S>>
constexpr auto operator*(const S& scalar, const Vector<T>& vector)
{
    return operator*(vector, scalar);
}

template <class T, class S>
constexpr auto operator/(const Vector<T>& vector, const S& scalar)
{
    return Vector<std::common_type_t<T, S>>{
        vector.x / scalar, vector.y / scalar};
}

template <class U, class V>
constexpr auto dot(const Vector<U>& lhs, const Vector<V>& rhs)
{
    return static_cast<std::common_type_t<U, V>>(
        lhs.x * rhs.x + lhs.y * rhs.y);
}

template <class U, class V>
std::common_type_t<U, V> cross(const Vector<U>& lhs, const Vector<V>& rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

template <class T>
Vector<T> ort(const Vector<T>& vector)
{
    return {vector.y, -vector.x};
}

template <class T>
Vector<T> normalize(const Vector<T>& vector)
{
    auto result = vector;
    result.normalize();
    return result;
}

template <class T>
T norm(const Vector<T>& vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

template <class T>
Vector<T> reflect(const Vector<T>& vector, const Vector<T>& normal)
{
    return vector + 2 * dot(vector, normal) * normal;
}

template <class U, class T>
constexpr Vector<U> cast(const Vector<T>& vector)
{
    return {static_cast<U>(vector.x), static_cast<U>(vector.y)};
}

template <class T>
std::ostream& operator<<(std::ostream& output, const Vector<T>& vector)
{
    return output << "(" << vector.x << ", " << vector.y << ")";
}

} // namespace geometry
