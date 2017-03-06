#include "CastleWars.h"

using namespace bkengine;


void CastleWars::loadConfig()
{
    auto &options = addData<OptionStorage>("options");
    settingsInterface->loadFromFile("config.ini");

    if (settingsInterface->hasValue("Player1.up")) {
        options.player1.up = settingsInterface->get("Player1.up");
    } else {
        options.player1.up = Keys::UP;
    }

    if (settingsInterface->hasValue("Player1.left")) {
        options.player1.left = settingsInterface->get("Player1.left");
    } else {
        options.player1.left = Keys::LEFT;
    }

    if (settingsInterface->hasValue("Player1.right")) {
        options.player1.right = settingsInterface->get("Player1.right");
    } else {
        options.player1.right = Keys::RIGHT;
    }

    if (settingsInterface->hasValue("Player1.action")) {
        options.player1.action = settingsInterface->get("Player1.action");
    } else {
        options.player1.action = Keys::RCTRL;
    }

    if (settingsInterface->hasValue("Player2.up")) {
        options.player2.up = settingsInterface->get("Player2.up");
    } else {
        options.player2.up = Keys::W;
    }

    if (settingsInterface->hasValue("Player2.left")) {
        options.player2.left = settingsInterface->get("Player2.left");
    } else {
        options.player2.left = Keys::A;
    }

    if (settingsInterface->hasValue("Player2.right")) {
        options.player2.right = settingsInterface->get("Player2.right");
    } else {
        options.player2.right = Keys::D;
    }

    if (settingsInterface->hasValue("Player2.action")) {
        options.player2.action = settingsInterface->get("Player2.action");
    } else {
        options.player2.action = Keys::LCTRL;
    }

    if (settingsInterface->hasValue("resolution")) {
        options.resolutionIndex = std::stoi(settingsInterface->get("resolution"));
    } else {
        options.resolutionIndex = 2;
    }
}

void CastleWars::setupEnvironment()
{
    Logger::UseStdout(true);
    Logger::SetLevel(0);
    Fonts::registerFont("Meath.ttf", 0, "meath");
    Fonts::registerFont("FUTURAB.ttf", 0, "futurab");
    setIcon("icon.ico");
    setSettingsInterface<INISettingsInterface>();
    loadConfig();
    Resolution resolution = getData<OptionStorage>("options").getResolution();
    resizeWindow(resolution.w, resolution.h);
    setWindowTitle("CastleWars3");
}

void CastleWars::setupScenes()
{
    addScene<MainMenu>("mainmenu");
    addScene<Credits>("credits");
    addScene<Options>("options");
}

void CastleWars::teardown()
{
    auto options = getData<OptionStorage>("options");
    settingsInterface->create("Player1.up", options.player1.up);
    settingsInterface->create("Player1.left", options.player1.left);
    settingsInterface->create("Player1.right", options.player1.right);
    settingsInterface->create("Player1.action", options.player1.action);
    settingsInterface->create("Player2.up", options.player2.up);
    settingsInterface->create("Player2.left", options.player2.left);
    settingsInterface->create("Player2.right", options.player2.right);
    settingsInterface->create("Player2.action", options.player2.action);
    settingsInterface->create("resolution",
                              std::to_string(options.resolutionIndex));
    settingsInterface->saveToFile("config.ini");
}

Json::Value CastleWars::serialize() const
{
    auto json = Game::serialize();
    json["type"] = "CASTLEWARS";
    return json;
}
