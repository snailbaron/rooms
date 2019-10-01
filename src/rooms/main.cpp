#include "config.hpp"
#include "frame_timer.hpp"
#include "field.hpp"
#include "view.hpp"

#include <SDL2/SDL.h>

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

//constexpr char testLevel[] =
//    "##########\n"
//    "#.....#..#\n"
//    "#..O...#.#\n"
//    "#......#.#\n"
//    "#........#\n"
//    "#........#\n"
//    "#..#..o...\n"
//    "#.#.......\n"
//    "#.........\n"
//    "#####...##\n"
//;

int main(int /*argc*/, char* argv[])
{
    const auto testLevelPath =
        fs::absolute(argv[0]).parent_path() / "data" / "levels" / "test.lev";
    std::cerr << "test level path: '" << testLevelPath << "'\n";

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    auto field = Field{};
    field.level.loadFromFile(testLevelPath);
    field.heroBody.position = {7.5f, 1.5f};
    field.heroBody.rotation = makeRotation(0.7f);

    auto view = View{field};

    auto frameTimer = FrameTimer{config().gameFps};
    while (view.isAlive()) {
        view.processInput();

        auto framesPassed = frameTimer();
        if (framesPassed == 0) {
            continue;
        }

        for (auto i = framesPassed; i > 0; i--) {
            field.update(frameTimer.delta());
        }

        view.update(frameTimer.delta() * framesPassed);
        view.draw();
    }

    SDL_Quit();
}
