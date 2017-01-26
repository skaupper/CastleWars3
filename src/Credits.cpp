#include "Credits.h"

Credits::Credits(Game *g) : Scene(2, "credits", g)
{
    resetLocations(scene);
}

int Credits::onEvent(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_ESCAPE) {
            resetLocations(scene);
            scene->game->setActiveScene("mainmenu");
        }
    }

    return 0;
}

int Credits::onLoop()
{
    static int ticks = 0;

    if (ticks % 1 == 0)
        //if(false)
    {
        ((Entity &)(getElement("lead developers"))).move(0, -1);
        ((Entity &)(getElement("lead developer sebastian kaupper"))).move(0,
                -1);
        ((Entity &)(getElement("lead developer christoph boehmwalder"))).move(0,
                -1);
        ((Entity &)(getElement("designers"))).move(0, -1);
        ((Entity &)(getElement("designer michael berthold"))).move(0, -1);
        ((Entity &)(getElement("designer dominik hauer"))).move(0, -1);
        ((Entity &)(getElement("special thanks"))).move(0, -1);
        ((Entity &)(getElement("special thanks stephan wieninger"))).move(0,
                -1);
        ((Entity &)(getElement("htl logo"))).move(0, -1);
    }

    ticks++;

    if (((Entity *)(scene->getElement("htl logo")))->getLocation()->y < -200) {
        ticks = 0;
        resetLocations(scene);
        scene->game->setActiveScene("mainmenu");
    }

    return 0;
}


void Credits::resetLocations()
{
    //scene->clear();
    scene->removeElement("background");
    scene->removeElement("lead developers");
    scene->removeElement("lead developer sebastian kaupper");
    scene->removeElement("lead developer christoph boehmwalder");
    scene->removeElement("designers");
    scene->removeElement("designer michael berthold");
    scene->removeElement("designer dominik hauer");
    scene->removeElement("special thanks");
    scene->removeElement("special thanks stephan wieninger");
    scene->removeElement("htl logo");
    scene->addElement(getImage("res/credits_bg.png", "background",
                               getRelativeLocation(0, 0), getRelativeSize(100, 100), scene)); // Background
    int offset = 100; // Debug
    scene->addElement(getText("Lead Developers", "lead developers",
                              getRelativeLocation(69.35, offset + 5), -1, scene));
    scene->addElement(getText("Sebastian Kaupper",
                              "lead developer sebastian kaupper", getRelativeLocation(53.9, offset + 7.5), 0,
                              scene));
    scene->addElement(getText("Christoph B�hmwalder",
                              "lead developer christoph boehmwalder", getRelativeLocation(48.7,
                                      offset + 13.5), 0, scene));
    scene->addElement(getText("Graphic Designers", "designers",
                              getRelativeLocation(67.5, offset + 45), -1, scene));
    scene->addElement(getText("Michael Berthold", "designer michael berthold",
                              getRelativeLocation(56.4, offset + 47.5), 0, scene));
    scene->addElement(getText("Dominik Hauer", "designer dominik hauer",
                              getRelativeLocation(58.85, offset + 53.5), 0, scene));
    scene->addElement(getText("Special thanks to", "special thanks",
                              getRelativeLocation(68.4, offset + 85), -1, scene));
    scene->addElement(getText("Stephan Wieninger",
                              "special thanks stephan wieninger", getRelativeLocation(53.3, offset + 87.5), 0,
                              scene));
    cout << 336 * Core::getInstance()->WINDOW_WIDTH / 1600 << endl;
    scene->addElement(getImage("res/htl_logo.png", "htl logo",
                               getRelativeLocation(58.85, offset + 120), new SDL_Rect{0, 0, 336 * Core::getInstance()->WINDOW_WIDTH / 1024, 229 * Core::getInstance()->WINDOW_HEIGHT / 768},
                               scene));
}
