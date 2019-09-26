#pragma once

#include <chrono>

class FrameTimer {
public:
    explicit FrameTimer(int fps);
    float delta() const;
    int operator()();

private:
    using Clock = std::chrono::high_resolution_clock;

    const float _delta;
    long long _lastFrame;
    Clock::time_point _startTime;
    Clock::duration _frameDuration;
};
