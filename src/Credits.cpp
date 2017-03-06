#include "Credits.h"

using namespace bkengine;


bool Credits::onEvent(const Event &event)
{
    if (event.type == EventType::KEYBOARD) {
        if (event.keyboard.key == Keys::ESCAPE) {
            resetLocations();
            parentGame->activate("mainmenu");
        }
    }

    return true;
}

void Credits::onLoop()
{
    static bool move = true;

    if (move) {
        for(auto element : elements) {
            if(element->getName() == "background") {
                continue;
            }
            std::static_pointer_cast<Entity>(element)->move(0, -0.075);
        }
    }

    if (getElement<Entity>("lead developers").getRenderBox().y <= 5) {
        move = false;
    }
}

void Credits::setupElements()
{
    addElement<Entity>("background", Rect { 0.f, 0.f, 100, 100 })
    .addAnimation<Animation>().addTexture(Texture("credits_bg.png"));
    addElement<Entity>("lead developers", Rect { 50, 105, 0, 0 })
    .addAnimation<Animation>().addTexture(Texture("futurab", "Developers", Rect { 0, 5.5 },
                                          Color(), TextQuality::BLENDED));
    addElement<Entity>("lead developer sebastian kaupper", Rect { 50, 111, 0, 0 })
    .addAnimation<Animation>().addTexture(Texture("futurab", "Sebastian Kaupper",
                                          Rect { 0, 4 }, Color(), TextQuality::BLENDED));
    addElement<Entity>("lead developer christoph boehmwalder", Rect { 50, 116, 0, 0 })
    .addAnimation<Animation>().addTexture(Texture("futurab",
                                          "Christoph Böhmwalder", Rect { 0, 4 }, Color(), TextQuality::BLENDED));
    addElement<Entity>("designers", Rect { 50, 130, 0, 0 })
    .addAnimation<Animation>().addTexture(Texture("futurab", "Graphic Designers",
                                          Rect { 0, 5.5 }, Color(), TextQuality::BLENDED));
    addElement<Entity>("designer michael berthold", Rect { 50, 137, 0, 0 })
    .addAnimation<Animation>().addTexture(Texture("futurab", "Michael Berthold",
                                          Rect { 0, 4 }, Color(), TextQuality::BLENDED));
    addElement<Entity>("designer dominik hauer", Rect { 50, 142, 0, 0 })
    .addAnimation<Animation>().addTexture(Texture("futurab", "Dominik Hauer", Rect { 0, 4 },
                                          Color(), TextQuality::BLENDED));
    addElement<Entity>("special thanks", Rect { 50, 155, 0, 0 })
    .addAnimation<Animation>().addTexture(Texture("futurab", "Special thanks to",
                                          Rect { 0, 5.5 }, Color(), TextQuality::BLENDED));
    addElement<Entity>("special thanks stephan wieninger", Rect { 50, 161, 0, 0 })
    .addAnimation<Animation>().addTexture(Texture("futurab", "Stephan Wieninger",
                                          Rect { 0, 4 }, Color(), TextQuality::BLENDED));
    addElement<Entity>("htl logo", Rect { 50, 180, 0, 0 })
    .addAnimation<Animation>().addTexture(Texture("htl_logo.png", Rect { 20, 0 }));
}

void Credits::resetLocations()
{
    restore();
}

Json::Value Credits::serialize() const
{
    auto json = Scene::serialize();
    json["type"] = "CREDITS";
    return json;
}
