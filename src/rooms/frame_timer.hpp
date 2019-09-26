#pragma once

#include <chrono>

class FrameTimer {
public:
    explicit FrameTimer(int fps);
    double delta() const;
    int operator()();

private:
    using Clock = std::chrono::high_resolution_clock;

    const double _delta;
    long long _lastFrame;
    Clock::time_point _startTime;
    Clock::duration _frameDuration;
};
