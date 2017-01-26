///@author Kaupper

#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Location.h"
#include "Core.h"


class Texture
{
    public:
        Texture();
        virtual ~Texture();

        int loadText(const std::string &text, const SDL_Color &color, short size = 0);

        int loadImage(const std::string &path);
        int loadImage(const std::string &path, const SDL_Rect &clip);
        int loadImage(const std::string &path, const SDL_Rect &clip, const SDL_Rect &size);

        SDL_Rect getSize();
        void setSize(int w, int h);

        int onRender(const Location &loc, bool flip = false);

    private:
        bool flip;
        SDL_Texture *texture = NULL;
        SDL_Rect clip;
        SDL_Rect size;
};

#endif // TEXTURE_H_INCLUDED
