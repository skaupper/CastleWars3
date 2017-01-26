#include "Element.h"

Element::Element(const Location &loc, const std::string &description,
                 bool isCollidable) :
    isCollidable(isCollidable),
    frame(0),
    currentAnimation(-1),
    description(description),
    location(loc),
    flipped(false)
{
}

Location Element::getLocation()
{
    return Element::location;
}

void Element::setAnimation(int index)
{
    if (index >= animations.size() || index < 0) {
        currentAnimation = 0;
    } else {
        currentAnimation = index;
    }
}

#include <iostream>

void Element::onRender()
{
    if (hasAnimation(currentAnimation)) {
        frame++;
        Animation &animation = getCurrentAnimation<Animation>();

        if (animation.hasTexture(0)) {
            animation.getNextTexture().onRender(location, flipped);
        }
    }
}

void Element::onLoop()
{
}

int Element::onEvent(SDL_Event *e)
{
    return 0;
}

bool Element::hasAnimation(int index)
{
    return index >= 0 && index < animations.size();
}

bool Element::hasAnimation(const std::string &name)
{
    for (auto &animation : animations) {
        if (animation->getDescription() == name) {
            return true;
        }
    }

    return false;
}

Element::~Element()
{
    animations.clear();
}

std::string Element::getDescription()
{
    return description;
}
