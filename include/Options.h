#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Game.h"
#include "FormsFunctions.h"

struct Resolution {
    int width;
    int height;
};

std::vector<Resolution> possibleResolutions = {{640, 480}, {800, 600}, {1024, 768}, {1440, 1080}};

std::string keyCodeToString(SDL_Keycode kc)
{
    if ((int)kc >= 97 && (int)kc <= 122) {
        std::stringstream s;
        int keycode = (int)kc;
        s << (char)(keycode - 32);
        std::cout << s.str() << endl;
        return s.str();
    } else if (kc == SDLK_UP) {
        return "UP";
    } else if (kc == SDLK_LEFT) {
        return "LEFT";
    } else if (kc == SDLK_RIGHT) {
        return "RIGHT";
    } else if (kc == SDLK_RCTRL) {
        return "RCTRL";
    } else if (kc == SDLK_LCTRL) {
        return "LCTRL";
    }

    return "";
}

bool contains(KeyboardLayout kl, SDL_Keycode kc)
{
    if (kl.up == kc) {
        return true;
    } else if (kl.left == kc) {
        return true;
    } else if (kl.right == kc) {
        return true;
    } else if (kl.action == kc) {
        return true;
    }

    return false;
}


int load()
{
    KeyboardLayout **players = (KeyboardLayout **) &olayouts;
    std::ifstream in("config.cfg");
    std::string line;

    if (in.is_open()) {
        for (int i = 0; std::getline(in, line); i++) {
            std::istringstream s(line);
            int n;

            if (i < 8) {
                switch (i % 4) {
                    case 0:
                        s >> n;
                        players[i / 4]->up = (SDL_Keycode)n;
                        break;

                    case 1:
                        s >> n;
                        players[i / 4]->left = (SDL_Keycode)n;
                        break;

                    case 2:
                        s >> n;
                        players[i / 4]->right = (SDL_Keycode)n;
                        break;

                    case 3:
                        s >> n;
                        players[i / 4]->action = (SDL_Keycode)n;
                        break;
                }
            } else if (i == 8) {
                s >> res;
                resolution = &res;
            }
        }

        //olayouts = players;
        in.close();
    } else {
        std::ofstream out("config.cfg");

        if (out.is_open()) {
            out << SDLK_w << std::endl;
            out << SDLK_a << std::endl;
            out << SDLK_d << std::endl;
            out << SDLK_f << std::endl;
            out << SDLK_UP << std::endl;
            out << SDLK_LEFT << std::endl;
            out << SDLK_RIGHT << std::endl;
            out << SDLK_RCTRL << std::endl;
            out << 0 << endl;
            out.close();
            load();
        } else {
            return -1;
        }
    }

    return 0;
}

int save()
{
    std::ofstream out("config.cfg");

    if (out.is_open()) {
        for (int i = 0; i <= 1; i++) {
            out << (int)olayouts[i].up << std::endl;
            out << (int)olayouts[i].left << std::endl;
            out << (int)olayouts[i].right << std::endl;
            out << (int)olayouts[i].action << std::endl;
        }

        out << res << std::endl;
        out.close();
    } else {
        std::cout << "Failed to save options!" << std::endl;
    }
}

int optionsOnEvent(Scene *scene, SDL_Event *event)
{
    static int selected = 0;
    static std::vector<string> hoverableElements = {
        "options keyboard layout player 1 up",
        "options keyboard layout player 2 up",
        "options keyboard layout player 1 left",
        "options keyboard layout player 2 left",
        "options keyboard layout player 1 right",
        "options keyboard layout player 2 right",
        "options keyboard layout player 1 action",
        "options keyboard layout player 2 action",
        "options screen size left",
        "options screen size right",
        "options save",
        "options cancel"
    };
    static bool pressed = false;
    static std::string pressedButton = "";
    static bool keyboardLayoutChanged = false;
    bool selectedChanged = false;

    if (event->type == SDL_KEYDOWN) {
        SDL_Keycode kc = event->key.keysym.sym;

        if (kc == SDLK_ESCAPE) {
            scene->game->setActiveScene("mainmenu");
        } else if (pressed) {
            std::string keyString = keyCodeToString(kc);

            if (keyString != "" && !contains(olayouts[0], kc)
                    && !contains(olayouts[1], kc)) {
                std::cout << "Left1: " << olayouts[0].left << endl;

                if (pressedButton == "options keyboard layout player 1 up") {
                    olayouts[0].up = kc;
                } else if (pressedButton == "options keyboard layout player 1 left") {
                    olayouts[0].left = kc;
                } else if (pressedButton == "options keyboard layout player 1 right") {
                    olayouts[0].right = kc;
                } else if (pressedButton == "options keyboard layout player 1 action") {
                    olayouts[0].action = kc;
                } else if (pressedButton == "options keyboard layout player 2 up") {
                    olayouts[1].up = kc;
                } else if (pressedButton == "options keyboard layout player 2 left") {
                    olayouts[1].left = kc;
                } else if (pressedButton == "options keyboard layout player 2 right") {
                    olayouts[1].right = kc;
                } else if (pressedButton == "options keyboard layout player 2 action") {
                    olayouts[1].action = kc;
                }

                std::stringstream s;
                s << pressedButton << " label";
                Location *loc = scene->getElement(s.str())->getLocation();
                scene->removeElement(s.str());
                scene->addElement(getText(keyString, s.str(), loc, 0, scene));
            }

            pressed = false;
        } else if (kc == olayouts[0].left || kc == olayouts[1].left) {
            selected--;

            if (selected < 0) {
                selected = hoverableElements->size() - 1;
            }

            selectedChanged = true;
        } else if (kc == olayouts[0].right || kc == olayouts[1].right) {
            selected = ++selected % hoverableElements->size();
            selectedChanged = true;
        } else if (kc == olayouts[0]. action || kc == olayouts[1].action) {
            bool screen_size = false;

            if ((*hoverableElements)[selected] == "options screen size left") {
                if (res == 0) {
                    res = resolutions - 1;
                } else {
                    res--;
                }

                screen_size = true;
            } else if ((*hoverableElements)[selected] == "options screen size right") {
                if (res == resolutions - 1) {
                    res = 0;
                } else {
                    res++;
                }

                screen_size = true;
            } else if ((*hoverableElements)[selected] == "options save") {
                save();
                scene->game->setActiveScene("mainmenu");
            } else if ((*hoverableElements)[selected] == "options cancel") {
                scene->game->setActiveScene("mainmenu");
            }

            pressed = false;

            if (((*hoverableElements)[selected]).find("options keyboard layout player") !=
                    string::npos) {
                pressedButton = (*hoverableElements)[selected];
                pressed = true;
            }

            if (screen_size) {
                stringstream s;
                s << possibleResolutions[res].width << 'x' << possibleResolutions[res].height;
                Location *loc = scene->getElement("options screen size label")->getLocation();
                scene->removeElement("options screen size label");
                scene->addElement(getText(s.str(), "options screen size label", loc, 0, scene));
            }
        }

        if (selectedChanged) {
            int counter = 0;

            for (list<Element *>::iterator i = scene->elements->begin();
                    i != scene->elements->end(); i++, counter++) {
                if ((*hoverableElements)[selected] == ((*i)->descr)) {
                    (*i)->setAnimation(1);
                } else {
                    (*i)->setAnimation(0);
                }
            }
        }
    }
}

Scene *loadOptions(Game *g)
{
    static int res = res;
    Scene *scene = new Scene(1, "options", g);
    scene->addElement(getImage("res/options_bg.png", "options background",
                               getRelativeLocation(0, 0), getRelativeSize(100, 100), scene)); // Background
    scene->addElement(getText("Player 1",
                              "options keyboard layout player 1 heading", getRelativeLocation(30, 7), 0,
                              scene)); // Keyboard layout Player 1 Heading
    scene->addElement(getText("Player 2",
                              "options keyboard layout player 2 heading", getRelativeLocation(58.5, 7), 0,
                              scene)); // Keyboard layout Player 2 Heading
    string paths[] = {"res/button.png", "res/button_light.png"};
    scene->addElement(getImage(paths, "options keyboard layout player 1 up",
                               getRelativeLocation(30, 17), getRelativeSize(11.5, 5), scene));
    scene->addElement(getText(keyCodeToString((olayouts)[0].up),
                              "options keyboard layout player 1 up label", getRelativeLocation(30.5,
                                      17.1 + (res * 0.2)), 0, scene));
    scene->addElement(getText("UP", "options keyboard layout up",
                              getRelativeLocation(48, 17.6 + (res * 0.2)), 0, scene));
    scene->addElement(getImage(paths, "options keyboard layout player 2 up",
                               getRelativeLocation(58.5, 17), getRelativeSize(11.5, 5), scene));
    scene->addElement(getText(keyCodeToString((olayouts)[1].up),
                              "options keyboard layout player 2 up label", getRelativeLocation(59,
                                      17.1 + (res * 0.2)), 0, scene));
    scene->addElement(getImage(paths, "options keyboard layout player 1 left",
                               getRelativeLocation(30, 24), getRelativeSize(11.5, 5), scene));
    scene->addElement(getText(keyCodeToString((olayouts)[0].left),
                              "options keyboard layout player 1 left label", getRelativeLocation(30.5,
                                      24.1 + (res * 0.2)), 0, scene));
    scene->addElement(getText("LEFT", "options keyboard layout left",
                              getRelativeLocation(47, 24.6 + (res * 0.2)), 0, scene));
    scene->addElement(getImage(paths, "options keyboard layout player 2 left",
                               getRelativeLocation(58.5, 24), getRelativeSize(11.5, 5), scene));
    scene->addElement(getText(keyCodeToString((olayouts)[1].left),
                              "options keyboard layout player 2 left label", getRelativeLocation(59,
                                      24.1 + (res * 0.2)), 0, scene));
    scene->addElement(getImage(paths, "options keyboard layout player 1 right",
                               getRelativeLocation(30, 31), getRelativeSize(11.5,  5), scene));
    scene->addElement(getText(keyCodeToString(olayouts[0].right),
                              "options keyboard layout player 1 right label", getRelativeLocation(30.5,
                                      31.1 + (res * 0.2)), 0, scene));
    scene->addElement(getText("RIGHT", "options keyboard layout right",
                              getRelativeLocation(46, 31.6 + (res * 0.2)), 0, scene));
    scene->addElement(getImage(paths, "options keyboard layout player 2 right",
                               getRelativeLocation(58.5, 31), getRelativeSize(11.5, 5), scene));
    scene->addElement(getText(keyCodeToString((olayouts)[1].right),
                              "options keyboard layout player 2 right label", getRelativeLocation(59,
                                      31.1 + (res * 0.2)), 0, scene));
    scene->addElement(getImage(paths, "options keyboard layout player 1 action",
                               getRelativeLocation(30, 38), getRelativeSize(11.5, 5), scene));
    scene->addElement(getText(keyCodeToString((olayouts)[0].action),
                              "options keyboard layout player 1 action label", getRelativeLocation(30.5,
                                      38.1 + (res * 0.2)), 0, scene));
    scene->addElement(getText("ACTION", "options keyboard layout action",
                              getRelativeLocation(45, 38.6 + (res * 0.2)), 0, scene));
    scene->addElement(getImage(paths, "options keyboard layout player 2 action",
                               getRelativeLocation(58.5, 38), getRelativeSize(11.5, 5), scene));
    scene->addElement(getText(keyCodeToString((olayouts)[1].action),
                              "options keyboard layout player 2 action label", getRelativeLocation(59,
                                      38.1 + (res * 0.2)), 0, scene));
    scene->addElement(getImage(paths, "options screen size left",
                               getRelativeLocation(30, 55), getRelativeSize(5, 7),
                               scene)); // Options Screen Size left
    scene->addElement(getText("<", "options screen size left label",
                              getRelativeLocation(31.3, 55.9 + (res * 0.2)), 0,
                              scene)); // Options Screen Size left label
    scene->addElement(getImage(paths, "options screen size", getRelativeLocation(37,
                               54.8 + (res * 0.2)), getRelativeSize(26, 7), scene)); // Options Screen Size
    scene->addElement(getImage(paths, "options screen size right",
                               getRelativeLocation(65, 55), getRelativeSize(5, 7),
                               scene)); // Options Screen Size right
    scene->addElement(getText(">", "options screen size right label",
                              getRelativeLocation(66.3, 55.9 + (res * 0.2)), 0,
                              scene)); // Options Screen Size right label
    scene->addElement(getImage(paths, "options save", getRelativeLocation(30, 83),
                               getRelativeSize(15, 10), scene)); // Options Save
    scene->addElement(getText("Save", "options save label",
                              getRelativeLocation(33.75, 85.3 + (res * 0.2)), 0, scene));
    scene->addElement(getImage(paths, "options cancel", getRelativeLocation(55, 83),
                               getRelativeSize(15, 10), scene)); // Options Cancel
    scene->addElement(getText("Cancel", "options save label",
                              getRelativeLocation(57.75, 85.3 + (res * 0.2)), 0, scene));
    stringstream s;
    s << possibleResolutions[*resolution].width << 'x' <<
      possibleResolutions[*resolution].height;
    scene->addElement(getText(s.str(), "options screen size label",
                              getRelativeLocation(40, 56.1 + (res * 0.2)), 0, scene));
    scene->getElement("options keyboard layout player 1 up")->setAnimation(1);
    scene->event = &optionsOnEvent;
    return scene;
}

#endif // OPTIONS_H
