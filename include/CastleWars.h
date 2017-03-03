#ifndef CASTLEWARS_H
#define CASTLEWARS_H

#include <bkengine/Game.h>
#include <bkengine/Fonts.h>
#include <bkengine/Logger.h>
#include <bkengine/SDLEventInterface.h>
#include <bkengine/INISettingsInterface.h>

#include "OptionStorage.h"
#include "MainMenu.h"
#include "Credits.h"
#include "Options.h"


class CastleWars : public bkengine::Game
{
    private:

    public:
        using Game::Game;

        virtual void setupEnvironment() override;
        virtual void setupScenes() override;
        virtual void teardown() override;
        virtual Json::Value serialize() const override;
        void loadConfig();
};

#endif
