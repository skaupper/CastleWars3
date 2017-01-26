#ifndef WEAPON_H
#define WEAPON_H

#include "Location.h"
#include "Entity.h"
#include <vector>
#include "Scene.h"


class Entity;

enum WeaponType {
    WEAPON_RANGE = 0,
    WEAPON_MELEE = 1,
    WEAPON_SPECIAL = 2
};

class Weapon: public Entity
{
    public:
        Weapon(Location loc, std::string descr, int hitpoints, WeaponType type,
               Scene &parentScene);
        int hitpoints;
        void fire();
        int render();
        int renderBullet();
        WeaponType type;
        bool shooting;
        Entity projectileTemplate;
        void setProjectileTemplate(std::string imagepath1,  SDL_Rect *imageSize);
        void setProjectileTemplate(Animation &animation1);
        std::vector<Entity> projectiles;
    private:
        void setupProjectilesList();
};


#endif
