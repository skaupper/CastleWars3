///@author Kaupper


#include "Game.h"
#include <iostream>

//FPS = 60
const float SCREEN_TICKS_PER_FRAME = 1000 / 60;


Game::Game(int width, int height, const std::string &title)
{
    Core::getInstance(width, height, title);
    running = false;
    activeScene = -1;
}

Game::~Game()
{
    scenes.clear();
}

void Game::setActiveScene(const std::string &name)
{
    int index = 0;

    for (auto &scene : scenes) {
        if (scene->getName() == name) {
            activeScene = index;
            return;
        }

        index++;
    }

    throw "Scene not found";
}

void Game::setActiveScene(int index)
{
    if (index < scenes.size() && index >= 0) {
        activeScene = index;
    } else {
        throw "Scene not found";
    }
}

bool Game::hasScene(const std::string &name)
{
    for (auto &scene : scenes) {
        if (scene->getName() == name) {
            return true;
        }
    }

    return false;
}

bool Game::hasScene(int index)
{
    return index < scenes.size() && index >= 0;
}
/*
Scene &Game::addScene(const Scene &scene)
{
    scenes.push_back(std::move((Scene &) scene));

    if (scenes.size() == 1) {
        setActiveScene(scene->getName());
    }

    return scenes[scenes.size() - 1];
}

Scene &Game::addScene(int id, const std::string &name))
{
    return addScene(Scene(id, name))
}
*/


void Game::removeScene(const std::string &name)
{
    int index = 0;

    for (auto &scene : scenes) {
        if (scene->getName() == name) {
            scenes.erase(scenes.begin() + index);
            return;
        }

        index++;
    }

    throw "Scene not found";
}

void Game::removeScene(int index)
{
    if (index < scenes.size() && index >= 0) {
        scenes.erase(scenes.begin() + index);
    } else {
        throw "Scene not found";
    }
}

int Game::run()
{
    int status = Core::getInstance().setup();

    if (status != 0) {
        return status;
    }

    SDL_Event event;
    Timer timer;
    running = true;

    while (running) {
        timer.start();

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            onEvent(&event);
        }

        onLoop();
        onRender();
        int frameTicks = timer.getTicks();

        if (frameTicks < SCREEN_TICKS_PER_FRAME) {
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        }

        timer.stop();
    }

    return 0;
}


void Game::onLoop()
{
    if (activeScene > -1) {
        getCurrentScene<Scene>().onLoop();
    }
}

void Game::onEvent(SDL_Event *event)
{
    if (activeScene > -1) {
        getCurrentScene<Scene>().onEvent(event);
    }
}

void Game::onRender()
{
    if (activeScene > -1) {
        SDL_RenderClear(Core::getInstance().getRenderer());
        getCurrentScene<Scene>().onRender();
        SDL_RenderPresent(Core::getInstance().getRenderer());
    }
}
