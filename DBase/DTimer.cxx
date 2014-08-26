#include "DTimer.h"

// **************** Con/Destructors ***********************

DTimer::DTimer():
startTicks(0), pauseTicks(0)
{
}

DTimer::~DTimer()
{
}

// **************** start *********************************

Uint32 DTimer::start(Uint32 override)
{
    if (override > 0) startTicks = override;
    else startTicks = SDL_GetTicks();
    pauseTicks = 0;
    return startTicks;
}

// **************** pause *********************************

Uint32 DTimer::pause(Uint32 override)
{
    if (startTicks > 0)
    {
        if (override > 0) pauseTicks = override;
        else pauseTicks = SDL_GetTicks();
        return pauseTicks;
    }
    else return 0;
}

// **************** unpause *******************************

Uint32 DTimer::unpause()
{
    if (pauseTicks > 0)
    {
        Uint32 pauseDuration = SDL_GetTicks() - pauseTicks;
        startTicks += pauseDuration;
        return pauseDuration;
    }
    else return 0;
}

// **************** stop **********************************

Uint32 DTimer::stop()
{
    startTicks = 0;
    pauseTicks = 0;
    return SDL_GetTicks();
}

// **************** elapsed *******************************

Uint32 DTimer::elapsed()
{
    if (startTicks > 0) return SDL_GetTicks() - startTicks;
    else return 0;
}


