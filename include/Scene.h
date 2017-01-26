///@author Kaupper & B�hmi

#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include "Element.h"
#include "KeyboardLayout.h"
#include "Entity.h"

class Element;
class Game;

class Scene
{
    public:
        Scene(int id, const std::string &name, Game *game);
        Scene(Scene &&scene);
        Scene &operator=(Scene &&scene);
        virtual ~Scene();

        bool hasElement(const std::string &name);
        bool hasElement(int index);

        void removeElement(const std::string &name);
        void removeElement(int index);


        template <typename T> T &addElement(const T &);
        template <typename T> T &addElement(const std::shared_ptr<T> &);
        template <typename T, typename... Params> T &addElement(Params...);

        template <typename T> T &getElement(const std::string &name);
        template <typename T, typename... Params> T &getElement(int index);

        virtual void onLoop();
        virtual void onRender();
        virtual int onEvent(SDL_Event *);

        std::string getName() const;

    private:
        std::string name;
        int id;

        std::vector<std::shared_ptr<Element>> elements;
        Game *game;
};

template <typename T> T &Scene::addElement(const T &element)
{
    return addElement<T>(std::make_shared<T>(std::move((T &) element)));
}

template <typename T> T &Scene::addElement(const std::shared_ptr<T> &element)
{
    elements.push_back(element);
    return *((T *) elements.back().get());
}

template <typename T, typename... Params> T &Scene::addElement(Params... params)
{
    return addElement<T>(std::make_shared<T>(params...));
}


template <typename T> T &Scene::getElement(const std::string &name)
{
    for (auto &element : elements) {
        if (element->getDescription() == name) {
            return *((T *) element.get());
        }
    }

    throw "Element not found";
}

template <typename T, typename... Params> T &Scene::getElement(int index)
{
    if (index >= 0 && index < elements.size()) {
        return *((T *) elements[index].get());
    }

    throw "Element not found";
}

#endif // SCENE_H_INCLUDED
