#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <vector>

#include <bkengine/Game.h>
#include <bkengine/Scene.h>

#include "OptionStorage.h"


class Options : public bkengine::Scene
{
    public:
        using Scene::Scene;

        virtual void setupElements() override;
        virtual bool onEvent(const bkengine::Event &event) override;
        virtual Json::Value serialize() const override;
};

#endif // OPTIONS_H
