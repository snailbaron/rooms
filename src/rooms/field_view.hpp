#pragma once

#include "field.hpp"
#include "geometry.hpp"
#include "screen_geometry.hpp"
#include "task.hpp"
#include "types.hpp"

#ifdef _WIN32
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

class FieldView {
public:
    FieldView(Field& field);

    void processInputEvent(const SDL_Event& event);
    void update(float delta);
    void draw(SDL_Surface* surface);

    FieldView& position(int x, int y)
    {
        _offset = {x, y};
        return *this;
    }

    FieldView& size(int x, int y)
    {
        _size = {x, y};
        return *this;
    }

    FieldView& resolution(int x, int y)
    {
        _resolution = {x, y};
        return *this;
    }

    FieldView& fov(float horizontal, float vertical)
    {
        _horizontalFovRatio = horizontal;
        _verticalFovRatio = vertical;
        return *this;
    }

private:
    static constexpr float _objectHeight = 2.f;

    ScreenPoint globalPoint(const ScreenPoint& localPoint) const;

    Field& _field;

    ScreenOffset _offset = {0, 0};
    ScreenSize _size = {1024, 768};
    ScreenSize _resolution = {1024, 768};
    float _horizontalFovRatio = 1.f;
    float _verticalFovRatio = 1.f;

    TaskPool _tasks;
    float _headHeight = 0;
};
