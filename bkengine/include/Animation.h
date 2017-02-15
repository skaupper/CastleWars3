///@Author B�hmi

#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>

#include "Texture.h"
#include "Logger.h"

class Animation
{
    public:
        Animation(const std::string &descr = "", unsigned int frameDelta = 1);
        virtual ~Animation();

        void addImage(const std::string &path);
        void addImage(const std::string &path, SDL_Rect rect);
        void addText(const std::string &text, const Color &color, short size);

        template <typename T> void addImage(const std::string &path);
        template <typename T> void addImage(const std::string &path, SDL_Rect rect);
        template <typename T> void addText(const std::string &text, const Color &color,
                                           short size);
        template <typename T> void addTexture(const T &texture);

        bool hasTexture(unsigned int index);

        Texture &getNextTexture();
        Texture &getCurrentTexture();

        void incFrameCount();
        void setFramesPerTexture(unsigned int frames);

        void reset();

        std::string getDescription();

    protected:
        unsigned int frameCounter;
        unsigned int framesPerTexture;
        int currentIndex;
        std::vector<Texture> textures;
        std::string description;
};


template <typename T> void Animation::addImage(const std::string &path)
{
    T t;
    int status = t.loadImage(path);

    if (status != 0) {
        Logger::LogError("Animation::addImage(const std::string &): Failed to load Texture ("
                         + std::string(MANGLE_SDL(SDL_GetError)()) + ")");
        return;
    }

    addTexture<T>(t);
}

template <typename T> void Animation::addImage(const std::string &path,
        SDL_Rect size)
{
    addImage<T>(path);
    textures.back().setSize(size);
}

template <typename T> void Animation::addText(const std::string &text,
        const Color &color, short size)
{
    T t;
    int status = t.loadText(text, color, size);

    if (status != 0) {
        Logger::LogError("Animation::addText(const std::string &, SDL_Color, short): Failed to load text ("
                         + std::string(MANGLE_SDL(SDL_GetError)()) + ")");
        return;
    }

    addTexture<T>(t);
}

template <typename T> void Animation::addTexture(const T &texture)
{
    textures.push_back(std::move((T &) texture));

    if (textures.size() == 1) {
        currentIndex = 0;
    }
}

#endif // ANIMATION_H
