#pragma once

#include <string>
using std::string;

#include <SDL.h>

#include "DImage.h"
#include "DPolygon.h"

class King
{
    public:
                      King        (SDL_Renderer* _renderer);
                     ~King        ();
        void          render      () { texture.render(pos.x, pos.y); }
        void          renderPoly  ();
        bool          load        (string fileName);
        void          moveCenter  (DPoint& point);
        const DPoint& getPosition () { return pos; }
        const DPoint& getFocus    () { return focus; }
        DPolygon*     getPoly     () { return &shape; }
        int           getHP       () { return hp; }
        void          takeDamage  (int damage = 1) { hp -= damage; }
    private:
        DPolygon shape;       
        SDL_Renderer* renderer;
        DImage texture;
        DPoint pos;
        DPoint focus;
        int hp;
};
