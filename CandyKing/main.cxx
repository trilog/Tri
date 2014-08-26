#include <iostream>
using std::cout;
using std::endl;
#include <sstream>
using std::ostringstream;
#include <chrono>
#include <random>

#include <SDL.h>

#include "DDisplayManager.h"
#include "DSoundManager.h"
#include "DWindow.h"
#include "DImage.h"
#include "DText.h"
#include "Shepherd.h"
#include "King.h"

int main (int argc, char** args)
{
    // ************ Random Number Generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> distribution(-M_PI, M_PI);
    // ************ Init
    DDisplayManager displayManager;
    displayManager.initSDL();
    displayManager.initIMG();
    displayManager.initTTF();
    if (!displayManager.isLegit()) return 1;
    DSoundManager soundManager;
    soundManager.init();
    // ************ Windows
    DWindow window;
    const int windowWidth  = 1280;
    const int windowHeight =  720;
    DPoint windowCenter(windowWidth/2, windowHeight/2);
    if (!window.initWindow("Edge: The Saga of the Candy King", windowWidth, windowHeight)) return 2;
    if (!window.initRenderer()) return 3;
    SDL_Renderer* renderer = window.getRenderer();
    // ************ Fonts
    SDL_Color black = { 0x00, 0x00, 0x00, 0xFF };
    SDL_Color red   = { 0x99, 0x22, 0x22, 0xFF };
//    SDL_Color blue  = { 0x22, 0x22, 0x99, 0xFF };
    TTF_Font* kingThings = TTF_OpenFont("Resources/Fonts/Kingthings/Kingthings_Calligraphica_Light.ttf", 45);
    TTF_Font* chantelli = TTF_OpenFont("Resources/Fonts/Chantelli/Chantelli_Antiqua.ttf", 30);
    DText title("Edge: Saga of the Candy King", renderer, kingThings, black);
    ostringstream scoreString;
    scoreString.str("Defend the king!");
    DText scoreText(scoreString.str(), renderer, chantelli, red);
    // ************ Textures
    DImage background(renderer, "Resources/CandyKing/backgrounds/cich.png", 0xFF, 0xFF, 0xFF);
    // ************ Sounds
//    Mix_Chunk* meow = soundManager.addSound("Cat-Meow", "Resources/CandyKing/wav/Meow.wav");
    soundManager.addSound("Cat-Whimper", "Resources/CandyKing/wav/Whimper.wav");
    soundManager.loadMusic("Resources/CandyKing/wav/KingCandySagaEdge.wav");
//    soundManager.playMusic();
    // ************ Objects
    King king(renderer);
    king.load("Resources/CandyKing/king/kingForest.txt");
    king.moveCenter(windowCenter);
    Shepherd shepherd(renderer, &soundManager);
    shepherd.addSolid(king.getPoly());
    shepherd.load("pig", "Resources/CandyKing/animals/pigScaled.txt");
    // ************ Primary Loop
    DTimer spawnTimer;
    spawnTimer.start();
    SDL_Event event;
    bool quit = false;
    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
    int mouseX = 0;
    int mouseY = 0;
    int score = 0;
    DPoint mousePoint;
    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT) quit = true;
            if (keyStates[SDL_SCANCODE_ESCAPE]) quit = true;
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
                mousePoint.set(mouseX, mouseY);
                if (mouseState & SDL_BUTTON(1)) shepherd.checkHit(mouseX, mouseY);
                // if (mouseState & SDL_BUTTON(2)) 
                if (mouseState & SDL_BUTTON(3)) king.moveCenter(mousePoint);
            }
        }
        if (spawnTimer.elapsed() > 700)
        {
            spawnTimer.start();
            float theta = distribution(generator);
            int x = (int) (720.0 * cos(theta) + windowWidth/2);
            int y = (int) (720.0 * sin(theta) + windowHeight/2);
            DPoint kingCenter = king.getPosition() + king.getFocus();
            shepherd.spawn("pig", x, y)->setDestination(kingCenter);
        }
        score = shepherd.getScore();
        if (score > 0)
        {
            scoreString.str("");
            scoreString << "Score: " << score;
            scoreText.setText(scoreString.str());
            scoreString.flush();
        }
        // ******** Clear
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);
        // ******** Add Elements
        background.render(  0,   0);
        background.render(712,   0);
        background.render(  0, 526);
        background.render(712, 526);
        title.render(300, 0);
        scoreText.render(700, 670);
        king.render();
        king.renderPoly();
        shepherd.render();
//        windowCenter.renderCross(renderer, blue, 8);
        // ******** Render
        SDL_RenderPresent(renderer);
    }
    // ************
    return 0;
}
