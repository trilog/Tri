#include "Animal.h"

// **************** Con/Destructors ***********************

Animal::Animal():
soundManager(NULL), 
state(asStanding), currentClip(0), flip(SDL_FLIP_NONE),
hitBoxShown(false), vectorsShown(false),
maxVelocity(10), maxPoints(10),
theta(0), velocity(0)
{
}

// **************** setImage ******************************

void Animal::setImage(DTexture* _texture, int x, int y)
{
    texture = _texture;
    setPosition(x, y);
}

// **************** getTheta ******************************

float Animal::calcTheta()
{
    if (coincident()) return 0;
    else return atan2((float) (dest.y - pos.y), (float) (dest.x - pos.x));
}

// **************** render ********************************

void Animal::render()
{
    switch (state)
    {
        case asDead:     stateDead();     break;
        case asStanding: stateStanding(); break;
        case asWalking:  stateWalking();  break;
        case asDying:    stateDying();    break;
        case asEating:   stateEating();   break;
        default:         return;          break;
    }

    texture->renderAdvanced(pos.x, pos.y, clips.at(currentClip), theta, flip);

    if (hitBoxShown)
    {
        polygon.set(clips.at(currentClip), pos, flip);
        polygon.absoluteAngle(getTheta());
        polygon.render(texture->getRenderer());
    }
    if (vectorsShown)
    {
        SDL_Color blue = { 0x22, 0x22, 0x99, 0xFF };
        journey.p1 = pos;
        journey.render(texture->getRenderer(), blue);
    }
}

// **************** getDistance ***************************

float Animal::getDistance()
{
    float x = (float) (pos.x - dest.x);
    float y = (float) (pos.y - dest.y);
    return sqrt((x * x) + (y * y));
}

// **************** setDestination ************************

void Animal::setDestination(DPoint& point)
{
    if ((state == asDying) || (state == asDead)) return;
    journey.p1 = pos;
    journey.p2 = point;
    for (DPolygon* shape: solidShapes) shape->clip(journey);
    dest = journey.p2;
    theta = calcTheta();
    velocity = maxVelocity;
    state = asWalking;
    timer.start();
}

// **************** setClip *******************************

void Animal::setClip(string name, int x, int y, int w, int h, int focusX, int focusY)
{
   ClipInfo clip;
   clip.name = name;
   clip.clip  = { x, y, w, h };
   clip.focus = { focusX, focusY };
   clips.push_back(clip);
}

// **************** hit ***********************************

bool Animal::hit(int x, int y)
{
    if ((state == asDying) || (state == asDead)) return false;
    polygon.set(clips.at(currentClip), pos);
    polygon.absoluteAngle(getTheta());
    return polygon.hit(x, y);
}

// **************** kill **********************************

int Animal::kill()
{
    state = asDying;
    velocity = 0;
    currentClip = 3;
    timer.start();
    if (soundManager != NULL) soundManager->playSound("Cat-Whimper");
    return maxPoints;
}

// **************** states ********************************

void Animal::stateDead()
{
    texture->setAlpha(0);
    return;
}

void Animal::stateDying()
{
    int alpha = 255 - timer.elapsed()/2;
    if (alpha < 0)
    {
        alpha = 0;
        state = asDead;
        timer.stop();
    }
    texture->setAlpha(alpha);
}

void Animal::stateWalking()
{
    texture->setAlpha(255);
    float currentDistance = getDistance();
    theta = calcTheta();
    flip = (fabs(theta) > 0.5 * M_PI) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
    velocity = maxVelocity;
    if (velocity > maxVelocity) velocity = maxVelocity;
    if (currentDistance > velocity)
    {
        currentClip = (timer.elapsed()/150) % 2;
        pos.x += (int) (velocity * cos(theta));
        pos.y += (int) (velocity * sin(theta));
    }
    else 
    {
        state = asEating;
        pos.x = dest.x;
        pos.y = dest.y;
        velocity = 0;
    }
}

void Animal::stateEating()
{
    texture->setAlpha(255);
    currentClip = (timer.elapsed()/150) % 2 + 4;
}

void Animal::stateStanding()
{
    texture->setAlpha(255);
    currentClip = 0;
}
