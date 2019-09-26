#pragma once

#include "level.hpp"
#include "geometry.hpp"

struct Field {
    Level level;
    Point<float> heroPosition;
    Vector<float> heroDirection;
};
