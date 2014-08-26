#include "DPoint.h"
#include <cmath>
#include <utility>

// **************** Con/Destructors ***********************

DPoint::DPoint():
x(0), y(0)
{
}

DPoint::DPoint(SDL_Point point):
x(point.x), y(point.y)
{
}

DPoint::DPoint(int _x, int _y):
x(_x), y(_y)
{
}

SDL_Point DPoint::sdl()
{
    SDL_Point point = { x, y };
    return point;
}

// **************** Arithmetic Operators ******************

DPoint& DPoint::operator+=(const DPoint& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

DPoint& DPoint::operator-=(const DPoint& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

void DPoint::set(int _x, int _y)
{
    x = _x;
    y = _y;
}

// **************** Operations ****************************

void DPoint::rotate(DPoint& focus, float& theta)
{
    float x_ = (float) (x - focus.x);
    float y_ = (float) (y - focus.y);
    x = (int) ((x_ * cos(theta)) - (y_ * sin(theta)));
    y = (int) ((y_ * cos(theta)) + (x_ * sin(theta)));
}

// **************** render ********************************

int DPoint::render(SDL_Renderer* renderer, SDL_Color& color, int markerSize)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    if (markerSize > 1)
    {
        // TODO: Allow for accurate rendering of even number markerSizes
        SDL_Rect rect = { x - (markerSize - 1)/2, y - (markerSize - 1)/2, markerSize, markerSize };
        return SDL_RenderFillRect(renderer, &rect);
    }
    else return SDL_RenderDrawPoint(renderer, x, y);
}

int DPoint::renderCross(SDL_Renderer* renderer, SDL_Color& color, int markerSize)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x - markerSize/2, y, x + markerSize/2, y);
    return SDL_RenderDrawLine(renderer, x, y - markerSize/2, x, y + markerSize/2);
}


