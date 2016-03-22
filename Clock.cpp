#include "Clock.h"

Clock::Clock(){}

void Clock::start()
{
    m_started = true;
    m_ticksAtStart = SDL_GetTicks();
}

void Clock::stop()
{
    m_started = false;
}

bool Clock::started()
{
    return m_started;
}

int Clock::getElapsedTime()
{
    if (m_started)
    {
        return SDL_GetTicks() - m_ticksAtStart;
    }

    return 0;
}

int Clock::restart()
{
    int elapsedTime = getElapsedTime();
    start();
    return elapsedTime;
}
