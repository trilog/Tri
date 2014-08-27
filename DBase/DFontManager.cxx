#include "DFontManager.h"

#include <iostream>
using std::cerr;
using std::endl;

// **************** Con/Destructors ***********************

DFontManager::DFontManager()
{
    ttfLegit = init();
}

DFontManager::~DFontManager()
{
    if (ttfLegit) TTF_Quit();
}

// **************** init **********************************

bool DFontManager::init()
{
    if (TTF_Init() == -1)
    {
        cerr << "SDL_ttf did not initialize" << TTF_GetError() << endl;
        return false;
    }
    return true;
}

// **************** openFont ******************************

TTF_Font* DFontManager::openFont(string fontName, string fontFile, int fontSize)
{
    map<string, TTF_Font*>::iterator it = fontMap.find(fontName);
    if (it != fontMap.end())
    {
        cerr << "DFontManager: " << fontName << " has already been loaded." << endl;
        return it->second;
    }
    TTF_Font* font = TTF_OpenFont(fontFile.c_str(), fontSize);
    fontMap[fontName] = font;
    return font;
}

// **************** getFont *******************************

TTF_Font* DFontManager::getFont(string fontName)
{
    map<string, TTF_Font*>::iterator it = fontMap.find(fontName);
    if (it != fontMap.end()) return it->second;
    else return NULL;
}
