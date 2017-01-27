///@author Kaupper

#include <iostream>

#include "Core.h"
#include "Game.h"
#include "Scene.h"

class TestScene : public Scene
{
    public:

        TestScene(int id, const std::string &name, Game *game) : Scene(id, name,
                    game) {}
        virtual int onEvent(SDL_Event *event)
        {
            if (event->type == SDL_MOUSEBUTTONDOWN
                    && ((SDL_MouseButtonEvent *)event)->button == SDL_BUTTON_LEFT) {
                return 1;
            }

            return Scene::onEvent(event);
        }
};

int main(int argc, char *argv[])
{
    std::cout << Core::init() << std::endl;

    try {
        Game game(1024, 768, "TestWindow");
        TestScene &scene = game.addScene<TestScene>(1, "scene1");
        Element &element = scene.addElement<Element>(Location{0, 0}, "testelement");
        Animation &animation = element.addAnimation<Animation>("testanimation", 60);
        animation.addImage("jo.png");
        animation.addText("DAS IST DER JO!", {0xFF, 0x00, 0x00, 0xFF}, 30);
        animation.addImage("jo.png");
        animation.addText("DAS IST DER JO!", {0xFF, 0x00, 0x00, 0xFF}, 30);
        animation.addImage("jo.png");
        animation.addText("DAS IST DER JO!", {0xFF, 0x00, 0x00, 0xFF}, 30);
        animation.addImage("jo.png");
        animation.addText("DAS IST DER JO!", {0xFF, 0x00, 0x00, 0xFF}, 30);
        animation.addImage("jo.png");
        animation.addText("DAS IST DER JO!", {0xFF, 0x00, 0x00, 0xFF}, 30);
        animation.addImage("jo.png");
        animation.addText("DAS IST DER JO!", {0xFF, 0x00, 0x00, 0xFF}, 30);
        animation.addImage("jo.png");
        animation.addText("DAS IST DER JO!", {0xFF, 0x00, 0x00, 0xFF}, 30);
        animation.addImage("jo.png");
        animation.addText("DAS IST DER JO!", {0xFF, 0x00, 0x00, 0xFF}, 30);
        animation.addImage("jo.png");
        animation.addText("DAS IST DER JO!", {0xFF, 0x00, 0x00, 0xFF}, 30);
        animation.addImage("jo.png");
        animation.addText("DAS IST DER JO!", {0xFF, 0x00, 0x00, 0xFF}, 30);
        animation.addImage("jo.png");
        animation.addText("DAS IST DER JO!", {0xFF, 0x00, 0x00, 0xFF}, 30);
        animation.addImage("jo.png");
        animation.addText("DAS IST DER JO!", {0xFF, 0x00, 0x00, 0xFF}, 30);
        animation.addImage("jo.png");
        animation.addText("DAS IST DER JO!", {0xFF, 0x00, 0x00, 0xFF}, 30);
        animation.addImage("jo.png");
        animation.addText("DAS IST DER JO!", {0xFF, 0x00, 0x00, 0xFF}, 30);
        animation.addImage("jo.png");
        animation.addText("DAS IST DER JO!", {0xFF, 0x00, 0x00, 0xFF}, 30);
        std::cout << game.run() << std::endl;
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
