#include "King.h"
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <fstream>
using std::ifstream;

// **************** Con/Destructors ***********************

King::King(SDL_Renderer* _renderer):
renderer(_renderer)
{
}

King::~King()
{
}

// **************** render ********************************

void King::renderPoly()
{
    shape.render(renderer);
    /*
    SDL_Color red   = { 0x99, 0x22, 0x22, 0xFF };
    SDL_Color green = { 0x22, 0x99, 0x22, 0xFF };
    pos.render(renderer, red, 12);
    focus.render(renderer, green, 16);
    */
}

// **************** load **********************************

bool King::load(string fileName)
{
    ifstream inFile(fileName.c_str());
    if (inFile.is_open())
    {
        string imageFile;
        Uint8 red = 0;
        Uint8 green = 0;
        Uint8 blue = 0;
        inFile >> imageFile >> red >> green >> blue;
        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;
        int focusX = 0;
        int focusY = 0;
        inFile >> x >> y >> w >> h >> focusX >> focusY; 
        cout << x << " " << y << " " << w << " " << h << " " << focusX << " " << focusY << endl;
        texture = DImage(renderer, imageFile, red, green, blue);
        shape.makeEllipse(83, 28, 289, 412);
        focus.set(focusX, focusY);
        return true;
    }
    else 
    {
        cerr << "Could not load King config: " << fileName << endl;
        return false;
    }
}

// **************** moveCenter ****************************

void King::moveCenter(DPoint& point)
{
    pos = point - focus;
    shape.moveFocus(point);
}
