#include "DPolygon.h"
#include <cmath>

// **************** Constructor ***************************

DPolygon::DPolygon():
open(false)
{
}

// **************** set ***********************************

void DPolygon::set(ClipInfo& clip, DPoint& _pos, SDL_RendererFlip flip)
{
    SDL_Rect rect = clip.clip;
    pos = _pos;
    focus = clip.focus;
    if (flip == SDL_FLIP_VERTICAL) focus.y = clip.clip.h - clip.focus.y;
    originalPoints.clear();
    originalPoints.emplace_back(pos.x,          pos.y);
    originalPoints.emplace_back(pos.x + rect.w, pos.y);
    originalPoints.emplace_back(pos.x + rect.w, pos.y + rect.h);
    originalPoints.emplace_back(pos.x,          pos.y + rect.h);
    reset();
}

// **************** reset *********************************

void DPolygon::reset()
{
    rotatedPoints = originalPoints;
    enclosePoints();
}

// **************** enclosePoints *************************

void DPolygon::enclosePoints()
{
    int minX = rotatedPoints.front().x;
    int maxX = rotatedPoints.front().x;
    int minY = rotatedPoints.front().y;
    int maxY = rotatedPoints.front().y;
    for (DPoint& point: rotatedPoints)
    {
        if (point.x < minX) minX = point.x;
        if (point.x > maxX) maxX = point.x;
        if (point.y < minY) minY = point.y;
        if (point.y > maxY) maxY = point.y;
    }
    boundingBox.x = minX;
    boundingBox.y = minY;
    boundingBox.w = maxX - minX;
    boundingBox.h = maxY - minY;
}

// **************** addPoint ******************************

void DPolygon::addPoint(int x, int y)
{
    originalPoints.emplace_back(x, y);
    reset();;
}

void DPolygon::addPoint(SDL_Point& point)
{
    originalPoints.push_back(point);
    reset();
}

void DPolygon::addPoint(DPoint& point)
{
    originalPoints.push_back(point);
    reset();
}

// **************** translate *****************************

void DPolygon::translate(int x, int y)
{
    for (DPoint& it: rotatedPoints)
    {
        it.x += x;
        it.y += y;
    }
    focus.x += x;
    focus.y += y;
}

// **************** rotate ********************************

void DPolygon::rotate(float angle)
{
    for (DPoint& it: rotatedPoints) rotate(it, angle); 
}

void DPolygon::rotate(DPoint& point, float angle)
{
    float x = (float) (point.x - focus.x - pos.x);
    float y = (float) (point.y - focus.y - pos.y);
    point.x = (int) (((x * cos(angle)) - (y * sin(angle)))) + pos.x;
    point.y = (int) (((y * cos(angle)) + (x * sin(angle)))) + pos.y;
}

// **************** absoluteAngle *************************

void DPolygon::absoluteAngle(float angle)
{
    reset();
    rotate(angle);
    enclosePoints();
}

// **************** checkBounds ***************************

bool DPolygon::checkBounds(int x, int y)
{
    if (x < boundingBox.x) return false;
    if (x > boundingBox.x + boundingBox.w) return false;
    if (y < boundingBox.y) return false;
    if (y > boundingBox.y + boundingBox.h) return false;
    return true;
}

// **************** windingNumber *************************
/*
int DPolygon::windingNumber(int x, int y)
{
    // Algorithm from http://geomalgorithms.com/a03-_inclusion.html Accessed 20 Feb 2014
    SDL_Point mouse = { x, y };
    list<SDL_Point> temp = rotatedPoints;
    temp.push_back(rotatedPoints.front());
    int wind = 0;
    int points = rotatedPoints.size();
    for(int point = 0; point < points; ++point)
    {
        if (temp.at(point).y <= mouse.y)
        {
            if (temp.at(point + 1).y > mouse.y) // Going up
            {
                if (triangleArea(temp.at(point), temp.at(point + 1), mouse) > 0) ++wind;
            }
        }
        else
        {
            if (temp.at(point + 1).y <= mouse.y) // Going down
            {
                if (triangleArea(temp.at(point), temp.at(point + 1), mouse) < 0) --wind;
            }
        }
    }
    return wind;
}
*/
// **************** hit ***********************************

bool DPolygon::hit(int x, int y)
{
    if (open) return false;
    if (rotatedPoints.size() < 3) return false;
//    if (!checkBounds(x, y)) return false;
    DLine line (boundingBox.x - 10, y, x, y);
    if (intersections(line) % 2 == 1) return true;
    //if (abs(windingNumber(x, y)) % 2 == 1) return true;
    return false;
}

// **************** render ********************************

void DPolygon::render(SDL_Renderer* renderer, SDL_Color& color)
{
    if (rotatedPoints.empty()) return;
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(renderer, &boundingBox);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    list<DPoint>::iterator prevPoint = rotatedPoints.end();
    for (list<DPoint>::iterator point = rotatedPoints.begin(); point != rotatedPoints.end(); ++point)
    {
        if (prevPoint != rotatedPoints.end()) SDL_RenderDrawLine(renderer, prevPoint->x, prevPoint->y, point->x, point->y);
        prevPoint = point;
    }
    if (!open) SDL_RenderDrawLine(renderer, rotatedPoints.front().x, rotatedPoints.front().y, rotatedPoints.back().x, rotatedPoints.back().y);
}

void DPolygon::render(SDL_Renderer* renderer)
{
    if (rotatedPoints.empty()) return;
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    list<DPoint>::iterator prevPoint = rotatedPoints.end();
    for (list<DPoint>::iterator point = rotatedPoints.begin(); point != rotatedPoints.end(); ++point)
    {
        if (prevPoint != rotatedPoints.end()) SDL_RenderDrawLine(renderer, prevPoint->x, prevPoint->y, point->x, point->y);
        prevPoint = point;
    }
    if (!open) SDL_RenderDrawLine(renderer, rotatedPoints.front().x, rotatedPoints.front().y, rotatedPoints.back().x, rotatedPoints.back().y);
}

void DPolygon::renderPoints(SDL_Renderer* renderer, SDL_Color& color)
{
    pos.render(renderer, color, 5);
    focus.renderCross(renderer, color, 8);
}

// **************** triangleArea **************************

float DPolygon::triangleArea(DPoint& p0, DPoint& p1, DPoint& p2)
{
    /* 
    Algorithm from http://geomalgorithms.com/a01-_area.html Accessed 20 Feb 2014
    < 0 area for clockwise points
    = 0 area for colinear points
    > 0 area for counterclockwise points
    if p1.y > p0.y positive results mean p2 lies to the right, negative to the left
    if p1.y < p0.y positive results mean p2 lies to the left, negative to the right
    */
    return 0.5 * ((float) (((p1.x - p0.x) * (p2.y - p0.y)) - ((p2.x - p0.x) * (p1.y - p0.y))));
}

unsigned int DPolygon::intersections(DLine& line, DPoint* clipPoint)
{
    unsigned int cross = 0;
    list<DPoint>::iterator prevPoint = rotatedPoints.end();
    for (list<DPoint>::iterator point = rotatedPoints.begin(); point != rotatedPoints.end(); ++point)
    {
        if (prevPoint != rotatedPoints.end()) 
        {
            DLine polyEdge(*prevPoint, *point);
            if (line.intersect(polyEdge, clipPoint)) ++cross;
        }
        prevPoint = point;
    }
    if (!open)
    {
        DLine polyEdge(rotatedPoints.back(), rotatedPoints.front());
        if (line.intersect(polyEdge, clipPoint)) ++cross;
    }
    return cross;
}

bool DPolygon::clip(DPolygon& poly)
{
    list<DPoint>::iterator prevPoint = rotatedPoints.end();
    for (list<DPoint>::iterator point = rotatedPoints.begin(); point != rotatedPoints.end(); ++point)
    {
        if (prevPoint != rotatedPoints.end()) 
        {
            DLine polyEdge(*prevPoint, *point);
            if (poly.intersections(polyEdge) > 0) return true;
        }
        prevPoint = point;
    }
    if (!open)
    {
        DLine polyEdge(rotatedPoints.back(), rotatedPoints.front());
        if (poly.intersections(polyEdge) > 0) return true;
    }
    return false;   
}

// **************** Simple Shapes *************************

void DPolygon::makeRectangle(int x, int y, int w, int h)
{
    originalPoints.clear();
    addPoint(x, y);
    addPoint(x + w, y);
    addPoint(x + w, y + h);
    addPoint(x,     y + h);
    setFocus(w/2,   h/2);
}

void DPolygon::makeEllipse(int x, int y, int w, int h)
{
    // TODO: Make it more elliptical
    originalPoints.clear();
    int centerX = x + w/2;
    if (w % 2 == 1) ++centerX;
    int centerY = y + h/2;
    if (h % 2 == 1) ++centerY;
    setFocus(centerX, centerY);
    // (x/w)^2 + (y/h)^2 = 1
    float a = ((float) w)/2.0;
    float b = ((float) h)/2.0;
    int slices = 20;
    if (w >= h) // Figure out whether or not x is the major axis
    {
        float term1 = b * b;
        float term2 = (b * b)/(a * a);
        addPoint(x, centerY);
        float sliceWidth = ((float) w)/((float) slices);
        for (int slice = 1; slice < slices; ++slice)
        {
            float xVal = ((float) slice) * sliceWidth - a;
            float yVal = sqrt(term1 - (term2 * xVal * xVal));
            addPoint(xVal + centerX, yVal + centerY);
        }
        addPoint(x + w, centerY);
        for (int slice = slices - 1; slice > 0; --slice)
        {
            float xVal = ((float) slice) * sliceWidth - a;
            float yVal = sqrt(term1 - (term2 * xVal * xVal));
            addPoint(xVal + centerX, -yVal + centerY);
        }
    }
    else
    {
        float term1 = a * a;
        float term2 = (a * a)/(b * b);
        addPoint(centerX, y);
        float sliceHeight = ((float) h)/((float) slices);
        for (int slice = 1; slice < slices; ++slice)
        {
            float yVal = ((float) slice) * sliceHeight - b;
            float xVal = sqrt(term1 - (term2 * yVal * yVal));
            addPoint(xVal + centerX, yVal + centerY);
        }
        addPoint(centerX, y + h);
        for (int slice = slices - 1; slice > 0; --slice)
        {
            float yVal = ((float) slice) * sliceHeight - b;
            float xVal = sqrt(term1 - (term2 * yVal * yVal));
            addPoint(-xVal + centerX, yVal + centerY);
        }
    }
}
