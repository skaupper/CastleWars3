#include "Player.h"
#include <iostream>
#include <sstream>


Player::Player(Location *loc, string descr, Scene *scene,
               Location *respawn) : Entity(loc, scene, descr)
{
    float size = Core::getInstance()->WINDOW_WIDTH * (8.0 / 100.0);
    float heightFactor = 1.75;
    Rect *rect = new Rect{0, 0, size, size * heightFactor};
    cout << rect->w << "x" << rect->h << endl;
    Player::respawn.x = respawn->x;
    Player::respawn.y = respawn->y;
    Player::weapon = NULL;
    Player::holdingWeapon = false;
    Player::lifes = 0;
    Player::maxlifes = 3;
    Player::hit(maxlifes);
    Player::fireCooldown = 0;
    Player::direction = 0;
    Player::inAir = false;
    Player::jumping = false;
    Player::jumpStartedTicks = 0;
    Player::deaths = 0;
    Player::dx = 8;
    Player::gravity = 0.3;
    Player::jumpPower = 15;
}

// Zieht dem Player "hitpoints" Leben ab
int Player::hit(int hitpoints)
{
    Player::lifes -= hitpoints;

    if (lifes <= 0) {
        deaths++;
        Player::moveTo(Player::respawn.x, Player::respawn.y);
        lifes = maxlifes;
        holdingWeapon = false;
        jumping = false;
        inAir = false;
        direction = 0;
        jumpStartedTicks = 0;
        setAnimation(0);
    }
}

void Player::giveWeapon(int index)
{
    stringstream ss;
    WeaponType type = index == 0 ? WEAPON_MELEE : WEAPON_RANGE;
    int damageValues[] = {1, 10};

    if (weapon != NULL) {
        weapon->clear();
    }

    ss << "weapon_" << descr << endl;
    weapon = new Weapon(Player::location, ss.str(), damageValues[index], type,
                        parentScene);
    Animation *weaponAnimation1 = new Animation("weapon1", -1);
    ss.str("");
    ss << "res/animations/punch/" << index << "/0.png";
    weaponAnimation1->addImage(ss.str(), collisionRect);
    weapon->addAnimation(weaponAnimation1);
    ss.str("");
    ss << "res/animations/punch/" << index << "/1.png";
    Animation *weaponAnimation2 = new Animation("weapon2", -1);
    weaponAnimation2->addImage(ss.str(), collisionRect);
    weapon->addAnimation(weaponAnimation2);
    holdingWeapon = true;
}

int Player::render()
{
    frame++;

    if (holdingWeapon) {
        weapon->renderBullet();
    }

    (currentAnimation->getTexture())->render(location, flipped);

    if (holdingWeapon) {
        weapon->location = location;
        weapon->flipped = flipped;
        weapon->render();
    }

    return 0;
}

Player::~Player()
{
    //dtor
}
