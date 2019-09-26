#pragma once

#include "level.hpp"
#include "geometry.hpp"

struct HeroControls {
    float moveForward = 0;
    float moveRight = 0;
    float turnLeft = 0;
    bool shoot = false;
};

struct Body {
    void update(float delta);

    Point<float> position;
    Vector<float> velocity;
    Matrix<float> rotation;
};

class Field {
public:
    void update(float delta);

    Level level;
    Body heroBody;
    HeroControls heroControls;
};
