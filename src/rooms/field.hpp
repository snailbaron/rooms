#pragma once

#include "level.hpp"
#include "types.hpp"

struct HeroControls {
    bool moveForward = false;
    bool moveBackward = false;
    bool moveRight = false;
    bool moveLeft = false;
    float turnLeft = 0;
    bool shoot = false;
};

struct Body {
    void update(float delta);

    Point position;
    Vector velocity;
    Matrix rotation;
};

class Field {
public:
    void update(float delta);

    Level level;
    Body heroBody;
    HeroControls heroControls;
};
