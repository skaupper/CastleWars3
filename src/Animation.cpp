/// @Author B�hmi

#include <iostream>

#include "Animation.h"


//descr:        Animation Description Identifier (ADI)
//frameDelta:   Frames, bis auf den n�chsten Frame gesprungen wird
Animation::Animation(std::string descr, int frameDelta)
{
    frameCount = 0;
    Animation::descr = descr;
    Animation::frameDelta = frameDelta;
    i = 0;
}

// Setzt frameCount auf 0
void Animation::reset()
{
    frameCount = 0;
}

// Gibt die aktuelle Textur zur�ck
Texture &Animation::getTexture()
{
    auto &tmp = textures[frameCount];
    incFrameCount();
    return tmp;
}

void Animation::addTexture(Texture &texture)
{
    textures.push_back(texture);
}

// Setzt frameCount auf frameCount + 1
// Wenn frameCount die Anzahl der Texturen �bersteigt, wird es auf 0 gesetzt
void Animation::incFrameCount()
{
    if (frameDelta == -1) {
        return;
    }

    if (i < frameDelta - 1) {
        i++;
    } else {
        i = 0;

        if (frameCount + 1 >= textures.size()) {
            frameCount = 0;
        } else {
            frameCount++;
        }
    }
}

void Animation::addImage(std::string path, SDL_Rect size)
{
    Texture t;

    if (0 != t.loadImage(path, {0}, size)) {
        std::cout << "Failed to load Texture!" << std::endl;
    }
    Animation::addTexture(t);
}

void Animation::addText(std::string text, SDL_Color *color, short size)
{
    Texture t;

    if (0 != t.loadText(text, color, size)) {
        std::cout << "Failed to load text: " << text << std::endl;
    }

    delete color;
    addTexture(t);
}

// Setzt frameDelta
void Animation::setDelta(int frameDelta)
{
    Animation::frameDelta = frameDelta;
}

// Destruktor
Animation::~Animation()
{
}

void Animation::clear()
{
    for (auto &texture : textures) {
        texture.clear();
    }

    textures.clear();
}
