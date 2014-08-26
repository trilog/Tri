#include "DSoundManager.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <SDL.h>

// **************** Con/Destructors ***********************

DSoundManager::DSoundManager():
music(NULL)
{
}

DSoundManager::~DSoundManager()
{
    if (music != NULL) Mix_FreeMusic(music);
    for (auto& it: sounds) Mix_FreeChunk(it.second);
    Mix_Quit();
}

// **************** init **********************************

bool DSoundManager::init()
{
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) 
    {
        cerr << "SDL Audio did not initialize:" << SDL_GetError() << endl;
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cerr << "SDL_mixer could not initialize: " << Mix_GetError() << endl;
        return false;
    }
    return true;
}

// **************** loadMusic *****************************

bool DSoundManager::loadMusic(string path)
{
    if (music != NULL) Mix_FreeMusic(music);
    music = Mix_LoadMUS(path.c_str());
    if (music == NULL)
    {
        cerr << "Unable to load music: " << path << ": " << Mix_GetError() << endl;
        return false;
    }
    return true;
}

// **************** addSound ******************************

Mix_Chunk* DSoundManager::addSound(string name, string path)
{
    map<string, Mix_Chunk*>::iterator it = sounds.find(name);
    if (it != sounds.end()) return it->second;
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if (sound == NULL)
    {
        cerr << "Unable to load: " << path << ": " << Mix_GetError() << endl;
        return NULL;
    }
    sounds.emplace(name, sound);
    return sound;
}

// **************** getSound ******************************

Mix_Chunk* DSoundManager::getSound(string name)
{
    map<string, Mix_Chunk*>::iterator it = sounds.find(name);
    if (it != sounds.end()) return it->second;
    else return NULL;
}

// **************** playSound *****************************

void DSoundManager::playSound(string name)
{
    Mix_Chunk* sound = getSound(name);
    if (sound != NULL) playSound(sound);
}
