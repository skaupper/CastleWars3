#ifndef ENTITY_H
#define ENTITY_H
#include "Element.h"
#include "Scene.h"

class Scene;

class Entity : public Element
{
    public:
        Entity(Location *loc, Scene *parentScene, string descr = "",
               bool isCollidable = false);
        virtual ~Entity();

        void move(float x, float y);
        void moveTo(float x, float y);
        bool collidesWith(Element *other, void (*func)(Entity *) = NULL);

        Scene *parentScene = NULL;
};

#endif // ENTITY_H
