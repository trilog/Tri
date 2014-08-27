#pragma once

#include <SDL.h>

class DWindow
{
    public:
              DWindow              ();
             ~DWindow              ();
        // Init
        bool  initRenderer         ();
        bool  initWindow           (const char* windowTitle = "Untitled Window", int _width = 640, int _height = 480);
        // Get Objects
        SDL_Renderer* getRenderer  () { return renderer; }
        SDL_Window*   getWindow    () { return window; }
        // Operations
        void  focus                ();
        void  handleEvent          (SDL_Event& event);
        void  render               ();
        // Queries
        int   getHeight            () { return height; }
        int   getWidth             () { return width; }
        bool  hasMouseFocus        () { return mouseFocus; }
        bool  hasKeyboardFocus     () { return keyboardFocus; }
        bool  isShown              () { return shown; }
    private:
        SDL_Window*   window;
        SDL_Renderer* renderer;
        int           windowID;
        int           width;
        int           height;
        bool          mouseFocus;
        bool          keyboardFocus;
        bool          shown;
};
