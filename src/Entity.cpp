#include "Entity.h"
#include <iostream>

//standard konstruktor
Entity::Entity(Location *loc, Scene *parentScene, string descr,
               bool isCollidable) : Element(loc, descr, isCollidable)
{
    Entity::parentScene = parentScene;
}

//entität wird um x/y bewegt
void Entity::move(float x, float y)
{
    Entity::location->x += x;
    Entity::location->y += y;
}


//entität wird zur position loc bewegt
void Entity::moveTo(float x, float y)
{
    Entity::location->x = x;
    Entity::location->y = y;
}

//prüft ob die entität mit einem anderem element kollidiert
bool Entity::collidesWith(Element *other, void (*func)(Entity *))
{
    float x = location->x;
    float y = location->y;
    float h = collisionRect->h;
    float w = collisionRect->w;
    float otherx = other->location->x;
    float othery = other->location->y;
    float otherh = other->collisionRect->h;
    float otherw = other->collisionRect->w;
    bool collides = false;

    if ((x >= otherx && x <= otherx + otherw) && (y >= othery
            && y <= othery + otherh)) {
        collides = true;
    }

    if ((x + w >= otherx && x + w <= otherx + otherw) && (y >= othery
            && y <= othery + otherh)) {
        collides = true;
    }

    if ((x < otherx && x + w > otherx + otherw) && (y >= othery
            && y <= othery + otherh)) {
        collides = true;
    }

    if ((x >= otherx && x <= otherx + otherw) && (y + h >= othery
            && y + h <= othery + otherh)) {
        collides = true;
    }

    if ((x + w >= otherx && x + w <= otherx + otherw) && (y + h >= othery
            && y + h <= othery + otherh)) {
        collides = true;
    }

    if ((x < otherx && x + w > otherx + otherw) && (y + h >= othery
            && y + h <= othery + otherh)) {
        collides = true;
    }

    if ((x >= otherx && x <= otherx + otherw) && (y <= othery
            && y + h >= othery + otherh)) {
        collides = true;
    }

    if ((x + w >= otherx && x + w <= otherx + otherw) && (y <= othery
            && y + h >= othery + otherh)) {
        collides = true;
    }

    if ((x < otherx && x + w > otherx + otherw) && (y <= othery
            && y + h >= othery + otherh)) {
        collides = true;
    }

    /*
    if((x < otherx && x + w > otherx + otherw) && ((y < othery + otherh&& y >othery) || (y + h > othery&& y + h < othery + otherh)))
        return true;
    */
    if (collides && other->descr == "box") {
        func(this);
        return false;
    }

    return collides;
}

Entity::~Entity()
{
    delete location;
    delete collisionRect;
    clear();
    delete animations;
}
