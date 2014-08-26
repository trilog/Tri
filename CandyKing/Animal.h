#pragma once

#include <vector>
using std::vector;

#include <SDL.h>

#include "DTexture.h"
#include "DTimer.h"
#include "DPolygon.h"
#include "DSoundManager.h"

enum AnimalState { asStanding, asWalking, asEating, asDying, asDead };

class Animal
{
    public:
                     Animal          ();
        void         setImage        (DTexture* _texture, int x = 0, int y = 0);
        void         addSolids       (vector<DPolygon*> solidList)     { solidShapes = solidList; }
        void         render          ();
        inline void  setPosition     (int x, int y)                    { pos.set(x, y); }
        void         setDestination  (DPoint& point);
        inline void  setMaxVelocity  (float _maxVelocity = 10)         { maxVelocity = _maxVelocity; }
        inline bool  coincident      ()                                { return pos == dest; }
        float        calcTheta       ();
        float        getTheta        ()                                { return theta; }
        float        getDistance     ();
        void         setClip         (string name, int x, int y, int w, int h, int focusX = 0, int focusY = 0);
        void         showHitBox      (bool _hitBoxShown = true)        { hitBoxShown = _hitBoxShown; }
        void         showVectors     (bool _vectorsShown = true)       { vectorsShown = _vectorsShown; }
        bool         hit             (int x, int y);
        void         renderPoly      (SDL_Renderer* renderer)          { polygon.render(renderer); }
        int          kill            ();
        bool         isDead          () const                          { return state == asDead; }
        void         setSoundManager (DSoundManager* _soundManager)    { soundManager = _soundManager; }
        void         setState        (AnimalState _state = asStanding) { state = _state; }
        void         stateDead       ();
        void         stateStanding   ();
        void         stateWalking    ();
        void         stateDying      ();
        void         stateEating     ();
    private:
        DTimer timer;
        DSoundManager* soundManager;
        DTexture* texture;
        AnimalState state;
        vector<ClipInfo> clips;
        size_t currentClip;
        SDL_RendererFlip flip;
        DPoint    pos;
        DPoint    dest;
        DPoint    entry;
        DPolygon  polygon;
        vector<DPolygon*> solidShapes;
        DLine     journey;
        bool      hitBoxShown;
        bool      vectorsShown;
        float     maxVelocity;
        int       maxPoints;
        float     theta;
        float     velocity;
};
