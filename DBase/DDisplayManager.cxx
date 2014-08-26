#include "DDisplayManager.h"
#include <iostream>
using std::cerr;
using std::endl;
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// **************** Con/Destructors ***********************

DDisplayManager::DDisplayManager():
imgLegit(false), sdlLegit(false), ttfLegit(false)
{
}

DDisplayManager::~DDisplayManager()
{
    if (ttfLegit) TTF_Quit();
    if (imgLegit) IMG_Quit();
    if (sdlLegit) SDL_Quit();
}

// **************** init **********************************

bool DDisplayManager::initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "SDL did not initialize: " << SDL_GetError() << endl;
        sdlLegit = false;
        return sdlLegit;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1")) cerr << "Warning VSync not enabled" << endl;
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) cerr << "Warning: linear texture filtering not enabled" << endl;
    sdlLegit = true;
    return sdlLegit;
}

bool DDisplayManager::initIMG()
{
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        cerr << "SDL_image did not initialize: " << IMG_GetError() << endl;
        imgLegit = false;
        return imgLegit;
    }
    imgLegit = true;
    return imgLegit;
}

bool DDisplayManager::initTTF()
{
    if (TTF_Init() == -1)
    {
        cerr << "SDL_ttf did not initialize" << TTF_GetError() << endl;
        ttfLegit = false;
        return ttfLegit;
    }
    ttfLegit = true;
    return ttfLegit;
}

