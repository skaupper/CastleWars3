///@author Kaupper

#include <iostream>

#include "Core.h"
#include "Game.h"
#include "Scene.h"

class TestScene : public Scene
{
    public:
        TestScene(const std::string &name) : Scene(name) {}
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
    // Logger::SetDebugStandardOut(false);
    // Logger::SetInfoStandardOut(false);
    // Logger::SetWarningStandardOut(false);
    // Logger::SetErrorStandardOut(false);
    // Logger::SetCriticalStandardOut(false);
    Core::init();

    try {
        Game game(1024, 768, "TestWindow");
        TestScene &scene = game.addScene<TestScene>("scene1");
        Element &element = scene.addElement<Element>("testelement");
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
        game.run();
    } catch (const char *s) {
        Logger::LogCritical(s);
    }

    Core::quit();
    return 0;
}
