#pragma once

#include "types.hpp"

#include <cmath>

struct ScreenSize {
    int x;
    int y;
};

struct ScreenRectangle {
    ScreenPoint origin;
    ScreenSize size;
};

inline ScreenPoint recalculatePoint(
    const ScreenPoint& sourcePoint,
    const ScreenSize& sourceSize,
    const ScreenSize& targetSize)
{
    return {
        static_cast<int>(
            std::round(1.f * targetSize.x * sourcePoint.x / sourceSize.x)),
        static_cast<int>(
            std::round(1.f * targetSize.y * sourcePoint.y / sourceSize.y))
    };
}
