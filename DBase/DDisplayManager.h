#ifndef __DDISPLAYMANAGER__
#define __DDISPLAYMANAGER__

class DDisplayManager
{
    public:
              DDisplayManager ();
             ~DDisplayManager ();
        bool  initSDL         ();
        bool  initIMG         ();
        bool  initTTF         ();
        bool  isLegit         () { return imgLegit && sdlLegit && ttfLegit; }
    private:
        bool imgLegit;
        bool sdlLegit;
        bool ttfLegit;
};

#endif /* DDisplayManager.h */
