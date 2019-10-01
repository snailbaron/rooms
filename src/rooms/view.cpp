#include "config.hpp"
#include "view.hpp"

View::View(Field& field)
    : _fieldView(field)
    , _window(nullptr, SDL_DestroyWindow)
{
    _window.reset(SDL_CreateWindow(
        config().windowTitle.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        config().windowWidth,
        config().windowHeight,
        //SDL_WINDOW_FULLSCREEN_DESKTOP |
            //SDL_WINDOW_INPUT_GRABBED |
            SDL_WINDOW_BORDERLESS
    ));

    SDL_SetRelativeMouseMode(SDL_TRUE);

    int windowWidth;
    int windowHeight;
    SDL_GetWindowSize(_window.get(), &windowWidth, &windowHeight);

    float fov = 0.7f;
    float vertFov = fov * windowHeight / windowWidth;

    _fieldView
        .position(0, 0)
        .size(windowWidth, windowHeight)
        .resolution(windowWidth, windowHeight)
        .fov(fov, vertFov);
}

bool View::isAlive() const
{
    return _isAlive;
}

void View::processInput()
{
    if (!_isAlive) {
        return;
    }

    for (SDL_Event event; SDL_PollEvent(&event); ) {
        if (event.type == SDL_QUIT) {
            _isAlive = false;
            return;
        } else {
            _fieldView.processInputEvent(event);
        }
    }
}

void View::update(float delta)
{
    _fieldView.update(delta);
}

void View::draw()
{
    auto windowSurface = SDL_GetWindowSurface(_window.get());
    auto windowRect = SDL_Rect{0, 0, 0, 0};
    SDL_GetWindowSize(_window.get(), &windowRect.w, &windowRect.h);
    SDL_FillRect(
        windowSurface,
        &windowRect,
        SDL_MapRGB(windowSurface->format, 30, 30, 30));

    _fieldView.draw(windowSurface);

    SDL_UpdateWindowSurface(_window.get());
}
