#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Weapon.h"

class Player : public Entity
{
    public:
        Player(Location *loc, std::string descr, Scene *scene, Location *respawn);
        int hit(int hitpoints);
        void giveWeapon(int index);
        Weapon *weapon;
        bool holdingWeapon;
        int render();
        virtual ~Player();
        bool jumping;
        bool inAir;
        int direction;
        int fireCooldown;
        Timer jumpTimer;
        int jumpStartedTicks;
        Location jumpStartedLocation;
        float dx;
        float gravity;
        float jumpPower;
        unsigned short deaths;

    private:
        int id;
        int maxlifes;
        int lifes;
        Location respawn;
};

#endif // PLAYER_H
