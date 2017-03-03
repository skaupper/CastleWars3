#include "CastleWars.h"
#include <json/json.h>
#include <bkengine/GameSerializer.h>

using namespace bkengine;


int main(int argc, char *argv[])
{/*
    CastleWars cw(1024, 768, "TestWindow");
    Logger::UseStdout(true);
    Logger::SetLevel(0);
    Fonts::registerFont("Meath.ttf", 0, "meath");
    Fonts::registerFont("FUTURAB.ttf", 0, "futurab");
    cw.setIcon("icon.ico");
    cw.setSettingsInterface<INISettingsInterface>();
    cw.loadConfig();
    Resolution resolution = cw.getData<OptionStorage>("options").getResolution();
    cw.resizeWindow(resolution.w, resolution.h);
    cw.setWindowTitle("CastleWars3");

    cw.addScene<MainMenu>("mainmenu");
    cw.addScene<Credits>("credits");
    cw.addScene<Options>("options");
    Logger::LogDebug(Json::StyledWriter().write(cw.serialize()));
    return 0;*/

    Serializer::addType<Game>("GAME");
    Serializer::addType<CastleWars>("CASTLEWARS");
    Serializer::addType<Scene>("SCENE");
    Serializer::addType<Options>("OPTIONS");
    Serializer::addType<Credits>("CREDITS");
    Serializer::addType<MainMenu>("MAINMENU");
    Serializer::addType<Element>("ELEMENT");
    Serializer::addType<Animation>("ANIMATION");
    Serializer::addType<Texture>("TEXTURE");
    Serializer::addType<INISettingsInterface>("ini");
    Serializer::addType<SDLEventInterface>("sdl_event");


    std::string fileName = "cw.json";
    std::ifstream file(fileName);
    long int length = 0;
    file.seekg(0, file.end);
    length = file.tellg();
    file.seekg(0, file.beg);

    char *buffer = new char[length + 1];
    buffer[length] = 0;

    file.read(buffer, length);

    Json::Value root;
    Json::Reader reader;
    bool successful = reader.parse(buffer, root);

    delete[] buffer;
    file.close();
    auto game = GameSerializer::deserialize<Game>(root);
    game->run();
    return 0;
}
