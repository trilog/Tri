// ****************************************************************************
// * DPoint: I needed a way to do more point operations than what SDL_Point   *
// * had come with.                                                           *
// ****************************************************************************

#pragma once

#include <SDL.h>

class DPoint
{
    public:
                   DPoint      ();
                   DPoint      (SDL_Point point);
                   DPoint      (int _x, int _y);
        SDL_Point  sdl         ();
        DPoint&    operator+=  (const DPoint& rhs);
        DPoint&    operator-=  (const DPoint& rhs);
        bool       operator==  (const DPoint& rhs) { return ((x == rhs.x) && (y == rhs.y)); }
        bool       operator!=  (const DPoint& rhs) { return !operator==(rhs); }
        void       rotate      (DPoint& focus, float& theta);
        int        render      (SDL_Renderer* renderer, SDL_Color& color, int markerSize = 1);
        int        renderCross (SDL_Renderer* renderer, SDL_Color& color, int markerSize = 5);
        void       set         (int _x, int _y);
        int x;
        int y;
};

// **************** Global Operators **********************
/*
DPoint& operator=(DPoint rhs)
{
    std::swap(rhs);
    return *this;
}
*/

inline DPoint operator+(DPoint lhs, const DPoint& rhs)
{
    lhs += rhs;
    return lhs;
}

inline DPoint operator-(DPoint lhs, const DPoint& rhs)
{
    lhs -= rhs;
    return lhs;
}
