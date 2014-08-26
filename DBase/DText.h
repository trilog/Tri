#pragma once

#include <string>
using std::string;

#include <SDL_ttf.h>

#include "DTexture.h"

class DText : public DTexture
{
    public:
                     DText    ();
                     DText    (string text, SDL_Renderer* _renderer, TTF_Font* _font, Uint8 red = 0x00, Uint8 green = 0x00, Uint8 blue = 0x00, Uint8 alpha = 0xFF);
                     DText    (string text, SDL_Renderer* _renderer, TTF_Font* _font, SDL_Color& _color);
        inline void  setColor (SDL_Color _color) { color = _color; }
        inline void  setColor (Uint8 red = 0x00, Uint8 green = 0x00, Uint8 blue = 0x00, Uint8 alpha = 0xFF) { color = { red, green, blue, alpha }; }
        inline void  setFont  (TTF_Font* _font) { font = _font; }
        bool         setText (string text);
    private:
        TTF_Font* font;
        SDL_Color color;
};
