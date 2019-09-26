#include "config.hpp"
#include "view.hpp"

View::View(const Field& field)
    : _fieldView(field)
    , _window(nullptr, SDL_DestroyWindow)
{
    _window.reset(SDL_CreateWindow(
        config().windowTitle.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        config().windowWidth,
        config().windowHeight,
        0));
}

void View::draw()
{
    auto windowSurface = SDL_GetWindowSurface(_window.get());
    _fieldView.draw(windowSurface);

    SDL_UpdateWindowSurface(_window.get());
}