#include <iostream>
using std::cout;
using std::endl;
#include <sstream>
using std::ostringstream;

#include <SDL.h>

#include "DDisplayManager.h"
#include "DWindow.h"
#include "DText.h"
#include "DLine.h"

int main (int argc, char** args)
{
    // ************ Init
    DDisplayManager displayManager;
    displayManager.initSDL();
    displayManager.initIMG();
    displayManager.initTTF();
    if (!displayManager.isLegit()) return 1;
    // ************ Windows
    const int windowWidth  = 1280;
    const int windowHeight =  720;
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
    // ************ Axes
    int crosshairSize = 240;
    DPoint center(800, 360);
    DPoint vertLine1(center.x, center.y - crosshairSize);
    DPoint vertLine2(center.x, center.y + crosshairSize);
    DLine  vertLine(vertLine1, vertLine2);
    DPoint horzLine1(center.x - crosshairSize, center.y);
    DPoint horzLine2(center.x + crosshairSize, center.y);
    DLine  horzLine(horzLine1, horzLine2);
    DPoint x100(100, 0);
    DPoint y100(0, 100);
    DPoint p1 = center;
    p1 += x100;
    DPoint p2 = center;
    p2 -= x100;
    DPoint p3 = center;
    p3 += y100;
    DPoint p4 = center;
    p4 -= y100;
    DPoint p5 = center + x100 + y100;
    DPoint p6 = center - x100 - y100;
    DPoint p7 = center + x100 - y100;
    DPoint p8 = center - x100 + y100;
    // ************ Objects
    DPoint clipPoint(100, 100);
    DLine aLine(100, 200, 400, 400);
    DLine bLine(400, 300, 200, 500);
    DLine cLine(aLine.p2.x, aLine.p2.y, bLine.p2.x, bLine.p2.y);
    DLine aLineCentered = aLine.vector() + center;
    DLine bLineCentered = bLine.vector() + center;
    DLine cLineCentered = cLine.vector() + center;
    DLine aPerpCentered = aLine.perp().vector() + center;
    DLine bPerpCentered = bLine.perp().vector() + center;
    // ************ Text
    TTF_Font* openSans = TTF_OpenFont("res/OpenSans-Regular.ttf", 30);
    DText aText("A", renderer, openSans, black);
    DText bText("B", renderer, openSans, black);
    DText cText("C", renderer, openSans, black);

    ostringstream fString;
    int f = 0; 
    fString << "aT . b: ";
    DText fText(fString.str(), renderer, openSans, black);

    ostringstream aaString;
    int aa = 0;
    aaString << "aT . c: ";
    DText aaText(aaString.str(), renderer, openSans, black);

    ostringstream bbString;
    int bb = 0;
    bbString << "bT . c: ";
    DText bbText(bbString.str(), renderer, openSans, black);

    ostringstream intersectString;
    intersectString << "Intersecting?";
    DText intersectText(intersectString.str(), renderer, openSans, black);

    // ************ Primary Loop
    SDL_Event event;
    bool quit = false;
    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
    int mouseX = 0;
    int mouseY = 0;
    bool recalc = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT) quit = true;
            if (keyStates[SDL_SCANCODE_ESCAPE]) quit = true;
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseState & SDL_BUTTON(1)) 
                {
                    bLine.p1 = DPoint(mouseX, mouseY);
                    recalc = true;
                }
                // if (mouseState & SDL_BUTTON(2))
                if (mouseState & SDL_BUTTON(3)) 
                {
                    bLine.p2 = DPoint(mouseX, mouseY);
                    recalc = true;
                }
            }
        }
        if (recalc)
        {
            if (bLine.intersect(aLine, &clipPoint)) intersectString.str("Lines are intersecting");
            else intersectString.str("Lines are not intersecting");
            intersectText.setText(intersectString.str());

            recalc = false;
            cLine.p1 = aLine.p2;
            cLine.p2 = bLine.p2;
            cLineCentered = cLine.vector() + center;
            bLineCentered = bLine.vector() + center;
            bPerpCentered = bLine.perp().vector() + center;

            fString.str("");
            f = aLine.perpDot(bLine);
            fString << "aT . b: " << f;
            fText.setText(fString.str());

            aaString.str("");
            aa = aLine.perpDot(cLine);
            aaString << "aT . c: " << aa;
            aaText.setText(aaString.str());

            bbString.str("");
            bb = bLine.perpDot(cLine);
            bbString << "bT . c: " << bb;
            bbText.setText(bbString.str());

        }
        // ******** Clear
        SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
        SDL_RenderClear(renderer);
        // ******** Axes
        vertLine.render(renderer, black);
        horzLine.render(renderer, black);
        center.render(renderer, black, 9);
        p1.render(renderer, black, 7);
        p2.render(renderer, black, 7);
        p3.render(renderer, black, 7);
        p4.render(renderer, black, 7);
        p5.render(renderer, black, 7);
        p6.render(renderer, black, 7);
        p7.render(renderer, black, 7);
        p8.render(renderer, black, 7);
        // ******** Add Elements
        aLine.render(renderer, red);
        aLineCentered.render(renderer, red);
        aPerpCentered.render(renderer, red);
        aText.render((aLine.p2.x + aLine.p1.x)/2, (aLine.p2.y + aLine.p1.y)/2);
        aText.render(aLineCentered.p2.x, aLineCentered.p2.y);

        bLine.render(renderer, green);
        bLineCentered.render(renderer, green);
        bPerpCentered.render(renderer, green);
        bText.render((bLine.p2.x + bLine.p1.x)/2, (bLine.p2.y + bLine.p1.y)/2);
        bText.render(bLineCentered.p2.x, bLineCentered.p2.y);

        cLine.render(renderer, blue);
        cLineCentered.render(renderer, blue);
        cText.render((cLine.p2.x + cLine.p1.x)/2, (cLine.p2.y + cLine.p1.y)/2);
        cText.render(cLineCentered.p2.x, cLineCentered.p2.y);
        clipPoint.render(renderer, black, 5);
        // Text
        fText.render(40, 40);
        aaText.render(40, 80);
        bbText.render(40, 120);
        intersectText.render(40, 160);
        // ******** Render
        SDL_RenderPresent(renderer);
    }
    return 0;
}
