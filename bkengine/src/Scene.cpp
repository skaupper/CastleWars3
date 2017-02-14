///@author Kaupper & B�hmi

#include "Scene.h"


Scene::Scene(const std::string &name)
{
    Scene::name = name;
}

Scene &Scene::operator=(Scene &&scene)
{
    name = std::move(scene.name);
    elements = std::move(scene.elements);
    return *this;
}

Scene::Scene(Scene &&scene)
{
    name = std::move(scene.name);
    elements = std::move(scene.elements);
}

Scene::~Scene()
{
    Logger::LogDebug("Scene::~Scene(): destruct scene");
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

    Logger::LogCritical("Scene::removeElement(const std::string & = " + name +
                        "): Element not found");
    throw "Element not found";
}

void Scene::removeElement(int index)
{
    if (index >= 0 && index < elements.size()) {
        elements.erase(elements.begin() + index);
    } else {
        Logger::LogCritical("Scene::removeElement(int = " + std::to_string(
                                index) + "): Element not found");
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
