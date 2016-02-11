#pragma once

#include <list>
using std::list;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <string>
using std::string;

#include <SDL.h>

#include "DImage.h"
#include "Animal.h"
#include "DSoundManager.h"

class Shepherd
{
    public:
                Shepherd (SDL_Renderer* _renderer, DSoundManager* _soundManager = NULL);
               ~Shepherd ();
        bool    load     (string animalName, string fileName);
        Animal* spawn    (string animalName, int x = 0, int y = 0);
        void    render   ();
        void    prune    ();
        void    checkHit (int mouseX, int mouseY);
        void    addSolid (DPolygon* poly) { solidShapes.push_back(poly); }
        int     getScore () const { return score; }
        void    pause    ();
        void    unpause  ();
    private:
        map<string, Animal> cloningPen;
        map<string, DImage> textures;
        list<Animal>        clones;
        list<Animal>        dyingClones;
        vector<DPolygon*>   solidShapes;
        SDL_Renderer*       renderer;
        DSoundManager*      soundManager;
        int                 score;
};
