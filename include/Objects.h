#ifndef OBJECTS_H
#define OBJECTS_H

#include "FormsFunctions.h"
#include "Element.h"
#include <time.h>
#include <stdlib.h>

extern SDL_Rect *gamemap;
void (*func)(Entity *);

int objectOnLoop(Scene *scene)
{
    Entity *e = (Entity *)scene->getElement("box");
    e->move(0, getRelativeSize(0, 1.5)->h);

    for (int i = 1; i < scene->countElements(); i++) {
        Element *el = scene->getElement(i);

        if ((e != (Entity *)el && el->isCollidable && e->collidesWith(el, func))
                || !(e->location->y > gamemap->y
                     && e->location->y + e->collisionRect->h < gamemap->y + gamemap->h)) {
            e->move(0, -1 * getRelativeSize(0, 1.5)->h);
            break;
        }
    }
}

void getNewObject(Scene *scene)
{
    bool added = true;
    int s = 5;
    SDL_Rect *size = getRelativeSize(s, s * getRelativeSize(100,
                                     0)->w / getRelativeSize(0, 100)->h);
    Entity *e;
    Animation *a;

    do {
        int x = 0;
        int y = 0;

        while (x + size->w > gamemap->x + gamemap->w || x < gamemap->x) {
            x = rand() % (getRelativeSize(90, 100)->w) + getRelativeSize(5, 0)->w;
        }

        while (y + size->h > gamemap->y + gamemap->h || y < gamemap->y) {
            y = rand() % (getRelativeSize(90, 100)->h) + getRelativeSize(0, 5)->h;
        }

        e = new Entity(new Location{x, y}, scene, "box", true);
        a = new Animation("box", -1);
        a->addImage("res/box.png", size);
        e->addAnimation(a);
        added = true;

        for (int i = 1; i < scene->countElements(); i++)
            if (e->collidesWith(scene->getElement(i), func)) {
                added = false;
                a->clear();
                delete a;
                break;
            }

        if (added) {
            scene->addElement(e);
        }
    } while (!added);
}

void removeObject(Scene *scene)
{
    if (scene->getElement("box") != NULL) {
        scene->removeElement("box");
    }
}



#endif // OBJECTS_H
