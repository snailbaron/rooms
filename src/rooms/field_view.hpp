#pragma once

#include "field.hpp"
#include "geometry.hpp"
#include "task.hpp"

#include <SDL2/SDL.h>

class FieldView {
public:
    FieldView(Field& field);

    void processInputEvent(const SDL_Event& event);
    void update(float delta);
    void draw(SDL_Surface* surface);

private:
    Point<int> globalPoint(const Point<int>& localPoint) const;

    Field& _field;

    Point<int> _position = {0, 0};
    Vector<int> _size = {1024, 768};

    Vector<int> _resolution = {1024, 768};

    TaskPool _tasks;
    float _headHeight = 0;
};
