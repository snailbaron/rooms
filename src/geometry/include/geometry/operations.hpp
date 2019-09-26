#pragma once

#include "geometry/matrix.hpp"
#include "geometry/point.hpp"
#include "geometry/util.hpp"
#include "geometry/vector.hpp"

template <class U, class V, class = enable_if_have_common_type_t<U, V>>
auto operator-(const Point<U>& lhs, const Point<V>& rhs)
{
    return Vector<std::common_type_t<U, V>>{lhs.x - rhs.x, lhs.y - rhs.y};
}

template <class U, class V, class = enable_if_have_common_type_t<U, V>>
auto operator*(const Matrix<U>& matrix, const Vector<V>& vector)
{
    return Vector<std::common_type_t<U, V>>{
        matrix(0, 0) * vector.x + matrix(0, 1) * vector.y,
        matrix(1, 0) * vector.x + matrix(1, 1) * vector.y
    };
}
