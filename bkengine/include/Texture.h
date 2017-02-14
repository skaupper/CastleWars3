///@author Kaupper

#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <iostream>

#include <string>
#include <memory>
#include <map>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Location.h"
#include "Core.h"


class Color
{
    public:
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        bool operator==(const Color &c) const
        {
            return r == c.r && g == c.g && b == c.b && a == c.a;
        }
        bool operator<(const Color &c) const
        {
            return (r + g + b + a) < (c.r + c.g + c.b + c.a);
        }
};

class TextureWrapper
{
    public:
        TextureWrapper(SDL_Texture *tex)
        {
            set(tex);
        }

        virtual ~TextureWrapper()
        {
            free();
        }

        SDL_Texture *get()
        {
            return texture;
        }

        void set(SDL_Texture *tex)
        {
            free();
            texture = tex;
        }

        void free()
        {
            if (texture) {
                MANGLE_SDL(SDL_DestroyTexture)(texture);
                texture = NULL;
            }
        }

    private:
        SDL_Texture *texture = NULL;
};

class Texture
{
    public:
        Texture();
        virtual ~Texture();

        std::shared_ptr<TextureWrapper> getCached(const std::string &s);
        std::shared_ptr<TextureWrapper> getCached(const std::string &s, const Color &c,
                short size);

        bool hasTextureCached(const std::string &s);
        bool hasTextureCached(const std::string &s, const Color &c, short size);

        int loadText(const std::string &text, const Color &color, short size = 0);

        int loadImage(const std::string &path);
        int loadImage(const std::string &path, const SDL_Rect &clip);
        int loadImage(const std::string &path, const SDL_Rect &clip,
                      const SDL_Rect &size);

        SDL_Rect getSize();
        void setSize(int w, int h);
        void setSize(const SDL_Rect &rect);

        int onRender(const Location &loc, bool flip = false);

    protected:
        bool flip;
        std::shared_ptr<TextureWrapper> texture;
        SDL_Rect clip;
        SDL_Rect size;

        static std::map<std::string, std::shared_ptr<TextureWrapper>> imageCache;
        static std::map<std::string, std::map<Color, std::map<short, std::shared_ptr<TextureWrapper>>>>
        textCache;
};

#endif // TEXTURE_H_INCLUDED
