#pragma once

#include <string>
using std::string;

#include "DTexture.h"

class DImage : public DTexture
{
    public:
              DImage    ();
              DImage    (SDL_Renderer* _renderer, string path, Uint8 red = 0xFF, Uint8 green = 0xFF, Uint8 blue = 0xFF);
             ~DImage    ();
        bool  loadImage (string path, Uint8 red = 0xFF, Uint8 green = 0xFF, Uint8 blue = 0xFF);
};
