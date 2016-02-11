#pragma once

#include <SDL.h>

class DWindow
{
    public:
              DWindow              ();
             ~DWindow              ();
        // Init
        bool  initRenderer         ();
        bool  initWindow           (const char* windowTitle = "Untitled Window", int width = 1280, int height = 720);
        // Get Objects
        SDL_Renderer* getRenderer  () { return renderer; }
        SDL_Window*   getWindow    () { return window; }
        // Operations
        void  focus                ();
        void  handleEvent          (SDL_Event& event);
        void  render               ();
        // Queries
        int   getHeight            () { return rect.h; }
        int   getWidth             () { return rect.w; }
        bool  hasMouseFocus        () { return mouseFocus; }
        bool  hasKeyboardFocus     () { return keyboardFocus; }
        bool  isShown              () { return shown; }
        SDL_Rect& getRect          () { return rect; }
    private:
        SDL_Window*   window;
        SDL_Renderer* renderer;
        int           windowID;
        SDL_Rect      rect;
        bool          mouseFocus;
        bool          keyboardFocus;
        bool          shown;
};
