#ifndef MAINMENU_H
#define MAINMENU_H

#include "Scene.h"
#include "FormsFunctions.h"

#include <iostream>

int mainMenuOnLoop(Scene *s)
{
    return 0;
}

// Mix_Music *mainMenuMus = NULL;

int mainMenuOnEvent(Scene *s, SDL_Event *e)
{
    bool selectedChanged = false;
    static int selected = 0;
    static Element *selectedElement = s->getElement("selected");

    if (e->type == SDL_KEYDOWN) {
        SDL_Keycode kc = e->key.keysym.sym;

        if (kc == mlayouts[0]->right || kc == mlayouts[1]->right) {
            selectedChanged = true;

            if (selected < 3) {
                selected++;
            } else {
                selected = 0;
            }
        } else if (kc == mlayouts[0]->left || kc == mlayouts[1]->left) {
            selectedChanged = true;

            if (selected > 0) {
                selected--;
            } else {
                selected = 3;
            }
        } else if (kc == mlayouts[0]->action || kc == mlayouts[1]->action) {
            switch (selected) {
                case 0: { // Start Game
                    // Biggest TODO ever
                    s->game->setActiveScene("game");
                    Mix_FadeOutMusic(500);
                    Mix_FreeMusic(mainMenuMus);
                    Mix_Music *mus = Mix_LoadMUS("res/music/game.aiff");

                    if (mus == NULL) {
                        cout << "Mixer Error: " << Mix_GetError() << endl;
                    } else {
                        Mix_FadeInMusic(mus, -1, 1000);
                    }

                    break;
                }

                case 1: // Credits
                    s->game->setActiveScene("credits");
                    break;

                case 2: // Exit
                    s->game->running = false;
                    break;

                case 3: // Options
                    s->game->setActiveScene("options");//"options");
                    break;
            }
        }
    }

    if (selectedChanged) {
        selectedElement->setAnimation(selected);
    }

    return 0;
}

Scene *loadMainMenu(Game *g)
{
    Scene *scene = new Scene(0, "mainmenu", g);
    mainMenuMus = Mix_LoadMUS("res/music/mainmenu.aiff");
    cout << Mix_GetError() << endl;

    if (mainMenuMus == NULL) {
        cout << "Mixer Error: " << Mix_GetError() << endl;
    } else {
        Mix_FadeInMusic(mainMenuMus, -1, 1000);
    }

    scene->addElement(getImage("res/mainmenu/bg.png", "background",
                               getRelativeLocation(0, 0), getRelativeSize(100, 100), scene));
    Element *selectedElement = new Element(getRelativeLocation(0, 0), "selected");
    Animation *selected_startgame = new Animation("selected start game", -1);
    Animation *selected_options = new Animation("selected options", -1);
    Animation *selected_credits = new Animation("selected credits", -1);
    Animation *selected_exit = new Animation("selected exit", -1);
    selected_startgame->addImage("res/mainmenu/selected_startgame.png",
                                 getRelativeSize(100, 100));
    selected_exit->addImage("res/mainmenu/selected_exit.png", getRelativeSize(100,
                            100));
    selected_options->addImage("res/mainmenu/selected_options.png",
                               getRelativeSize(100, 100));
    selected_credits->addImage("res/mainmenu/selected_credits.png",
                               getRelativeSize(100, 100));
    selectedElement->addAnimation(selected_startgame);
    selectedElement->addAnimation(selected_options);
    selectedElement->addAnimation(selected_exit);
    selectedElement->addAnimation(selected_credits);
    selectedElement->setAnimation(0);
    scene->addElement(selectedElement);
    scene->loop = &mainMenuOnLoop;
    scene->event = &mainMenuOnEvent;
    return scene;
}

#endif // MAINMENU_H
