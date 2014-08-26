#include <iostream>
using std::cout;
using std::endl;
#include <sstream>
using std::ostringstream;

#include <SDL.h>

#include "DDisplayManager.h"
#include "DWindow.h"
#include "DText.h"
#include "DPolygon.h"

int main (int argc, char** args)
{
    // ************ Init
    DDisplayManager displayManager;
    displayManager.initSDL();
    displayManager.initIMG();
    displayManager.initTTF();
    if (!displayManager.isLegit()) return 1;
    // ************ Windows
    const int windowWidth  = 800;
    const int windowHeight = 600;
    DWindow window;
    if (!window.initWindow("Geometry Test", windowWidth, windowHeight)) return 2;
    if (!window.initRenderer()) return 3;
    SDL_Renderer* renderer = window.getRenderer();
    // ************ Color Definitions
    SDL_Color black = { 0x00, 0x00, 0x00, 0xFF };
    SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
    SDL_Color red   = { 0x99, 0x22, 0x22, 0xFF };
    SDL_Color green = { 0x22, 0x99, 0x22, 0xFF };
    SDL_Color blue  = { 0x22, 0x22, 0xFF, 0xFF };
    // ************ Objects
    DPoint aPoint (400, 100);
    DPoint b1Point(200, 200);
    DPoint b2Point(600, 200);
    DPoint c1Point(300, 400);
    DPoint c2Point(500, 400);
    DPoint dPoint (400, 300);
    DPolygon shape;
    shape.addPoint(aPoint);
    shape.addPoint(b1Point);
    shape.addPoint(c1Point);
    shape.addPoint(dPoint);
    shape.addPoint(c2Point);
    shape.addPoint(b2Point);
    DLine crossLine(400, 400, 300, 350);
    DLine modLine(400, 400, 300, 350);
    // ************ Text
    TTF_Font* openSans = TTF_OpenFont("Resources/Fonts/OpenSans/OpenSans-Regular.ttf", 30);
    DText intersectText("Intersections: ", renderer, openSans, black);
    ostringstream intersectString;
    // ************ Primary Loop
    SDL_Event event;
    bool quit = false;
    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
    DPoint mousePoint;
    DPoint oldMousePoint;
    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT) quit = true;
            if (keyStates[SDL_SCANCODE_ESCAPE]) quit = true;
            Uint32 mouseState = SDL_GetMouseState(&mousePoint.x, &mousePoint.y);
            if (mousePoint != oldMousePoint)
            {
                modLine.p2 = mousePoint;
                crossLine.p2 = modLine.p2;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (mouseState & SDL_BUTTON(1)) // Left click
                {
                    modLine.p1 = mousePoint;
                    crossLine.p1 = modLine.p1;
                }
                if (mouseState & SDL_BUTTON(2)) // Middle click
                {
                    shape.setFocus(mousePoint);;
                }
                if (mouseState & SDL_BUTTON(3)) // Right click
                {
                    shape.moveFocus(mousePoint);
                }
            }
        }
        if (mousePoint != oldMousePoint);
        {
            oldMousePoint = mousePoint;
            intersectString.str("");
            intersectString << "Intersections: " << shape.intersections(crossLine);
            intersectText.setText(intersectString.str());
            shape.clip(modLine);
        }
        // ******** Clear
        SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
        SDL_RenderClear(renderer);
        // ******** Points
        aPoint.render(renderer, green, 3);
        b1Point.render(renderer, green, 3);
        c1Point.render(renderer, green, 3);
        b2Point.render(renderer, green, 3);
        c2Point.render(renderer, green, 3);
        dPoint.render(renderer, green, 3);
        // ******** Add Elements
        shape.render(renderer, black);
        crossLine.render(renderer, blue);
        modLine.render(renderer, red);
        // ******** Text
        intersectText.render(40, 500);
        // ******** Render
        SDL_RenderPresent(renderer);
    }
    return 0;
}
