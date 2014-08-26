#include "DLine.h"

// **************** Con/Destructors ***********************

DLine::DLine()
{
}

DLine::DLine(int x1, int y1, int x2, int y2):
p1(DPoint(x1, y1)), p2(DPoint(x2, y2))
{
}

DLine::DLine(SDL_Point& _p1, SDL_Point& _p2):
p1(DPoint(_p1)), p2(DPoint(_p2))
{
}

DLine::DLine(DPoint& _p1, DPoint& _p2):
p1(_p1), p2(_p2)
{
}

// **************** render ********************************

int DLine::render(SDL_Renderer* renderer, SDL_Color& color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    p1.render(renderer, color, 7);
    p2.render(renderer, color, 3);
    return SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
}

// **************** Arithmetic Operators ******************

DLine& DLine::operator+=(const DPoint& rhs)
{
    p1 += rhs;
    p2 += rhs;
    return *this;
}

DLine& DLine::operator-=(const DPoint& rhs)
{
    p1 -= rhs;
    p2 -= rhs;
    return *this;
}

// **************** Vector Operations *********************

DLine DLine::vector()
{
    DPoint origin(0, 0);
    DPoint p3 = p2 - p1;
    DLine line(origin, p3);
    return line;
}

int DLine::dot(DLine& rhs)
{
    DLine l1 = vector();
    DLine l2 = rhs.vector();
    return (l1.p2.x * l2.p2.x) + (l1.p2.y * l2.p2.y);
}

int DLine::perpDot(DLine& rhs)
{
    DLine l1 = perp().vector();
    DLine l2 = rhs.vector();
    return (l1.p2.x * l2.p2.x) + (l1.p2.y * l2.p2.y);
}

DLine DLine::perp()
{
    DLine l = vector();
    float x_ = l.p2.x;
    float y_ = l.p2.y;
    l.p2.x = -y_;
    l.p2.y = x_;
    l += p1;
    return l;
}
/*
bool DLine::clipLine(DLine& bLine, DPoint* clipPoint)
{
    int axb = crossMag(bLine);
    if (axb == 0) return false;
    DLine cLine(p1, bLine.p1);
    int cxb = cLine.crossMag(bLine);
    if (axb > 0)
    {
        if ((cxb < 0) || (cxb > axb)) return false;
    }
    else
    {
        if ((cxb > 0) || (cxb < axb)) return false;
    }
    return true;
}
*/

bool DLine::intersect(DLine& bLine, DPoint* clipPoint)
{
    // Algorithm from http://www.cplusplus.com/forum/beginner/49408/ Accessed 27 April 2014
    DLine cLine(p2, bLine.p2);
    int atb = perpDot(bLine);
    if (atb == 0) return false;
    int atc = perpDot(cLine);
    int btc = bLine.perpDot(cLine);
    if (atb > 0)
    {
        if (atc < 0)   return false;
        if (btc < 0)   return false;
        if (atc > atb) return false;
        if (btc > atb) return false;
    }
    else
    {
        if (atc > 0)   return false;
        if (btc > 0)   return false;
        if (atc < atb) return false;
        if (btc < atb) return false;
    }
    if (clipPoint != NULL)
    {
        float scale = 1.0 - ((float) btc)/((float) atb);
        int x = p1.x + rint(scale * ((float) xMagnitude()));
        int y = p1.y + rint(scale * ((float) yMagnitude()));
        clipPoint->set(x, y);
    }
    return true;
}

int DLine::crossMag(DLine& rhs)
{
    DPoint v1 = p2 - p1;
    DPoint v2 = rhs.p2 - rhs.p1;
    return (v1.x * v2.y) - (v2.x * v1.y);
}
