#ifndef STARTGAME_H
#define STARTGAME_H

#include "Game.h"
#include <iostream>
#include "FormsFunctions.h"
#include "Pause.h"
#include "Objects.h"
#include "Map.h"
#include "Player.h"

#include <time.h>
#include <stdlib.h>


Scene *glscene;


SDL_Rect *gamemap;

bool player1Cheat = false;
bool player2Cheat = false;

int player1LastDeaths = 0;
int player2LastDeaths = 0;

Entity *player1DeathCount = NULL;
Entity *player2DeathCount = NULL;

int generalBoxCooldown = 600;
int boxCooldown = 0;

Player *player1;
Player *player2;
int fireCooldown = 20;

template <typename T> int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

int gameOnEvent(Scene *scene, SDL_Event *event)
{
    if (paused) {
        return pauseOnEvent(scene, event);
    }

    if (event->type == SDL_KEYUP) {
        SDL_Keycode kc = event->key.keysym.sym;

        if (kc == layouts[0].left && player1->direction == -1) {
            player1->direction = 0;
            player1->setAnimation(0);
        }

        if (kc == layouts[0].right && player1->direction == 1) {
            player1->direction = 0;
            player1->setAnimation(0);
        }

        if (kc == layouts[1].left && player2->direction == -1) {
            player2->direction = 0;
            player2->setAnimation(0);
        }

        if (kc == layouts[1].right && player2->direction == 1) {
            player2->direction = 0;
            player2->setAnimation(0);
        }
    }

    if (event->type == SDL_KEYDOWN) {
        SDL_Keycode kc = event->key.keysym.sym;

        if (kc == SDLK_F1) {
            if (player1->dx < 20) {
                player1->dx++;
            }
        }

        if (kc == SDLK_F2) {
            if (player1->dx > 5) {
                player1->dx--;
            }
        }

        if (kc == SDLK_F3) {
            if (player2->dx < 20) {
                player2->dx++;
            }
        }

        if (kc == SDLK_F4) {
            if (player2->dx > 5) {
                player2->dx--;
            }
        }

        if (kc == SDLK_F5) {
            if (player1->jumpPower < 25) {
                player1->jumpPower++;
            }
        }

        if (kc == SDLK_F6) {
            if (player1->jumpPower > 10) {
                player1->jumpPower--;
            }
        }

        if (kc == SDLK_F7) {
            if (player2->jumpPower < 25) {
                player2->jumpPower++;
            }
        }

        if (kc == SDLK_F8) {
            if (player2->jumpPower > 10) {
                player2->jumpPower--;
            }
        }

        if (kc == SDLK_F9 && !player1Cheat) {
            player1Cheat = true;
            cout << "PLAYER 1 IS A DIRTY CHEATER" << endl;
        }

        if (kc == SDLK_F10 && !player2Cheat) {
            player2Cheat = true;
            cout << "PLAYER 2 IS A DIRTY CHEATER" << endl;
        }

        if (kc == layouts[0].left) {
            player1->direction = -1;
            player1->setAnimation(1);
            player1->flipped = true;
        }

        if (kc == layouts[0].action && player1->fireCooldown == 0) {
            if (player1->holdingWeapon) {
                player1->weapon->fire();
                player1->fireCooldown = fireCooldown;

                if (player1->weapon->type == WEAPON_MELEE ? player1->weapon->collidesWith(
                            scene->getElement("player2")) :
                        false) { //(player1->weapon->projectileTemplate == NULL?false: player1->weapon->projectileTemplate->collidesWith(scene->getElement("player2"))))
                    if (player1Cheat) {
                        player2->hit(1000);
                    } else {
                        player2->hit(1);
                    }
                }
            }
        }

        if (kc == layouts[0].right) {
            player1->direction = 1;
            player1->setAnimation(1);
            player1->flipped = false;
        }

        if (kc == layouts[0].up && !player1->inAir) {
            player1->jumping = true;
            player1->frame = 0;
            player1->jumpStartedTicks = player1->jumpTimer.getTicks();
            delete player1->jumpStartedLocation;
            player1->jumpStartedLocation = new Location{player1->location->x, player1->location->y};
        }

        if (kc == layouts[1].left) {
            player2->direction = -1;
            player2->setAnimation(1);
            player2->flipped = true;
        }

        if (kc == layouts[1].right) {
            player2->direction = 1;
            player2->setAnimation(1);
            player2->flipped = false;
        }

        if (kc == layouts[1].up && !player2->inAir) {
            player2->jumping = true;
            player2->frame = 0;
            player2->jumpStartedTicks = player2->jumpTimer.getTicks();
            delete player2->jumpStartedLocation;
            player2->jumpStartedLocation = new Location{player2->location->x, player2->location->y};
        }

        if (kc == layouts[1].action && player2->fireCooldown == 0) {
            if (player2->holdingWeapon) {
                player2->weapon->fire();
                player2->fireCooldown = fireCooldown;

                if (player2->weapon->type == WEAPON_MELEE ? player2->weapon->collidesWith(
                            scene->getElement("player1")) :
                        false) { //(player2->weapon->projectileTemplate == NULL? false: player2->weapon->projectileTemplate->collidesWith(scene->getElement("player1"))))
                    if (player2Cheat) {
                        player1->hit(player2->weapon->hitpoints * 10);
                    } else {
                        player1->hit(player2->weapon->hitpoints);
                    }
                }
            }
        }

        if (kc == SDLK_ESCAPE) {
            loadPauseScreen(scene);
            paused = true;
        }
    }

    return 0;
}
void applyGravity(Entity *player, Scene *scene)
{
    float dy = ((Player *)player)->gravity;
    bool &playerAir = ((Player *)player)->inAir;
    bool &playerJumping = ((Player *)player)->jumping;
    bool gamemapCollision = false;
    float s = dy * pow((player->frame == 0 ? 0 : (player->frame - 1)),
                       2) - dy * pow(player->frame, 2);
    player->move(0, -s);

    for (int i = 1; i < scene->countElements(); i++) {
        gamemapCollision = (player->location->y <= gamemap->y
                            || player->location->y + player->collisionRect->h >= gamemap->y + gamemap->h);

        if (gamemapCollision || player->collidesWith(scene->getElement(i), func)
                && scene->getElement(i)->isCollidable) {
            if (player->descr == scene->getElement(i)->descr) {
                continue;
            }

            playerAir = false;
            playerJumping = false;
            player->frame = 0;

            if (!gamemapCollision) {
                player->moveTo(player->location->x,
                               scene->getElement(i)->location->y - player->collisionRect->h - 0.1);
            } else {
                player->moveTo(player->location->x,
                               gamemap->y + gamemap->h - player->collisionRect->h);
            }

            break;
        }
    }
}

void handleJump(Player *player, Scene *scene)
{
    bool &playerAir = player->inAir;
    bool &playerJumping = player->jumping;
    Element *otherElement;
    static bool gamemapCollision = false;

    if (playerJumping) {
        player->move(0, -player->jumpPower);
        playerAir = true;

        for (int i = 1; i < scene->countElements(); i++) {
            gamemapCollision = (player->location->y <= gamemap->y
                                || player->location->y + player->collisionRect->h >= gamemap->y + gamemap->h);

            if (gamemapCollision || player->collidesWith(scene->getElement(i), func)
                    && scene->getElement(i)->isCollidable) {
                player->frame = 0;
                playerJumping = false;

                if (player->descr == scene->getElement(i)->descr) {
                    continue;
                }

                if (!gamemapCollision) {
                    player->moveTo(player->location->x,
                                   scene->getElement(i)->location->y + scene->getElement(i)->collisionRect->h +
                                   0.1);
                } else {
                    player->moveTo(player->location->x, gamemap->y + 0.1);
                }

                break;
            }
        }
    }
}

void movePlayer(Player *player, Scene *scene)
{
    float &dx = player->dx;
    int &playerDirection = player->direction;
    Element *otherElement = NULL;
    player->move(dx * playerDirection, 0);

    for (int i = 1; i < scene->countElements(); i++) {
        otherElement = scene->getElement(i);

        if (player->descr == otherElement->descr) {
            continue;
        }

        if (!(player->location->x + player->collisionRect->w + dx * playerDirection <
                gamemap->x + gamemap->w
                && player->location->x + dx * playerDirection > gamemap->x)
                || player->collidesWith(otherElement, func) && otherElement->isCollidable) {
            player->move(-dx * playerDirection, 0);
            break;
        }
    }
}

void collectLoot(Entity *player)
{
    glscene->removeElement("box");
    ((Player *)player)->giveWeapon(rand() % 2);
    boxCooldown = generalBoxCooldown;
}
int gameOnLoop(Scene *scene)
{
    if (paused) {
        return 0;
    }

    stringstream ss;

    if (player1->deaths != player1LastDeaths) {
        scene->removeElement(player1DeathCount->descr);
        ss.str("");
        player1DeathCount->clear();
        delete player1DeathCount;
        player1DeathCount = NULL;
        ss << player1->deaths;
        player1DeathCount = getText(ss.str(), "player 1 death count",
                                    getRelativeLocation(20, 20), 1, scene);
        scene->addElement(player1DeathCount);
    }

    if (player2->deaths != player2LastDeaths) {
        scene->removeElement(player2DeathCount->descr);
        ss.str("");
        player2DeathCount->clear();
        delete player2DeathCount;
        player2DeathCount = NULL;
        ss << player2->deaths;
        player2DeathCount = getText(ss.str(), "player 2 death count",
                                    getRelativeLocation(80, 20), 1, scene);
        scene->addElement(player2DeathCount);
    }

    player1LastDeaths = player1->deaths;
    player2LastDeaths = player2->deaths;

    if (player1->fireCooldown != 0) {
        if (player1->fireCooldown > 0) {
            player1->fireCooldown--;
        }

        if (player1->fireCooldown < fireCooldown / 2) {
            player1->weapon->setAnimation(0);
        }
    }

    if (player1->holdingWeapon && player1->weapon->projectileTemplate != NULL) {
        player1->weapon->projectileTemplate->loop(player1->weapon);
    }

    if (player2->fireCooldown != 0) {
        if (player2->fireCooldown > 0) {
            player2->fireCooldown--;
        }

        if (player2->fireCooldown < fireCooldown / 2) {
            player2->weapon->setAnimation(0);
        }
    }

    if (player2->holdingWeapon && player2->weapon->projectileTemplate != NULL) {
        player2->weapon->projectileTemplate->loop(player2->weapon);
    }

    if (boxCooldown > 0) {
        boxCooldown--;
    } else {
        if ((boxCooldown) == 0) {
            getNewObject(scene);
            boxCooldown--;
        } else {
            objectOnLoop(scene);
        }
    }

    // Moving
    movePlayer(player1, scene);
    movePlayer(player2, scene);
    // Jumping
    handleJump(player1, scene);
    handleJump(player2, scene);
    // Gravity
    applyGravity(player1, scene);
    applyGravity(player2, scene);
    return 0;
}

Scene *loadGame(Game *g)
{
    srand(time(NULL));
    Scene *scene = new Scene(3, "game", g);
    func = &collectLoot;
    gamemap = getRelativeSize(90, 90);
    gamemap->x = getRelativeLocation(5, 5)->x;
    gamemap->y = getRelativeLocation(5, 5)->y;
    player1 = new Player(getRelativeLocation(30, 60), "player1", scene,
                         getRelativeLocation(10, 60));
    player2 = new Player(getRelativeLocation(80, 73), "player2", scene,
                         getRelativeLocation(80, 60));
    int size = 8;
    float heightFactor = 1.75;
    scene->addElement(getImage("res/game/bg.png", "background",
                               getRelativeLocation(0, 0), getRelativeSize(100, 100), scene));
    player1DeathCount = getText("0", "player 1 death count", getRelativeLocation(20,
                                20), 1, scene);
    player2DeathCount = getText("0", "player 2 death count", getRelativeLocation(80,
                                20), 1, scene);
    player1DeathCount->isCollidable = false;
    player2DeathCount->isCollidable = false;
    scene->addElement(player1DeathCount);
    scene->addElement(player2DeathCount);
    cout << scene->getElement("background")->descr << endl;
    Animation *player1Walking = new Animation("player 1 walking", 2);
    stringstream filename;
    filename.str("");

    for (int i = 0; i <= 7; i++) {
        filename.str("");
        filename << "res/animations/walk/player1/" << i << ".png";
        player1Walking->addImage(filename.str(), getRelativeSize(size,
                                 size * heightFactor));
    }

    Animation *player1Standing = new Animation("player 1 standing", -1);
    player1Standing->addImage("res/animations/walk/player1/0.png",
                              getRelativeSize(size, size * heightFactor));
    player1->addAnimation(player1Standing);
    player1->addAnimation(player1Walking);
    player1->setAnimation(0);
    Animation *player2Walking = new Animation("player 2 walking", 2);
    filename.str("");

    for (int i = 0; i <= 7; i++) {
        filename.str("");
        filename << "res/animations/walk/player2/" << i << ".png";
        player2Walking->addImage(filename.str(), getRelativeSize(size,
                                 size * heightFactor));
    }

    Animation *player2Standing = new Animation("player 2 standing", -1);
    player2Standing->addImage("res/animations/walk/player2/0.png",
                              getRelativeSize(size, size * heightFactor));
    player2->addAnimation(player2Standing);
    player2->addAnimation(player2Walking);
    player2->setAnimation(0);
    scene->addElement(player1);
    scene->addElement(player2);
    scene->loop = gameOnLoop;
    scene->event = gameOnEvent;
    loadMap(scene);
    player2->flipped = true;
    player1->jumpTimer.start();
    player2->jumpTimer.start();
    glscene = scene;
    return scene;
}

#endif // STARTGAME_H
