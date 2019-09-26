#pragma once

#include "field.hpp"

#include <optional>

class Game {
public:
    void start();

    void update(double delta);

private:
    std::optional<Field> _field;
};
