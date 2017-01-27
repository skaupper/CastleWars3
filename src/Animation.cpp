/// @Author B�hmi

#include <iostream>

#include "Animation.h"


Animation::Animation(const std::string &description, int framesPerTexture) :
    frameCounter(0),
    framesPerTexture(framesPerTexture),
    currentIndex(0),
    description(description)
{
}

void Animation::reset()
{
    frameCounter = 0;
    currentIndex = -1;
}

Texture &Animation::getNextTexture()
{
    auto &tmp = getCurrentTexture();
    incFrameCount();
    return tmp;
}

Texture &Animation::getCurrentTexture()
{
    if (hasTexture(currentIndex)) {
        return textures[currentIndex];
    }

    Logger::LogCritical("Animation::getCurrentTexture(): Texture not found");
    throw "Texture not found";
}

bool Animation::hasTexture(int index)
{
    return index >= 0 && index < textures.size();
}

void Animation::addTexture(const Texture &texture)
{
    textures.push_back(std::move((Texture &) texture));

    if (textures.size() == 1) {
        currentIndex = 0;
    }
}

void Animation::incFrameCount()
{
    if (framesPerTexture <= 0) {
        return;
    }

    if (frameCounter < framesPerTexture - 1) {
        frameCounter++;
    } else {
        frameCounter = 0;
        currentIndex = (currentIndex + 1) % textures.size();
    }
}

void Animation::addImage(const std::string &path)
{
    Texture t;
    int status = t.loadImage(path);

    if (status != 0) {
        Logger::LogError("Animation::addImage(const std::string &): Failed to load Texture (" + std::string(MANGLE_SDL(SDL_GetError)()) + ")");
        return;
    }

    addTexture(t);
}

void Animation::addImage(const std::string &path, SDL_Rect size)
{
    addImage(path);
    textures.back().setSize(size);
}

void Animation::addText(const std::string &text, SDL_Color color, short size)
{
    Texture t;
    int status = t.loadText(text, color, size);
    if (status != 0) {
        Logger::LogError("Animation::addText(const std::string &, SDL_Color, short): Failed to load text (" + std::string(MANGLE_SDL(SDL_GetError)()) + ")");
        return;
    }

    addTexture(t);
}

void Animation::setFramesPerTexture(int frames)
{
    framesPerTexture = frames;
}

Animation::~Animation()
{
    textures.clear();
}

std::string Animation::getDescription()
{
    return description;
}
