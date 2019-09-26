#pragma once

#include "field.hpp"
#include "geometry.hpp"

#include <SDL2/SDL.h>

class FieldView {
public:
    FieldView(const Field& field);

    void draw(SDL_Surface* surface);

private:
    Point<int> globalPoint(const Point<int>& localPoint) const;

    const Field& _field;

    Point<int> _position = {10, 10};
    Vector<int> _size = {800, 600};

    Vector<int> _resolution = {300, 100};
};
