#pragma once

#include "field.hpp"
#include "field_view.hpp"

#include <SDL2/SDL.h>

#include <memory>

class View {
public:
    View(const Field& field);

    void draw();

private:
    FieldView _fieldView;
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> _window;
};
