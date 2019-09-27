#pragma once

#include <SDL2/SDL.h>

#include <string>

struct Config {
    std::string windowTitle = "Rooms";
    int windowWidth = 1024;
    int windowHeight = 768;
    int gameFps = 60;
    float mouseSensitivity = 0.003f;

    SDL_Keycode moveForwardKey = SDLK_w;
    SDL_Keycode moveBackwardKey = SDLK_s;
    SDL_Keycode moveLeftKey = SDLK_a;
    SDL_Keycode moveRightKey = SDLK_d;
};

inline Config& config()
{
    static Config config;
    return config;
}
