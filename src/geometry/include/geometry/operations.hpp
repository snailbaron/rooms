#pragma once

#include "geometry/internals/util.hpp"

#include "geometry/matrix.hpp"
#include "geometry/point.hpp"
#include "geometry/vector.hpp"

namespace geometry {

template <class U, class V,
    class = internals::enable_if_have_common_type_t<U, V>>
auto operator-(const Point<U>& lhs, const Point<V>& rhs)
{
    return Vector<std::common_type_t<U, V>>{lhs.x - rhs.x, lhs.y - rhs.y};
}

template <class U, class V,
    class = internals::enable_if_have_common_type_t<U, V>>
auto operator-(const Vector<U>& lhs, const Point<V>& rhs)
{
    return Vector<std::common_type_t<U, V>>{lhs.x - rhs.x, lhs.y - rhs.y};
}

template <class U, class V,
    class = internals::enable_if_have_common_type_t<U, V>>
auto operator*(const Matrix<U>& matrix, const Vector<V>& vector)
{
    return Vector<std::common_type_t<U, V>>{
        matrix(0, 0) * vector.x + matrix(0, 1) * vector.y,
        matrix(1, 0) * vector.x + matrix(1, 1) * vector.y
    };
}

} // namespace geometry
