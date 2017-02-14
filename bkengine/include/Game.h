///@author Kaupper

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <vector>
#include <string>
#include <memory>

#include "Core.h"
#include "Scene.h"
#include "Timer.h"

class Scene;

class Game
{
    public:
        Game(int width, int height, const std::string &title);
        virtual ~Game();

        void setActiveScene(const std::string &name);
        void setActiveScene(int index);

        bool hasScene(const std::string &name);
        bool hasScene(int index);

        void removeScene(const std::string &name);
        void removeScene(int index);


        template <typename T> T &addScene(const T &);
        template <typename T> T &addScene(const std::shared_ptr<T> &);
        template <typename T, typename... Params> T &addScene(Params...);

        template <typename T> T &getScene(const std::string &name);
        template <typename T, typename... Params> T &getScene(int index);

        template <typename T> T &getCurrentScene();
        int run();
        void stop();

    private:
        std::vector<std::shared_ptr<Scene>> scenes;
        int activeScene;
        bool running;
        Timer timer;

        void onLoop();
        int onEvent(SDL_Event *);
        void onRender();
};


template <typename T> T &Game::addScene(const T &scene)
{
    return addScene<T>(std::make_shared<T>(std::move((T &) scene)));
}

template <typename T> T &Game::addScene(const std::shared_ptr<T> &scene)
{
    scenes.push_back(scene);

    if (scenes.size() == 1) {
        activeScene = 0;
    }

    return *((T *) scenes.back().get());
}

template <typename T, typename... Params> T &Game::addScene(Params... params)
{
    return addScene<T>(std::make_shared<T>(params...));
}


template <typename T> T &Game::getScene(const std::string &name)
{
    for (auto &scene : scenes) {
        if (scene->getName() == name) {
            return *((T *) scene.get());
        }
    }

    Logger::LogCritical("Game::getScene(const std::string & = " + name +
                        "): Scene not found");
    throw "Scene not found";
}

template <typename T, typename... Params> T &Game::getScene(int index)
{
    if (index >= 0 && index < scenes.size()) {
        return *((T *) scenes[index].get());
    }

    Logger::LogCritical("Game::getScene(int = " + std::to_string(
                            index) + "): Scene not found");
    throw "Scene not found";
}

template <typename T> T &Game::getCurrentScene()
{
    if (activeScene == -1) {
        Logger::LogCritical("Game::getCurrentScene(): Scene not found");
        throw "No scene added";
    }

    return *((T *) scenes[activeScene].get());
}

#endif // GAME_H_INCLUDED
