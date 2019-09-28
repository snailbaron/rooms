#pragma once

#include "geometry/point.hpp"
#include "geometry/vector.hpp"

#include <cmath>
#include <limits>

template <class T>
struct TraceResult {
    operator bool() const
    {
        return std::isfinite(distance);
    }

    T distance;
    Vector<T> normal;
};

template <class T>
TraceResult<T> traceCircle(
    const Point<T>& origin,
    const Vector<T>& lookDirection,
    const Point<T>& center,
    const T& r)
{
    auto d = cross(lookDirection, center - origin);
    if (std::abs(d) > r) {
        return {std::numeric_limits<T>::infinity(), {}};
    }

    auto centerToLineVector = d * ort(lookDirection);
    auto incomingVector = -std::sqrt(r * r - d * d) * lookDirection;
    auto radialVector = centerToLineVector + incomingVector;

    return {
        norm(center + radialVector - origin),
        normalized(radialVector)
    };
}
