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

    if (elements.size() == 0) {
        createElements();
    }

    if (move) {
        getElement<Entity>("lead developers").move(0, -0.075);
        getElement<Entity>("lead developer sebastian kaupper").move(0, -0.075);
        getElement<Entity>("lead developer christoph boehmwalder").move(0, -0.075);
        getElement<Entity>("designers").move(0, -0.075);
        getElement<Entity>("designer michael berthold").move(0, -0.075);
        getElement<Entity>("designer dominik hauer").move(0, -0.075);
        getElement<Entity>("special thanks").move(0, -0.075);
        getElement<Entity>("special thanks stephan wieninger").move(0, -0.075);
        getElement<Entity>("htl logo").move(0, -0.075);
    }

    if (getElement<Entity>("lead developers").getRenderBox().y <= 5) {
        move = false;
    }
}


void Credits::createElements()
{
    addElement<Entity>("background", Rect { 0.f, 0.f, 100, 100 })
        .addAnimation<Animation>().addTexture(Texture("credits_bg.png"));

    addElement<Entity>("lead developers", Rect { 50, 105, 0, 0 })
        .addAnimation<Animation>().addTexture(Texture("futurab", "Developers", Rect { 0, 5.5 }, Color(), TextQuality::BLENDED));
    addElement<Entity>("lead developer sebastian kaupper", Rect { 50, 111, 0, 0 })
        .addAnimation<Animation>().addTexture(Texture("futurab", "Sebastian Kaupper", Rect { 0, 4 }, Color(), TextQuality::BLENDED));
    addElement<Entity>("lead developer christoph boehmwalder", Rect { 50, 116, 0, 0 })
        .addAnimation<Animation>().addTexture(Texture("futurab", "Christoph Böhmwalder", Rect { 0, 4 }, Color(), TextQuality::BLENDED));
    addElement<Entity>("designers", Rect { 50, 130, 0, 0 })
        .addAnimation<Animation>().addTexture(Texture("futurab", "Graphic Designers", Rect { 0, 5.5 }, Color(), TextQuality::BLENDED));
    addElement<Entity>("designer michael berthold", Rect { 50, 137, 0, 0 })
        .addAnimation<Animation>().addTexture(Texture("futurab", "Michael Berthold", Rect { 0, 4 }, Color(), TextQuality::BLENDED));
    addElement<Entity>("designer dominik hauer", Rect { 50, 142, 0, 0 })
        .addAnimation<Animation>().addTexture(Texture("futurab", "Dominik Hauer", Rect { 0, 4 }, Color(), TextQuality::BLENDED));
    addElement<Entity>("special thanks", Rect { 50, 155, 0, 0 })
        .addAnimation<Animation>().addTexture(Texture("futurab", "Special thanks to", Rect { 0, 5.5 }, Color(), TextQuality::BLENDED));
    addElement<Entity>("special thanks stephan wieninger", Rect { 50, 161, 0, 0 })
        .addAnimation<Animation>().addTexture(Texture("futurab", "Stephan Wieninger", Rect { 0, 4 }, Color(), TextQuality::BLENDED));

    addElement<Entity>("htl logo", Rect { 50, 180, 0, 0 })
        .addAnimation<Animation>().addTexture(Texture("htl_logo.png", Rect { 20, 0 }));
}

void Credits::resetLocations()
{
    getElement<Element>("lead developers").setRenderBox({ 50, 105, 0, 0});
    getElement<Element>("lead developer sebastian kaupper").setRenderBox({ 50, 111, 0, 0 });
    getElement<Element>("lead developer christoph boehmwalder").setRenderBox({ 50, 116, 0, 0 });
    getElement<Element>("designers").setRenderBox({ 50, 130, 0, 0 });
    getElement<Element>("designer michael berthold").setRenderBox({ 50, 137, 0, 0 });
    getElement<Element>("designer dominik hauer").setRenderBox({ 50, 142, 0, 0 });
    getElement<Element>("special thanks").setRenderBox({ 50, 155, 0, 0 });
    getElement<Element>("special thanks stephan wieninger").setRenderBox({ 50, 161, 0, 0 });
    getElement<Element>("htl logo").setRenderBox({ 50, 180, 0, 0 });
}
