///@author Kaupper

#include <iostream>

#include "Core.h"
#include "Game.h"
#include "Scene.h"
/*
#include "Player.h"
#include "MainMenu.h"
#include "Options.h"
#include "Credits.h"
#include "StartGame.h"
*/

class TestScene : public Scene
{
    public:
        TestScene(int id, const std::string &name, Game *game) : Scene(id, name, game)
        {
            std::cout << getName() << std::endl;
        }
};

int main(int argc, char *argv[])
{
    Core::init();

    try {
        Game game(1024, 768, "TestWindow");
        Scene &scene = game.addScene<Scene>(1, "scene1");
        game.run();
    } catch (const char *s) {
        std::cout << s << std::endl;
    }

    Core::quit();
    /*
    if (load() == -1) {
        std::cout << "Failed to load config file!" << std::endl;
    } else {
        Game game(possibleResolutions[*resolution].width,
                  possibleResolutions[*resolution].height, "Castle Wars");
        game.addScene(loadMainMenu(game));
        game.addScene(loadOptions(game));
        game.addScene(loadCredits(game));
        game.addScene(loadGame(game));
        game.run();
        game.clear();
    }*/
    return 0;
}
