#include "Shepherd.h"
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <fstream>
using std::ifstream;

// **************** Con/Destructors ***********************

Shepherd::Shepherd(SDL_Renderer* _renderer, DSoundManager* _soundManager):
renderer(_renderer), soundManager(_soundManager),
score(0)
{
}

Shepherd::~Shepherd()
{
}

// **************** load **********************************

bool Shepherd::load(string animalName, string fileName)
{
    {
        map<string, Animal>::iterator it = cloningPen.find(animalName);
        if (it != cloningPen.end())
        {
            cerr << animalName << " already exists" << endl;
            return NULL;
        }
    }
    ifstream inFile(fileName.c_str());
    if (inFile.is_open())
    {
        string imageFile;
        Uint8 red = 0;
        Uint8 green = 0;
        Uint8 blue = 0;
        inFile >> imageFile >> red >> green >> blue;
        map<string, DImage>::iterator it = textures.find(imageFile);
        if (it == textures.end())
        {
            cout << "Loading: " << imageFile << " (" << red << ", " << green << ", " << blue << ")" << endl;
            textures[imageFile] = DImage(renderer, imageFile, red, green, blue);
        } 
        it = textures.find(imageFile);
        Animal progenitor;
        progenitor.setImage(&it->second, 0, 0);
        progenitor.setSoundManager(soundManager);
        int clips = 0;
        inFile >> clips;
        string clipName;
        int x1 = 0;
        int y1 = 0;
        int x2 = 0;
        int y2 = 0;
        int xf = 0;
        int yf = 0;
        for (int i = 0; i < clips; ++i) 
        {
            inFile >> clipName >> x1 >> y1 >> x2 >> y2 >> xf >> yf;
            cout << clipName << " " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << xf << " " << yf << endl;
            progenitor.setClip(clipName, x1, y1, x2 - x1, y2 - y1, xf - x1, yf - y1);
        }
        cloningPen[animalName] = progenitor;
        inFile.close();
        return true;
    }
    else
    {
        cerr << "Could not load animal: " << fileName << endl;
        return false;
    }
}

// **************** spawn *********************************

Animal* Shepherd::spawn(string animalName, int x, int y)
{
    map<string, Animal>::iterator it = cloningPen.find(animalName);
    if (it == cloningPen.end())
    {
        cerr << "Could not find animal: " << animalName << endl;
        return NULL;
    }
    clones.push_back(it->second);
    Animal* animal = &clones.back();
    animal->setPosition(x, y);
    // animal->showHitBox();
    // animal->showVectors();
    animal->addSolids(solidShapes);
    return animal;
}

// **************** clone management **********************

void Shepherd::checkHit(int mouseX, int mouseY)
{
    for (list<Animal>::iterator it = clones.begin(); it != clones.end(); ++it)
    {
        if (it->hit(mouseX, mouseY))
        {
            score += it->getScore();
            it->kill();
            dyingClones.splice(dyingClones.cbegin(), clones, it);
            break; // break so that only one hit will be registered even when there are overlapping animals
        }
    }
}

bool deadAnimal (Animal& animal) { return animal.isDead(); }

void Shepherd::render()
{
    dyingClones.remove_if(deadAnimal);
    for (Animal& it: dyingClones) it.render();
    for (Animal& it: clones) it.render();
}
