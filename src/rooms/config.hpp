#pragma once

#include <string>

struct Config {
    std::string windowTitle = "Rooms";
    int windowWidth = 1024;
    int windowHeight = 768;
    int gameFps = 60;
};

inline Config& config()
{
    static Config config;
    return config;
}
