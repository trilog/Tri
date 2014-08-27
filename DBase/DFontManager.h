#pragma once

#include <map>
using std::map;
#include <string>
using std::string;

#include <SDL_ttf.h>

class DFontManager
{
    public:
                   DFontManager ();
                  ~DFontManager ();
        bool       init         ();
        TTF_Font*  openFont     (string fontName, string fontFile, int fontSize = 10);
        TTF_Font*  getFont      (string fontName);
    private:
        bool ttfLegit;
        map<string, TTF_Font*> fontMap;
};
