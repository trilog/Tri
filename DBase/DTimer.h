#ifndef __DTIMER__
#define __DTIMER__

#include <SDL.h>

class DTimer
{
    public:
                DTimer();
               ~DTimer();
        Uint32  start(Uint32 override = 0);
        Uint32  pause(Uint32 override = 0);
        Uint32  unpause();
        Uint32  stop();
        Uint32  elapsed();
    private:
        Uint32 startTicks;
        Uint32 pauseTicks;
};

#endif /* DTimer.h */
