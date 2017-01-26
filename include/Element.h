///@Author B�hmi

#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include <string>

#include <SDL.h>

#include "Location.h"
#include "Animation.h"

class Element
{
    public:
        Element(const Location &loc, const std::string &description = "", bool isCollidable = false);
        virtual ~Element();

        void setAnimation(int index);
        void addAnimation(Animation &animation);
        Animation &getCurrentAnimation();
        bool hasAnimation();

        virtual int onRender();
        virtual int onLoop();
        virtual int onEvent(SDL_Event *e);



        Location getLocation();
        int getId();
        std::string getDescription();

        void clear();

private:
        SDL_Rect collisionRect;
        Location location;
        bool flipped;
        int id;
        std::string description;
        int frame;
        bool isCollidable = false;
        int currentAnimation;
        std::vector<Animation> animations;
};

#endif // ELEMENT_H
