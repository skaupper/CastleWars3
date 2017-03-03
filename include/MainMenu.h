#ifndef MAINMENU_H
#define MAINMENU_H

#include <bkengine/Game.h>
#include <bkengine/Scene.h>

#include "OptionStorage.h"


class MainMenu : public bkengine::Scene
{
    public:
        using Scene::Scene;

        virtual void setupElements() override;
        virtual bool onEvent(const bkengine::Event &) override;
        virtual Json::Value serialize() const override;
};

#endif // MAINMENU_H
