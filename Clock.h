#ifndef CLOCK_HPP_INCLUDED
#define CLOCK_HPP_INCLUDED
#include "stdafx.h"

class Clock
{
public:
    Clock();

    void start();

    void stop();

    int getElapsedTime();

    int restart();

    bool started();

private:

    int m_ticksAtStart = 0;

    bool m_started = false;
};
#endif // CLOCK_HPP_INCLUDED
