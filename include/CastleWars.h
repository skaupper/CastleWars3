#ifndef CASTLEWARS_H
#define CASTLEWARS_H

#include <bkengine/Game.h>
#include <bkengine/Fonts.h>
#include <bkengine/Logger.h>
#include <bkengine/INISettingsInterface.h>

#include "OptionStorage.h"
#include "MainMenu.h"
#include "Credits.h"
#include "Options.h"


class CastleWars : public bkengine::Game
{
    private:
        void loadConfig();

    public:
        using Game::Game;

        virtual void setup() override;
        virtual void teardown() override;
};

#endif
