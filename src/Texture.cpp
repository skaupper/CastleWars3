///@author Kaupper

#include "Texture.h"
#include <iostream>
#include <sstream>


static int texturecount = 0;

Texture::Texture() : texture(NULL)
{
    flip = false;
}

#define move(tex) \
    { \
        texture = tex.texture; \
        flip = tex.flip; \
        clip = tex.clip; \
        size = tex.size; \
        tex.texture = NULL; \
    }

Texture::Texture(Texture &&tex)
{
    move(tex);
}

Texture &Texture::operator=(Texture &&tex)
{
    move(tex);
    return *this;
}

Texture::~Texture()
{
    if (texture) {
        MANGLE_SDL(SDL_DestroyTexture)(texture);
        Logger::LogDebug("Texture::~Texture");
    }
}

int Texture::loadText(const std::string &text, const SDL_Color &color,
                      short size)
{
    TTF_Font *font = NULL;

    if (size < 0) {
        font = Core::getInstance()->getFont(FontSize::SMALL);
    } else if (size == 0) {
        font = Core::getInstance()->getFont(FontSize::MEDIUM);
    } else if (size > 0) {
        font = Core::getInstance()->getFont(FontSize::LARGE);
    }

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

    if (textSurface == NULL) {
        return -1;
    }

    SDL_Texture *nTexture = NULL;
    nTexture = MANGLE_SDL(SDL_CreateTextureFromSurface)
               (Core::getInstance()->getRenderer(),
                textSurface);

    if (nTexture == NULL) {
        return -2;
    }

    Logger::LogDebug("Texture::Texture");
    MANGLE_SDL(SDL_FreeSurface)(textSurface);
    texture = nTexture;
    int w, h;
    MANGLE_SDL(SDL_QueryTexture)(texture, NULL, NULL, &w, &h);
    Texture::clip = Texture::size = { 0, 0, w, h };
    return 0;
}

int Texture::loadImage(const std::string &path)
{
    SDL_Texture *nTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL) {
        return -1;
    }

    nTexture = MANGLE_SDL(SDL_CreateTextureFromSurface)
               (Core::getInstance()->getRenderer(),
                loadedSurface);

    if (nTexture == NULL) {
        return -2;
    }

    Logger::LogDebug("Texture::Texture");
    clip = { 0, 0, loadedSurface->w, loadedSurface->h };
    size = clip;
    MANGLE_SDL(SDL_FreeSurface)(loadedSurface);
    texture = nTexture;
    return 0;
}

int Texture::loadImage(const std::string &path, const SDL_Rect &clip)
{
    int status = loadImage(path);
    Texture::clip = clip;
    Texture::size = clip;
    return status;
}

int Texture::loadImage(const std::string &path, const SDL_Rect &clip,
                       const SDL_Rect &size)
{
    int status = loadImage(path);
    Texture::clip = clip;
    Texture::size = size;
    return status;
}

SDL_Rect Texture::getSize()
{
    return size;
}

void Texture::setSize(int w, int h)
{
    if (w != 0) {
        size.w = w;
    }

    if (h != 0) {
        size.h = h;
    }
}

void Texture::setSize(const SDL_Rect &rect)
{
    size = rect;
}

int Texture::onRender(const Location &loc, bool flip)
{
    SDL_Renderer *renderer = Core::getInstance()->getRenderer();
    SDL_Rect rect { (int) loc.x, (int) loc.y, (int) size.w, (int) size.h };
    SDL_Point point { getSize().x / 2, 0 };
    int ret;

    if (flip) {
        ret = MANGLE_SDL(SDL_RenderCopyEx)(renderer, texture, &clip, &rect, 0, &point,
                                           SDL_FLIP_HORIZONTAL);
    } else {
        ret =  MANGLE_SDL(SDL_RenderCopy)(renderer, texture, &clip, &rect);
    }

    return ret;
}
