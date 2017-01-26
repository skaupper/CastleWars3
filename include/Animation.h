///@Author B�hmi

#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>

#include "Texture.h"

using namespace std;

class Animation
{
    public:
        int i;
        Animation(std::string descr, int frameDelta);
        virtual ~Animation();
        void reset();
        void addTexture(Texture &texture);
        Texture &getTexture();
        void incFrameCount();
        void setDelta(int frameDelta);
        void addImage(std::string path, SDL_Rect rect);
        void addText(std::string text, SDL_Color *color, short size);
        void clear();

    private:
        std::vector<Texture> textures;
        int frameDelta;
        int frameCount;
        std::string descr;
};

#endif // ANIMATION_H
