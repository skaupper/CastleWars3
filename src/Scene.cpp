///@author Kaupper & B�hmi

#include "Scene.h"


Scene::Scene(int id, const std::string &name, Game *game)
{
    Scene::game = game;
    Scene::id = id;
    Scene::name = name;
}

Scene &Scene::operator=(Scene &&scene)
{
    game = scene.game;
    id = scene.id;
    name = std::move(scene.name);
    elements = std::move(scene.elements);
    scene.game = NULL;
    scene.id = 0;
    return *this;
}

Scene::Scene(Scene &&scene)
{
    game = scene.game;
    id = scene.id;
    name = std::move(scene.name);
    elements = std::move(scene.elements);
    scene.game = NULL;
    scene.id = 0;
}

Scene::~Scene()
{
    // print only if game != NULL (game is NULL if the instance has been moved)
    if (game) {
        std::cout << "destruct scene" << std::endl;
    }

    elements.clear();
}

bool Scene::hasElement(int index)
{
    return index < elements.size() && index >= 0;
}

bool Scene::hasElement(const std::string &name)
{
    for (auto &element : elements) {
        if (element->getDescription() == name) {
            return true;
        }
    }

    return false;
}

void Scene::removeElement(const std::string &name)
{
    int index = 0;

    for (auto &element : elements) {
        if (element->getDescription() == name) {
            elements.erase(elements.begin() + index);
            return;
        }

        index++;
    }

    throw "Element not found";
}

void Scene::removeElement(int index)
{
    if (index >= 0 && index < elements.size()) {
        elements.erase(elements.begin() + index);
    } else {
        throw "Element not found";
    }
}

void Scene::onRender()
{
    for (auto &element : elements) {
        element->onRender();
    }
}

void Scene::onLoop()
{
    for (auto &element : elements) {
        element->onLoop();
    }
}

int Scene::onEvent(SDL_Event *event)
{
    int status = 0;

    for (auto &element : elements) {
        status = element->onEvent(event);

        if (status != 0) {
            return status;
        }
    }

    return 0;
}

std::string Scene::getName() const
{
    return name;
}
