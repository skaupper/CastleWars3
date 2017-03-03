#ifndef CREDITS_H
#define CREDITS_H

#include <bkengine/Game.h>
#include <bkengine/Scene.h>
#include <bkengine/Entity.h>
#include <bkengine/Event.h>
#include <bkengine/Misc.h>

class Credits : public bkengine::Scene
{
    public:
        using Scene::Scene;

        virtual bool onEvent(const bkengine::Event &event) override;
        virtual void onLoop() override;
        virtual void setupElements() override;
        virtual Json::Value serialize() const override;

    private:
        void createElements();
        void resetLocations();
};
#endif // CREDITS_H
