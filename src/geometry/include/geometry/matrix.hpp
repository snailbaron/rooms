#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <utility>
#include <type_traits>

template <class T>
class Matrix {
public:
    Matrix()
    {
        _values.fill({});
    }

    Matrix(T a00, T a01, T a10, T a11)
        : _values({
            std::move(a00), std::move(a01), std::move(a10), std::move(a11)})
    { }

    T& operator()(size_t i, size_t j)
    {
        assert(i >= 0 && i < 2 && j >= 0 && j < 2);
        return _values[2 * i + j];
    }

    const T& operator()(size_t i, size_t j) const
    {
        assert(i >= 0 && i < 2 && j >= 0 && j < 2);
        return _values[2 * i + j];
    }

    template <class U, class = std::enable_if_t<std::is_convertible_v<U, T>>>
    Matrix& operator*=(const Matrix<U>& rhs)
    {
        Matrix r;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                r(i, j) = (*this)(i, 0) * rhs(0, j) + (*this)(i, 1) * rhs(1, j);
            }
        }
        std::swap(_values, r._values);
        return *this;
    }

private:
    std::array<T, 4> _values;
};

template <class U, class T>
constexpr Matrix<U> cast(const Matrix<T>& matrix)
{
    return {
        static_cast<U>(matrix(0, 0)),
        static_cast<U>(matrix(0, 1)),
        static_cast<U>(matrix(1, 0)),
        static_cast<U>(matrix(1, 1))
    };
}

template <class U, class V>
auto operator*(const Matrix<U>& lhs, const Matrix<V>& rhs)
{
    auto result = cast<std::common_type_t<U, V>>(lhs);
    result *= rhs;
    return result;
}

template <class T>
Matrix<T> makeRotation(const T& angle)
{
    auto s = std::sin(angle);
    auto c = std::cos(angle);
    return {c, -s, s, c};
}
