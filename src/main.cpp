#include <iostream>

#include <bkengine/Core.h>
#include <bkengine/Game.h>
#include <bkengine/Scene.h>
#include <bkengine/Entity.h>
#include <bkengine/Logger.h>

#include "MainMenu.h"
#include "Credits.h"

using namespace bkengine;

/*
class TestScene : public Scene
{
    public:
        TestScene(const std::string &name) : Scene(name) {}
        virtual bool onEvent(const Event &event)
        {
            if (event.type == EventType::MOUSE && event.mouse.button == Buttons::LEFT) {
                Logger::LogDebug("quit");
                return false;
            }
            return Scene::onEvent(event);
        }
};

class TestEntity : public Entity
{
    public:
        explicit TestEntity(Scene *parentScene, const std::string &descr = "", const Rect &renderBox = Rect(),
                            int collisionLayer = -1) : Entity(parentScene, descr, renderBox, collisionLayer) {}
        int direction = 0;
        int id = 0;
        void setId(int id) { this->id = id; }
        virtual void onLoop()
        {
            move(0.1 * direction, 0);
        }

        virtual bool onEvent(const Event &event)
        {
            if (event.type == EventType::KEYBOARD) {
                Keys key = event.keyboard.key;
                Logger::LogDebug(key.toString());
                Logger::LogDebug(event.keyboard.state == KeyState::DOWN ? "DOWN" : "UP");

                Keys right = (id == 1 ? Keys::RIGHT : Keys::D);
                Keys left = (id == 1 ? Keys::LEFT : Keys::A);
                if (right == key) {
                    direction = 1;
                } else if (left == key) {
                    direction = -1;
                } else {
                    direction = 0;
                }

                static bool once = false;
                if (id == 1 && key == Keys::RETURN) {
                    if(!once) {
                        move(80, 20);
                    }
                    once = true;
                }
            }
            return true;
        }
};
*/

int main(int argc, char *argv[])
{
    Logger::UseStdout(true);
    Logger::SetLevel(0);

    Fonts::registerFont("Meath.ttf", 30, "meath");
    Fonts::registerFont("FUTURAB.ttf", 30, "futurab");
    Game game(1024, 768, "TestWindow");
    game.setIcon("icon.ico");
    game.addScene<MainMenu>("mainmenu");
    game.addScene<Credits>("credits");
    /*
    TestScene &scene = game.addScene<TestScene>("scene1");
    TestEntity &entity1 = scene.addElement<TestEntity>("1", Rect(0, 0, 20, 50), 1);
    entity1.setId(1);
    TestEntity &entity2 = scene.addElement<TestEntity>("2", Rect(80, 50, 20, 50), 1);
    entity2.setId(2);
    entity2.applyCollisionBox({50, 0, 50, 100});
    entity1.addAnimation<Animation>().addTexture(Texture("jo.png", Rect(100, 100)));
    entity2.addAnimation<Animation>().addTexture(Texture("jo.png", Rect(100, 100)));
    */
    game.run();

    Core::quit();
    return 0;
}
