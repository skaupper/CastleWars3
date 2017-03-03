#include "MainMenu.h"
#include <bkengine/Logger.h>

using namespace bkengine;


void MainMenu::setupElements()
{
    addElement<Element>("background").addAnimation<Animation>().addTexture(
        Texture("bg.png"));
    Element &overlay = addElement<Element>("overlay");
    overlay.addAnimation<Animation>("startgame").addTexture(
        Texture("startgame.png"));
    overlay.addAnimation<Animation>("exit").addTexture(Texture("exit.png"));
    overlay.addAnimation<Animation>("options").addTexture(Texture("options.png"));
    overlay.addAnimation<Animation>("credits").addTexture(Texture("credits.png"));
    overlay.activate("startgame");
}

bool MainMenu::onEvent(const Event &event)
{
    static int selected = 0;
    static std::array<std::string, 4> menuPoints = {
        "startgame",
        "credits",
        "exit",
        "options",
    };
    static std::array<std::string, 4> scenes = {
        "game",
        "credits",
        "",
        "options",
    };
    bool selectedChanged = false;
    auto &options = parentGame->getData<OptionStorage>("options");

    if (event.type == EventType::KEYBOARD
            && event.keyboard.state == KeyState::DOWN) {
        Key key = event.keyboard.key;

        if (key == options.player1.right || key == options.player2.right) {
            selectedChanged = true;
            selected = (selected + 1) % menuPoints.size();
        } else if (key == options.player1.left || key == options.player2.left) {
            selectedChanged = true;
            selected = (selected - 1 + menuPoints.size()) % menuPoints.size();
        } else if (key == options.player1.action || key == options.player2.action) {
            if (menuPoints[selected] == "exit") {
                parentGame->stop();
            } else {
                parentGame->activate(scenes[selected]);
            }
        }
    }

    if (selectedChanged) {
        getElement<Element>("overlay").activate(menuPoints[selected]);
    }

    return true;
}


Json::Value MainMenu::serialize() const
{
    auto json = Scene::serialize();
    json["type"] = "MAINMENU";
    return json;
}
