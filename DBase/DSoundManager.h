#pragma once

#include <string>
using std::string;
#include <map>
using std::map;

#include <SDL_mixer.h>

class DSoundManager
{
    public:
              DSoundManager ();
             ~DSoundManager ();
        bool  init();
        // ******** Music
        bool  loadMusic     (string path);
        void  playMusic     () { Mix_PlayMusic(music, -1); }
        void  pauseMusic    () { Mix_PauseMusic(); }
        void  resumeMusic   () { Mix_ResumeMusic(); }
        void  stopMusic     () { Mix_HaltMusic(); }
        // ******** Sounds
        Mix_Chunk* addSound (string name, string path);
        Mix_Chunk* getSound (string name);
        inline void  playSound (Mix_Chunk* sound) { Mix_PlayChannel(-1, sound, 0); }
        void  playSound (string name);
    private:
        Mix_Music* music;
        map<string, Mix_Chunk*> sounds;
};
