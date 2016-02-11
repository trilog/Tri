#include "OverGame.h"
#include <chrono>
#include <cmath>
#include <sstream>
using std::ostringstream;

#include "DText.h"

#define _USE_MATH_DEFINES

// **************** Con/Destructors ***********************

OverGame::OverGame():
paused(false)
{
}

OverGame::~OverGame()
{
}

// **************** Init **********************************

void OverGame::init()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
    distribution = std::uniform_real_distribution<float>(-M_PI, M_PI);
    displayManager.init();
    fontManager.init();
    soundManager.init();
    window.initWindow("Edge: Saga of the Candy King", 1280, 720);
    window.initRenderer();
    renderer = window.getRenderer();
    king = new King(renderer);
}

// **************** End ***********************************

void OverGame::end()
{
    delete king;
    king = NULL;
}

// **************** Stage 1 *******************************

void OverGame::initStage1()
{
    background = DImage(renderer, "Resources/CandyKing/backgrounds/crappybackground.png", 0xFF, 0xFF, 0xFF);
    soundManager.addSound("Cat-Whimper", "Resources/CandyKing/wav/Whimper.wav");
    soundManager.loadMusic("Resources/CandyKing/wav/KingCandySagaEdge.wav");
    fontManager.openFont("KingThings45", "Resources/Fonts/Kingthings/Kingthings_Calligraphica_Light.ttf", 45);
    fontManager.openFont("Chantelli30", "Resources/Fonts/Chantelli/Chantelli_Antiqua.ttf", 30);
    king->load("Resources/CandyKing/king/kingForest.txt");
    shepherd = new Shepherd(renderer, &soundManager);
    shepherd->addSolid(king->getPoly());
    shepherd->load("pig", "Resources/CandyKing/animals/pigScaled.txt");
    spawnTimer.start();
}

void OverGame::runStage1()
{
    const int windowWidth = window.getWidth();
    const int windowHeight = window.getHeight();
    DPoint windowCenter(windowWidth/2, windowHeight/2);
    king->moveCenter(windowCenter);
    TTF_Font* kingThings = fontManager.getFont("KingThings45");
    TTF_Font* chantelli = fontManager.getFont("Chantelli30");
    SDL_Color black = { 0x00, 0x00, 0x00, 0xFF };
    SDL_Color red   = { 0x99, 0x22, 0x22, 0xFF };
    DText title("Edge: Saga of the Candy King", renderer, kingThings, black);
    ostringstream scoreString;
    scoreString.str("Defend the king!");
    DText scoreText(scoreString.str(), renderer, chantelli, red);
    // soundManager.playMusic();
    SDL_Event event;
    // ************ Loop
    bool quit = false;
//    const Uint8* keyStates = SDL_GetKeyboardState(NULL);
    int mouseX = 0;
    int mouseY = 0;
    int score = 0;
    DPoint mousePoint;
    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT) quit = true;
 //           if (keyStates[SDL_SCANCODE_ESCAPE])
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        paused = !paused;
                        if (paused) shepherd->pause();
                        else shepherd->unpause();
                        break;
                    default:
                        break;
                }
            }
            if (!paused) 
            {
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
                    mousePoint.set(mouseX, mouseY);
                    if (mouseState & SDL_BUTTON(1)) shepherd->checkHit(mouseX, mouseY);
                    // if (mouseState & SDL_BUTTON(2)) 
                    if (mouseState & SDL_BUTTON(3)) king->moveCenter(mousePoint);
                }
            }
        }
        if (!paused)
        {
            if (spawnTimer.elapsed() > 700)
            {
                spawnTimer.start();
                float theta = distribution(generator);
                int x = (int) (720.0 * cos(theta) + windowWidth/2);
                int y = (int) (720.0 * sin(theta) + windowHeight/2);
                DPoint kingCenter = king->getPosition() + king->getFocus();
                shepherd->spawn("pig", x, y)->setDestination(kingCenter);
            }
            score = shepherd->getScore();
            if (score > 0)
            {
                scoreString.str("");
                scoreString << "Score: " << score;
                scoreText.setText(scoreString.str());
                scoreString.flush();
            }
        }
        // ******** Clear
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);
        // ******** Add Elements
        background.render(0, 0);
        title.render(100, 0);
        scoreText.render(900, 670);
        king->render();
        // king->renderPoly();
        shepherd->render();
        // windowCenter.renderCross(renderer, blue, 8);
        if (paused)
        {
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x99);
            SDL_RenderFillRect(renderer, &window.getRect());
        }
        // ******** Render
        SDL_RenderPresent(renderer);
    }
}


void OverGame::endStage1()
{
    delete king;
    king = NULL;
    delete shepherd;
    shepherd = NULL;
}
