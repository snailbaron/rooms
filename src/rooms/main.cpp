#include "config.hpp"
#include "frame_timer.hpp"
#include "field.hpp"
#include "view.hpp"
#include "geometry.hpp"

#ifdef _WIN32
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main(int /*argc*/, char* argv[])
{
    const auto testLevelPath =
        fs::absolute(argv[0]).parent_path() / "data" / "levels" / "test.lev";
    std::cerr << "test level path: '" << testLevelPath << "'\n";

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    auto field = Field{};
    field.level.loadFromFile(testLevelPath);
    field.heroBody.position = {7.5f, 1.5f};
    field.heroBody.rotation = geometry::makeRotation(0.7f);

    auto view = View{field};

    auto frameTimer = FrameTimer{config().gameFps};
    while (view.isAlive()) {
        view.processInput();

        auto framesPassed = frameTimer();
        if (framesPassed > 0) {
            for (auto i = framesPassed; i > 0; i--) {
                field.update(frameTimer.delta());
            }

            view.update(frameTimer.delta() * framesPassed);
            view.draw();
        }
        frameTimer.relax();
    }

    SDL_Quit();

    return 0;
}
