#include <iostream>

#include <bkengine/Core.h>
#include <bkengine/Game.h>
#include <bkengine/Scene.h>
#include <bkengine/Entity.h>

using namespace bkengine;

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

class TestEntity : public Entity
{
    public:
        explicit TestEntity(const std::string &descr = "", const Location &loc = {0, 0},
                            bool isCollidable = false) : Entity(descr, loc, isCollidable) {}
        virtual void onLoop()
        {
            move(1, 0);
        }
};

int main(int argc, char *argv[])
{
    Logger::UseStdout(true);
    Logger::SetLevel(0);
    Core::init();

    try {
        Fonts::registerFont("Meath.ttf", 30, "meath");
        Game game(1024, 768, "TestWindow");
        TestScene &scene = game.addScene<TestScene>("scene1");
        /*Element &element = scene.addElement<Element>("testelement");
        Animation &animation = element.addAnimation<Animation>("testanimation", 60);
        animation.addImage("jo.png");
        animation.addTexture(Texture("meath", "DAS IST DER JO!", {0xFF, 0x00, 0x00, 0xFF}, {800, 100},
                                     TextQuality::BLENDED));
        */TestEntity &entity = scene.addElement<TestEntity>("testentity", Location());
        entity.addAnimation<Animation>().addTexture(Texture("meath",
                "test_string", {0, 50}));
        game.run();
    } catch (const char *s) {
        Logger::LogCritical(s);
    }

    Core::quit();
    return 0;
}
