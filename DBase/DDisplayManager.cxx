#include "DDisplayManager.h"
#include <iostream>
using std::cerr;
using std::endl;
#include <SDL.h>
#include <SDL_image.h>

// **************** Con/Destructors ***********************

DDisplayManager::DDisplayManager():
imgLegit(false), sdlLegit(false)
{
}

DDisplayManager::~DDisplayManager()
{
    if (imgLegit) IMG_Quit();
    if (sdlLegit) SDL_Quit();
}

// **************** init **********************************

bool DDisplayManager::init()
{
    sdlLegit = initSDL();
    imgLegit = initIMG();
    return isLegit();
}

bool DDisplayManager::initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "SDL did not initialize: " << SDL_GetError() << endl;
        sdlLegit = false;
        return false;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1")) cerr << "Warning VSync not enabled" << endl;
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) cerr << "Warning: linear texture filtering not enabled" << endl;
    return true;
}

bool DDisplayManager::initIMG()
{
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        cerr << "SDL_image did not initialize: " << IMG_GetError() << endl;
        return false;
    }
    return true;
}
