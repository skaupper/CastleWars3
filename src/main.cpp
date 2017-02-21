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
        explicit TestEntity(Scene *parentScene, const std::string &descr = "", const Rect &renderBox = Rect(),
                            int collisionLayer = -1) : Entity(parentScene, descr, renderBox, collisionLayer) {}
        int direction = 0;
        int id = 0;
        void setId(int id) { this->id = id; }
        virtual void onLoop()
        {
            move(0.1 * direction, 0);
        }

        virtual int onEvent(SDL_Event *event)
        {
            if (event->type == SDL_KEYDOWN) {
                SDL_KeyboardEvent *kb = (SDL_KeyboardEvent *) event;
                SDL_Keycode code = kb->keysym.sym;
                /*
                SDL_Keycode right = (id == 1 ? SDLK_RIGHT : SDLK_d);
                SDL_Keycode left = (id == 1 ? SDLK_LEFT : SDLK_a);
                if (right == code) {
                    direction = 1;
                } else if (left == code) {
                    direction = -1;
                } else {
                    direction = 0;
                }
                */
                static bool once = false;
                if (id == 1 && code == SDLK_RETURN) {
                    if(!once) {
                        move(80, 20);
                    }
                    once = true;
                }
            }
            return 0;
        }
};

int main(int argc, char *argv[])
{
    Logger::UseStdout(true);
    Logger::SetLevel(0);

    try {
        Fonts::registerFont("Meath.ttf", 30, "meath");
        Game game(1024, 768, "TestWindow");
        game.setIcon("icon.ico");
        TestScene &scene = game.addScene<TestScene>("scene1");
        TestEntity &entity1 = scene.addElement<TestEntity>("1", Rect(0, 0, 20, 50), 1);
        entity1.setId(1);
        TestEntity &entity2 = scene.addElement<TestEntity>("2", Rect(80, 50, 20, 50), 1);
        entity2.setId(2);
        entity1.addAnimation<Animation>().addTexture(Texture("jo.png", Rect(100, 100)));
        entity2.addAnimation<Animation>().addTexture(Texture("jo.png", Rect(100, 100)));
        game.run();
    } catch (const char *s) {
        Logger::LogCritical(s);
    }

    Core::quit();
    return 0;
}
