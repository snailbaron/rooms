#pragma once

#include <SDL2/SDL.h>

class Widget {
public:
    virtual ~Widget() {}

    virtual void draw(SDL_Surface* screen) = 0;
    virtual bool contains(int x, int y) const = 0;

    virtual void onGetFocus() {}
    virtual void onLoseFocus() {}
    virtual void onPress() {}
    virtual void onRelease() {}
    virtual void onActivate() {}
};
