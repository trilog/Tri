// ****************************************************************************
// * DLine: This is a data structure that behaves like a 2D-vector.           *
// ****************************************************************************

#pragma once

#include "DPoint.h"

class DLine
{
    public:
               DLine      ();
               DLine      (DPoint& _p1, DPoint& _p2);
               DLine      (SDL_Point& _p1, SDL_Point& _p2);
               DLine      (int x1, int y1, int x2, int y2);
        int    render     (SDL_Renderer* renderer, SDL_Color& color);
        bool   operator== (const DLine& rhs) { return ((p1 == rhs.p1) && (p2 == rhs.p2)); }
        bool   operator!= (const DLine& rhs) { return !operator==(rhs); }
        DLine& operator+= (const DPoint& rhs);
        DLine& operator-= (const DPoint& rhs);
        int    dot        (DLine& rhs);
        int    perpDot    (DLine& rhs);
        int    crossMag   (DLine& rhs);
        float  magnitude  () { return sqrt((float) dot(*this)); }
        int    xMagnitude () { return p2.x - p1.x; }
        int    yMagnitude () { return p2.y - p1.y; }
        float  theta      () { return atan2((float) (p2.y - p1.y), (float) (p2.x - p1.x)); }
        bool   intersect  (DLine& bLine, DPoint* = NULL);
        bool   clipLine   (DLine& bLine) { return intersect(bLine, &p2); }
        DLine  vector     ();
        DLine  perp       ();
        DPoint p1;
        DPoint p2;
};

// **************** Global Operators **********************

inline DLine operator+(DLine lhs, const DPoint& rhs)
{
    lhs += rhs;
    return lhs;
}

inline DLine operator-(DLine lhs, const DPoint& rhs)
{
    lhs -= rhs;
    return lhs;
}
