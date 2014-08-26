#include "DTexture.h"

#include <iostream>
using std::cerr;
using std::endl;

// **************** Con/Destructors ***********************

DTexture::DTexture():
renderer(NULL), texture(NULL), manager(NULL)
{
}

DTexture::~DTexture()
{
    if ((manager != NULL) && (texture != NULL)) SDL_DestroyTexture(texture);
}

// **************** free **********************************

void DTexture::free()
{
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

// **************** convertSurface ************************

bool DTexture::convertSurface(SDL_Surface* surface, bool deleteSurface)
{
    free();
    SDL_SetSurfaceRLE(surface, 1);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    defaultClip.clip  = { 0, 0, surface->w, surface->h };
    defaultClip.focus = { 0, 0 };
    if (texture == NULL)
    {
        cerr << "Unable to create texture from surface: " << SDL_GetError() << endl;
        return false;
    }
    if (deleteSurface) SDL_FreeSurface(surface);
    return true;
}

// **************** render ********************************

void DTexture::render(int x, int y, ClipInfo& clip)
{
    SDL_Rect dstRect = { x - clip.focus.x, y - clip.focus.y, clip.clip.w, clip.clip.h };
    SDL_Rect srcRect = { clip.clip.x, clip.clip.y, clip.clip.w, clip.clip.h };
    render(&dstRect, &srcRect);
}

void DTexture::render(SDL_Rect* dstRect, SDL_Rect* srcRect)
{
    SDL_RenderCopy(renderer, texture, srcRect, dstRect);
}

void DTexture::renderAdvanced(int x, int y, ClipInfo& clip, double angle, SDL_RendererFlip flip)
{
    SDL_Rect dstRect = { x - clip.focus.x, y - clip.focus.y, clip.clip.w, clip.clip.h };
    SDL_Rect srcRect = { clip.clip.x, clip.clip.y, clip.clip.w, clip.clip.h };
    SDL_Point center = { clip.focus.x, clip.focus.y };
    if (flip == SDL_FLIP_VERTICAL) 
    {
        dstRect.y = y - (clip.clip.h - clip.focus.y);
        center.y = clip.clip.h - clip.focus.y;
    }
    renderAdvanced(&dstRect, &srcRect, angle, &center, flip);
}

void DTexture::renderAdvanced(SDL_Rect* dstRect, SDL_Rect* srcRect, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(renderer, texture, srcRect, dstRect, (180.0/M_PI) * angle, center, flip);
}
