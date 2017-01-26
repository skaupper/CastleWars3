///@Author B�hmi

#include "Element.h"

// loc:             Die Location, auf der das Element erscheint
// animations:      Ein Pointer auf den Start einer Liste von Animations-Pointern
// animationCount:  Anzahl der Animationen
Element::Element(Location &loc, const std::string &description, bool isCollidable)
{
    Element::isCollidable = isCollidable;
    Element::frame = 0;
    Element::currentAnimation = 0;
    Element::description = description;
    Element::location = loc;
    Element::flipped = false;
    currentAnimation = -1;
}

// Gibt die Location zur�ck
Location Element::getLocation()
{
    return Element::location;
}

// Gibt die ID zur�ck
int Element::getId()
{
    return Element::id;
}

// Setzt die CurrentAnimation auf einen index im animations-Array
void Element::setAnimation(int index)
{
    if (index >= animations.size() || index < 0) {
        currentAnimation = 0;
    } else {
        currentAnimation = index;
    }
}

void Element::addAnimation(Animation &animation)
{
    animations.push_back(animation);
    collisionRect = animation.getTexture().size;
}

// Ruft die Render-Methode der aktuellen Textur der aktuellen Animation auf
int Element::onRender()
{
    if (currentAnimation > -1) {
        frame++;
        getCurrentAnimation().getTexture().onRender(location, flipped);
    }
}

int Element::onLoop()
{
    return 0;
}

int Element::onEvent(SDL_Event *e)
{
    return 0;
}

Animation &Element::getCurrentAnimation()
{
    return animations[currentAnimation];
}

bool Element::hasAnimation()
{
    return currentAnimation != -1;
}

// Destruktor
Element::~Element()
{
    Element::clear();
}

void Element::clear()
{
    for (auto &animation : animations) {
        animation.clear();
    }

    animations.clear();
}

std::string Element::getDescription()
{
    return description;
}
