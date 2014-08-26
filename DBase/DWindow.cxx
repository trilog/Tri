#include "DWindow.h"
#include <iostream>
using std::cerr;
using std::endl;

// **************** Con/Destructors ***********************

DWindow::DWindow():
window(NULL), renderer(NULL), 
width(0), height(0),
mouseFocus(false), keyboardFocus(false), shown(false)
{
}

DWindow::~DWindow()
{
    if (renderer != NULL) 
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }
}

bool DWindow::initWindow(const char* windowTitle, int _width, int _height)
{
    width = _width;
    height = _height;
    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        cerr << "Error: Could not create window: " << SDL_GetError() << endl;
        return false;
    }
    windowID = SDL_GetWindowID(window);
    mouseFocus = true;
    keyboardFocus = true;
    shown = true;
    return true;
}

bool DWindow::initRenderer()
{
    if (renderer != NULL) SDL_DestroyRenderer(renderer);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        cerr << "Error: Could not create renderer: " << SDL_GetError() << endl;
        return false;
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    shown = true;
    return true;
}

void DWindow::handleEvent(SDL_Event& event)
{
    if (event.type == SDL_WINDOWEVENT)
    {
        switch (event.window.event)
        {
            case SDL_WINDOWEVENT_SHOWN:
                shown = true;
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                shown = false;
                break;
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                width = event.window.data1;
                height = event.window.data2;
                SDL_RenderPresent(renderer);
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                SDL_RenderPresent(renderer);
                break;
            case SDL_WINDOWEVENT_ENTER:
                mouseFocus = true;
                break;
            case SDL_WINDOWEVENT_LEAVE:
                mouseFocus = false;
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                keyboardFocus = true;
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                keyboardFocus = false;
                break;
            case SDL_WINDOWEVENT_CLOSE:
                SDL_HideWindow(window);
                break;
        }
    }
}

void DWindow::focus()
{
    if (!shown) SDL_ShowWindow(window);
    SDL_RaiseWindow(window);
}

void DWindow::render()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
