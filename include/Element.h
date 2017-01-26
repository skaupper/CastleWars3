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
        Element(const Location &loc, const std::string &description = "",
                bool isCollidable = false);
        virtual ~Element();

        void setAnimation(int index);
        void addAnimation(Animation &animation);
        Animation &getCurrentAnimation();


        bool hasAnimation(const std::string &name);
        bool hasAnimation(int index);

        void removeAnimation(const std::string &name);
        void removeAnimation(int index);


        template <typename T> T &addAnimation(const T &);
        template <typename T> T &addAnimation(const std::shared_ptr<T> &);
        template <typename T, typename... Params> T &addAnimation(Params...);

        template <typename T> T &getAnimation(const std::string &name);
        template <typename T, typename... Params> T &getAnimation(int index);

        template <typename T> T &getCurrentAnimation();

        virtual void onRender();
        virtual void onLoop();
        virtual int onEvent(SDL_Event *e);

        Location getLocation();
        int getId();
        std::string getDescription();

    private:
        SDL_Rect collisionRect;
        Location location;
        bool flipped;
        std::string description;
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

    throw "Animation not found";
}

template <typename T, typename... Params> T &Element::getAnimation(int index)
{
    if (index >= 0 && index < animations.size()) {
        return *((T *) animations[index].get());
    }

    throw "Animation not found";
}


template <typename T> T &Element::getCurrentAnimation()
{
    return getAnimation<T>(currentAnimation);
}

#endif // ELEMENT_H
