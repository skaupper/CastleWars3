///@Author B�hmi

#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include <string>
#include <memory>

#include <SDL.h>

#include "Location.h"
#include "Animation.h"

class Element
{
    public:
        Element(const std::string &description = "", const Location &loc = {0, 0},
                bool isCollidable = false);
        virtual ~Element();

        void setAnimation(unsigned int index);
        void addAnimation(Animation &animation);
        Animation &getCurrentAnimation();


        bool hasAnimation(const std::string &name);
        bool hasAnimation(unsigned int index);

        void removeAnimation(const std::string &name);
        void removeAnimation(unsigned int index);


        template <typename T> T &addAnimation(const T &);
        template <typename T> T &addAnimation(const std::shared_ptr<T> &);
        template <typename T, typename... Params> T &addAnimation(Params...);

        template <typename T> T &getAnimation(const std::string &name);
        template <typename T, typename... Params> T &getAnimation(unsigned int index);

        template <typename T> T &getCurrentAnimation();

        virtual void onRender();
        virtual void onLoop();
        virtual int onEvent(SDL_Event *e);

        Location getLocation();
        std::string getDescription();

    protected:
        std::string description;
        SDL_Rect collisionRect;
        Location location;
        bool flipped;
        int frame;
        bool isCollidable = false;
        int currentAnimation;
        std::vector<std::shared_ptr<Animation>> animations;
};

template <typename T> T &Element::addAnimation(const T &animation)
{
    return addAnimation<T>(std::make_shared<T>(std::move((T &) animation)));
}

template <typename T> T &Element::addAnimation(const std::shared_ptr<T>
        &animation)
{
    animations.push_back(animation);

    if (animations.size() == 1) {
        currentAnimation = 0;
    }

    return *((T *) animations.back().get());
}

template <typename T, typename... Params> T &Element::addAnimation(
    Params... params)
{
    return addAnimation<T>(std::make_shared<T>(params...));
}


template <typename T> T &Element::getAnimation(const std::string &name)
{
    for (auto &animation : animations) {
        if (animation->getDescription() == name) {
            return *((T *) animation.get());
        }
    }

    Logger::LogCritical("Element::getAnimation(const std::string & = " + name +
                        "): Animation not found");
    throw "Animation not found";
}

template <typename T, typename... Params> T &Element::getAnimation(unsigned int index)
{
    if (index < animations.size()) {
        return *((T *) animations[index].get());
    }

    Logger::LogCritical("Element::getAnimation(int = " + std::to_string(
                            index) + "): Animation not found");
    throw "Animation not found";
}


template <typename T> T &Element::getCurrentAnimation()
{
    return getAnimation<T>(currentAnimation);
}

#endif // ELEMENT_H
