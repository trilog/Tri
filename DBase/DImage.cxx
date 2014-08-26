#include "DImage.h"
#include <iostream>
using std::cerr;
using std::endl;
#include <SDL_image.h>

// **************** Con/Destructors ***********************

DImage::DImage()
{
}

DImage::DImage(SDL_Renderer* _renderer, string path, Uint8 red, Uint8 green, Uint8 blue)
{
    setRenderer(_renderer);
    loadImage(path, red, green, blue);
}

DImage::~DImage()
{
}

// **************** loadImage *****************************

bool DImage::loadImage(string path, Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL)
    {
        cerr << "Unable to load: " << path << " erorr: " << IMG_GetError() << endl;
        return false;
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, red, green, blue));
    return convertSurface(surface, true);
}
/*
bool DImage::autoClipImage(string path, Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL)
    {
        cerr << "Unable to load: " << path << " error: " << IMG_GetError() << endl;
        return false;
    }
    const SDL_PixelFormat* format = surface->format;
    Uint32 transparent = SDL_MapRGB(format, red, green, blue);
    SDL_SetColorKey(surface, SDL_TRUE, transparent);
    width = surface->w;
    height = surface->h;
    return true;
}
*/
