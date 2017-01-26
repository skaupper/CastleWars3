#ifndef CREDITS_H
#define CREDITS_H

#include "Game.h"
#include "Scene.h"
#include "FormsFunctions.h"

class Credits : public Scene
{
    public:
        Scene loadCredits(Game *g);
        int onEvent(SDL_Event *event);
        int onLoop();

    private:
        void resetLocations();
};
#endif // CREDITS_H
