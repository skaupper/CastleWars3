///@Author B�hmi

#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>

#include "Texture.h"

class Animation
{
    public:
        Animation(const std::string &descr, int frameDelta = 1);
        virtual ~Animation();

        void addImage(const std::string &path);
        void addImage(const std::string &path, SDL_Rect rect);
        void addText(const std::string &text, SDL_Color color, short size);
        void addTexture(const Texture &texture);

        bool hasTexture(int index);

        Texture &getNextTexture();
        Texture &getCurrentTexture();

        void incFrameCount();
        void setFramesPerTexture(int frames);

        void reset();

        std::string getDescription();

    private:
        int frameCounter;
        int framesPerTexture;
        int currentIndex;
        std::vector<Texture> textures;
        std::string description;
};

#endif // ANIMATION_H
