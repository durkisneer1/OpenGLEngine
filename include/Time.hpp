#pragma once

#include <SDL.h>


namespace kn {
namespace time {

class Clock final {
public:
    Clock() = default;
    ~Clock() = default;

    double tick(int frameRate = 60);

private:
    double m_frameTime = 0.0;
    double m_targetFrameTime = 0.0;
    double m_deltaTime = 0.0;
    double m_frequency = SDL_GetPerformanceFrequency();
    double m_now = SDL_GetPerformanceCounter();
    double m_last = SDL_GetPerformanceCounter();
};

double getTicks();

}
}
