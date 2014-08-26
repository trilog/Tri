#include "DText.h"
#include <iostream>
using std::cerr;
using std::endl;

// **************** Con/Destructors ***********************

DText::DText():
font(NULL)
{
}

DText::DText (string text, SDL_Renderer* _renderer, TTF_Font* _font, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
    setRenderer(_renderer);
    setFont(_font);
    setColor(red, green, blue, alpha);
    setText(text);
}

DText::DText (string text, SDL_Renderer* _renderer, TTF_Font* _font, SDL_Color& _color)
{
    setRenderer(_renderer);
    setFont(_font);
    setColor(_color);
    setText(text);
}

// **************** setText *******************************

bool DText::setText(string text)
{
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (surface == NULL)
    {
        cerr << "Unable to render text surface: " << TTF_GetError() << endl;
        return false;
    }
    return convertSurface(surface, true);
}
