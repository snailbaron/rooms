#include "config.hpp"
#include "frame_timer.hpp"
#include "field.hpp"
#include "view.hpp"

#include <SDL2/SDL.h>

constexpr char testLevel[] =
    "##########\n"
    "#.....#..#\n"
    "#..#.###.#\n"
    "#..###.#.#\n"
    "#.##...#.#\n"
    "#..###.#.#\n"
    "#....#...#\n"
    "#..###...#\n"
    "#........#\n"
    "##########\n"
;

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    auto field = Field{};
    field.level.loadFromString(testLevel);
    field.heroPosition = {7.5f, 1.5f};
    field.heroDirection = {-1, 1};

    auto view = View{field};

    auto frameTimer = FrameTimer{config().gameFps};
    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
            }
        }

        auto framesPassed = frameTimer();

        if (framesPassed > 0) {
            view.draw();
        }
    }

    SDL_Quit();
}
