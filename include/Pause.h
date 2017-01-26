#ifndef PAUSE_H
#define PAUSE_H

#include <cmath>
#include "Element.h"
#include "FormsFunctions.h"
#include <vector>

extern KeyboardLayout layouts[2];
extern bool paused;

vector<Element *> *pausedElements;

void unloadPauseScreen(Scene *scene)
{
    for (int i = 0; i < pausedElements->size(); i++) {
        scene->removeElement((*pausedElements)[i]->descr);
    }

    delete pausedElements;
}

int pauseOnEvent(Scene *scene, SDL_Event *event)
{
    static int selectedIndex = 0;
    static bool selectedChanged = false;
    static int count = 2;
    static string hoverableElements[2] = {"continue", "exit"};

    if (event->type == SDL_KEYDOWN) {
        SDL_Keycode kc = event->key.keysym.sym;

        if (kc == layouts[0].left || kc == layouts[1].left) {
            selectedIndex = abs((selectedIndex - 1) % 2);
            selectedChanged = true;
        } else if (kc == layouts[0].right || kc == layouts[1].right) {
            selectedIndex = abs((selectedIndex - 1) % 2);
            selectedChanged = true;
        } else if (kc == layouts[0].action || kc == layouts[1].action) {
            switch (selectedIndex) {
                case 0:
                    paused = false;
                    unloadPauseScreen(scene);
                    break;

                case 1:
                    paused = false;
                    scene->game->setActiveScene("mainmenu");
                    Mix_FadeOutMusic(500);
                    Mix_Music *mus = Mix_LoadMUS("res/music/mainmenu.aiff");
                    cout << Mix_GetError() << endl;

                    if (mus == NULL) {
                        cout << "Mixer Error: " << Mix_GetError() << endl;
                    } else {
                        Mix_FadeInMusic(mus, 0, 1000);
                    }

                    unloadPauseScreen(scene);
                    selectedIndex = 0;
                    break;
            }
        }

        if (selectedChanged) {
            int counter = 0;

            for (list<Element *>::iterator i = scene->elements->begin();
                    i != scene->elements->end(); i++, counter++) {
                if (hoverableElements[selectedIndex] == (*i)->descr) {
                    (*i)->setAnimation(1);
                } else {
                    (*i)->setAnimation(0);
                }
            }
        }
    }
}

void loadPauseScreen(Scene *scene)
{
    vector<Element *> *eles = new vector<Element *>();
    pausedElements = eles;
    Element *ele = new Element(new Location{0, 0}, "bg");
    Animation *a = new Animation("bg", -1);
    a->addImage("res/pause_bg.png", getRelativeSize(100, 100));
    ele->addAnimation(a);
    eles->push_back(ele);
    ele = new Element(getRelativeLocation(40, 5), "label"); // label
    Animation *label = new Animation("label", -1);
    label->addText("PAUSE", new SDL_Color{255, 255, 255}, 1);
    ele->addAnimation(label);
    eles->push_back(ele);
    ele = new Element(getRelativeLocation(30, 40), "continue");
    Animation *con = new Animation("continue", -1);
    con->addImage("res/button.png", getRelativeSize(40, 10));
    ele->addAnimation(con);
    con = new Animation("continue_hover", -1);
    con->addImage("res/button_light.png", getRelativeSize(40, 10));
    ele->addAnimation(con);
    ele->setAnimation(1);
    eles->push_back(ele);
    ele = new Element(getRelativeLocation(31.5, 40.5), "continue_text");
    Animation *cont = new Animation("continue_text", -1);
    cont->addText("CONTINUE", new SDL_Color{255, 255, 255}, 0);
    ele->addAnimation(cont);
    eles->push_back(ele);
    ele = new Element(getRelativeLocation(30, 80), "exit");
    Animation *ex = new Animation("exit", -1);
    ex->addImage("res/button.png", getRelativeSize(40, 10));
    ele->addAnimation(ex);
    ex = new Animation("exit_hover", -1);
    ex->addImage("res/button_light.png", getRelativeSize(40, 10));
    ele->addAnimation(ex);
    eles->push_back(ele);
    ele = new Element(getRelativeLocation(31.5, 80.5), "exit_text");
    Animation *ext = new Animation("exit_text", -1);
    ext->addText("EXIT", new SDL_Color{255, 255, 255}, 0);
    ele->addAnimation(ext);
    eles->push_back(ele);

    for (int i = 0; i < eles->size(); i++) {
        scene->addElement((*eles)[i]);
    }
}


#endif // PAUSE_H
