#pragma once

#include <random>

#include <SDL.h>

#include "DTimer.h"
#include "DDisplayManager.h"
#include "DFontManager.h"
#include "DImage.h"
#include "DWindow.h"
#include "DSoundManager.h"
#include "Shepherd.h"
#include "King.h"

class OverGame
{
    public:
              OverGame     ();
             ~OverGame     ();
        void  init         ();
        void  end          ();
        void  initStage1   ();
        void  runStage1    ();
        void  endStage1    ();
    private:
        std::default_random_engine generator;
        std::uniform_real_distribution<float> distribution;
        DDisplayManager displayManager;
        DFontManager    fontManager;
        DSoundManager   soundManager;
        DWindow         window;
        SDL_Renderer*   renderer;
        DTimer          spawnTimer;
        DTimer          levelTimer;
        DImage          background;
        King*           king;
        Shepherd*       shepherd;
        bool            paused;
};
