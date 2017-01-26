#include "Weapon.h"
#include "Scene.h"
#include <iostream>
#include "Player.h"
#include <sstream>

extern SDL_Rect *gamemap;

bool inRectBullet(SDL_Rect *large, SDL_Rect *small)
{
    return small->x > large->x && small->x + small->w < large->x + large->w
           && small->y > large->y && small->y + small->h < large->y + large->h;
}

int getPercentageWidthBullet(double percent)
{
    int window_width = Core::getInstance()->WINDOW_WIDTH;
    return window_width * (percent / 100);
}

int getPercentageHeightBullet(double percent)
{
    int window_height = Core::getInstance()->WINDOW_HEIGHT;
    return window_height * (percent / 100);
}

Location *getRelativeLocationBullet(double percent_x, double percent_y)
{
    return new Location{getPercentageWidthBullet(percent_x), getPercentageHeightBullet(percent_y)};
}

SDL_Rect *getRelativeSizeBullet(double percent_x, double percent_y)
{
    return new SDL_Rect{0, 0, getPercentageWidthBullet(percent_x), getPercentageHeightBullet(percent_y)};
}

bool contains(string s1, string s2)
{
    bool contain = false;

    for (int i = 0; i < s1.size() - s2.size() + 1; i++) {
        if (s1[i] == s2[0]) {
            contain = true;

            for (int j = 1; j < s2.size(); j++) {
                if (s1[i + j] != s2[j]) {
                    contain = false;
                }
            }

            if (contain) {
                return true;
            }
        }
    }

    return false;
}

int projectileOnLoop(Element *ele)
{
    Entity *me = (Entity *)(((Weapon *)ele)->projectileTemplate);
    bool collides = false;
    int index;

    if (contains(ele->descr, "player1")) {
        index = 1;
    } else {
        index = 2;
    }

    stringstream ss;
    ss << "player" << index % 2 + 1;
    string enemy = ss.str();
    ss.str("");
    ss << "player" << index;
    Player *player = (Player *)me->parentScene->getElement(ss.str());
    me->move((getRelativeSizeBullet(2, 0)->w) * (me->flipped ? -1 : 1), 0);

    for (int i = 0; i < me->parentScene->countElements(); i++) {
        Element *tmp = me->parentScene->getElement(i);

        if (!inRectBullet(gamemap, new SDL_Rect{me->location->x, me->location->y, me->collisionRect->w, me->collisionRect->h})
                || (tmp->descr != "player 1 death count"
                    && tmp->descr != "player 2 death count" && tmp->descr != "box"
                    && me->collidesWith(tmp) && tmp->descr != "background"
                    && tmp->descr != ss.str())) {
            collides = true;
            cout << tmp->descr << endl;
            cout << player->descr << endl;

            if (me->collidesWith(me->parentScene->getElement(enemy))) {
                ((Player *) me->parentScene->getElement(enemy))->hit(((Weapon *)
                        ele)->hitpoints);
            }

            ((Weapon *)ele)->shooting = false;
            ((Weapon *)ele)->projectileTemplate->clear();
            delete((Weapon *)ele)->projectileTemplate;
            ((Weapon *)ele)->projectileTemplate = NULL;
            break;
        }
    }

    return 0;
}

Weapon::Weapon(Location *loc, string descr, int hitpoints, WeaponType type,
               Scene *parentScene): Entity(loc, parentScene, descr, false)
{
    Weapon::location = loc;
    Weapon::hitpoints = hitpoints;
    Weapon::type = type;

    if (type == WEAPON_RANGE) {
        setupProjectilesList();
    }

    Weapon::shooting = false;
}

void Weapon::setupProjectilesList()
{
    //projectiles = new vector<Entity>();
}

void Weapon::setProjectileTemplate(string imagepath, SDL_Rect *imageSize)
{
    projectileTemplate = new Entity(location, parentScene, "projectile", true);
    Animation *projectileAnimation = new Animation("projectile", -1);
    projectileAnimation->addImage(imagepath, imageSize);
    projectileTemplate->addAnimation(projectileAnimation);
    projectileTemplate->descr = descr;
    projectileTemplate->loop = projectileOnLoop;

    if (flipped)
        projectileTemplate->location = new Location{location->x, location->y + getRelativeSizeBullet(0, 5.5)->h};
    else
        projectileTemplate->location = new Location{location->x, location->y + getRelativeSizeBullet(0, 5.5)->h};

    projectileTemplate->flipped = flipped;
}

void Weapon::setProjectileTemplate(Animation *animation)
{
    projectileTemplate = new Entity(location, parentScene, "projectile", true);
    projectileTemplate->addAnimation(animation);
    projectileTemplate->loop = projectileOnLoop;
}

void Weapon::fire()
{
    cout << "Firing" << endl;

    if (type == WEAPON_RANGE) {
        if (!shooting) {
            setProjectileTemplate("res/animations/punch/1/1.png", getRelativeSizeBullet(3,
                                  1.5));
            projectileTemplate->flipped = flipped;
            shooting = true;
        }
    } else if (type == WEAPON_MELEE) {
        setAnimation(1);
    }
}

int Weapon::render()
{
    frame++;
    (currentAnimation->getTexture())->render(location, flipped);
    return 0;
}

int Weapon::renderBullet()
{
    if (projectileTemplate != NULL) {
        projectileTemplate->render();
    }
}
