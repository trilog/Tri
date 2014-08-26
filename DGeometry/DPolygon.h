// ****************************************************************************
// * DPolygon: You can make open or closed polygons                           *
// ****************************************************************************

#pragma once
#define _USE_MATH_DEFINES
#include <list>
using std::list;

#include <SDL.h>

#include "DTexture.h"
#include "DLine.h"

class DPolygon
{
    public:
                      DPolygon      ();
                      DPolygon      (ClipInfo& clip, DPoint& _pos, SDL_RendererFlip flip = SDL_FLIP_NONE) { set(clip, _pos, flip); }

        void          addPoint      (int x, int y);
        void          addPoint      (SDL_Point& point);
        void          addPoint      (DPoint& point);

        void          openShape     () { open = true; }
        bool          isOpen        () { return open; }
        inline void   reset         ();
        void          enclosePoints ();

        void          setFocus      (int x, int y)     { focus.set(x, y); }
        void          setFocus      (SDL_Point& point) { focus = point; }
        void          setFocus      (DPoint& point)    { focus = point; }
        void          moveFocus     (DPoint& point)    { translate(point - focus); }

        void          render        (SDL_Renderer* renderer);
        void          render        (SDL_Renderer* renderer, SDL_Color& color);
        void          renderPoints  (SDL_Renderer* renderer, SDL_Color& color);

        void          translate     (int x, int y);
        void          translate     (DPoint point) { translate(point.x, point.y); }
        void          translate     (SDL_Point& point) { translate(point.x, point.y); }
        void          rotate        (float angle = 0);
        void          rotate        (DPoint& point, float angle = 0);
        void          absoluteAngle (float angle = 0); 
        void          set           (ClipInfo& clip, DPoint& _focus, SDL_RendererFlip flip = SDL_FLIP_NONE);
        bool          hit           (int x, int y);
        bool          checkBounds   (int x, int y);
//        int           windingNumber (int x, int y);
        float         triangleArea  (DPoint& p1, DPoint& p2, DPoint& p3);
        unsigned int  intersections (DLine& line, DPoint* = NULL);
        bool          clip          (DLine& line) { return intersections(line, &line.p2) > 0; }
        bool          clip          (DPolygon& poly);
        list<DPoint>& getPoints  () { return rotatedPoints; }

        // ******** Simple Shapes
        void         makeRectangle (int x, int y, int w, int h);
        void         makeRectangle (SDL_Rect& rect) { makeRectangle(rect.x, rect.y, rect.w, rect.h); }
        void         makeEllipse   (int x, int y, int w, int h);
        void         makeEllipse   (SDL_Rect& rect) { makeEllipse(rect.x, rect.y, rect.w, rect.h); }
    private:
        list<DPoint> originalPoints;
        list<DPoint> rotatedPoints;
        DPoint focus;
        DPoint pos;
        SDL_Rect boundingBox;
        bool open;
};
