#pragma once

class DDisplayManager
{
    public:
              DDisplayManager ();
             ~DDisplayManager ();
        bool  init            ();
        bool  initSDL         ();
        bool  initIMG         ();
        bool  isLegit         () { return imgLegit && sdlLegit; }
    private:
        bool imgLegit;
        bool sdlLegit;
};
