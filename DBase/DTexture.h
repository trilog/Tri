#pragma once
#define _USE_MATH_DEFINES

#include <string>
using std::string;

#include <SDL.h>

#include "DTextureManager.h"

struct ClipInfo
{
    string    name;
    SDL_Rect  clip;
    SDL_Point focus;
};

class DTexture
{
    public:
              DTexture       ();
             ~DTexture       ();
        bool  convertSurface (SDL_Surface* surface, bool deleteSurface = true);
        void  free           ();
        void  setRenderer    (SDL_Renderer* _renderer)   { renderer = _renderer; }
        void  setManager     (DTextureManager* _manager) { manager  = _manager; }
        void  setAlpha       (Uint8 alpha)               { SDL_SetTextureAlphaMod(texture, alpha); }
        void  setBlendMode   (SDL_BlendMode blending)    { SDL_SetTextureBlendMode(texture, blending); }
        virtual void render  (int x, int y)              { render(x, y, defaultClip); }
        virtual void render  (int x, int y, ClipInfo& clip);
        virtual void render  (SDL_Rect* dstRect, SDL_Rect* srcRect);

        virtual void renderAdvanced (int x, int y, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) { renderAdvanced(x, y, defaultClip, angle, flip); }
        virtual void renderAdvanced (int x, int y, ClipInfo& clip, double angle = 0, SDL_RendererFlip = SDL_FLIP_NONE);
        virtual void renderAdvanced (SDL_Rect* dstRect, SDL_Rect* srcRect, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        SDL_Renderer* getRenderer() { return renderer; }
    private:
        SDL_Renderer*    renderer;
        SDL_Texture*     texture;
        DTextureManager* manager;
        ClipInfo         defaultClip;
};
