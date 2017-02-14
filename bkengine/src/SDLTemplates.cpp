#include "SDLTemplates.h"

const char *test_SDL_GetError()
{
    return SDLProvider::getInstance()->SDL_GetError();
}

void test_SDL_DestroyRenderer(SDL_Renderer *renderer)
{
    SDLProvider::getInstance()->SDL_DestroyRenderer(renderer);
}

void test_SDL_DestroyWindow(SDL_Window *window)
{
    SDLProvider::getInstance()->SDL_DestroyWindow(window);
}

void test_SDL_Quit()
{
    SDLProvider::getInstance()->SDL_Quit();
}

int test_SDL_Init(uint32_t flags)
{
    return SDLProvider::getInstance()->SDL_Init(flags);
}

SDL_bool test_SDL_SetHint(const char *name, const char *value)
{
    return SDLProvider::getInstance()->SDL_SetHint(name, value);
}

SDL_Window *test_SDL_CreateWindow(const char *title, int x,
                                  int y, int w, int h, uint32_t flags)
{
    return SDLProvider::getInstance()->SDL_CreateWindow(title, x, y, w, h, flags);
}

void test_SDL_SetWindowIcon(SDL_Window *window,
                            SDL_Surface *surface)
{
    SDLProvider::getInstance()->SDL_SetWindowIcon(window, surface);
}

void test_SDL_FreeSurface(SDL_Surface *surface)
{
    SDLProvider::getInstance()->SDL_FreeSurface(surface);
}

SDL_Renderer *test_SDL_CreateRenderer(SDL_Window *window,
                                      int index, uint32_t flags)
{
    return SDLProvider::getInstance()->SDL_CreateRenderer(window, index, flags);
}

int test_SDL_SetRenderDrawColor(SDL_Renderer *renderer,
                                uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return SDLProvider::getInstance()->SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

int test_SDL_PollEvent(SDL_Event *event)
{
    return SDLProvider::getInstance()->SDL_PollEvent(event);
}

void test_SDL_Delay(uint32_t ms)
{
    SDLProvider::getInstance()->SDL_Delay(ms);
}

int test_SDL_RenderClear(SDL_Renderer *renderer)
{
    return SDLProvider::getInstance()->SDL_RenderClear(renderer);
}

void test_SDL_RenderPresent(SDL_Renderer *renderer)
{
    SDLProvider::getInstance()->SDL_RenderPresent(renderer);
}

void test_SDL_DestroyTexture(SDL_Texture *texture)
{
    SDLProvider::getInstance()->SDL_DestroyTexture(texture);
}

SDL_Texture *test_SDL_CreateTextureFromSurface(
    SDL_Renderer *renderer, SDL_Surface *surface)
{
    return SDLProvider::getInstance()->SDL_CreateTextureFromSurface(renderer,
            surface);
}

int test_SDL_QueryTexture(SDL_Texture *texture,
                          uint32_t *format, int *access, int *w, int *h)
{
    return SDLProvider::getInstance()->SDL_QueryTexture(texture, format, access, w,
            h);
}

int test_SDL_RenderCopyEx(SDL_Renderer *renderer,
                          SDL_Texture *texture, const SDL_Rect *srcrect,
                          const SDL_Rect *dstrect, const double angle, const SDL_Point *center,
                          const SDL_RendererFlip flip)
{
    return SDLProvider::getInstance()->SDL_RenderCopyEx(renderer, texture, srcrect,
            dstrect, angle,
            center, flip);
}

int test_SDL_RenderCopy(SDL_Renderer *renderer,
                        SDL_Texture *texture, const SDL_Rect *srcrect,
                        const SDL_Rect *dstrect)
{
    return SDLProvider::getInstance()->SDL_RenderCopy(renderer, texture, srcrect,
            dstrect);
}

uint32_t test_SDL_GetTicks()
{
    return SDLProvider::getInstance()->SDL_GetTicks();
}


int test_TTF_Init()
{
    return SDLProvider::getInstance()->TTF_Init();
}

TTF_Font *test_TTF_OpenFont(const char *path, int size)
{
    return SDLProvider::getInstance()->TTF_OpenFont(path, size);
}

SDL_Surface *test_TTF_RenderText_Solid(TTF_Font *font, const char *text,
                                       SDL_Color color)
{
    return SDLProvider::getInstance()->TTF_RenderText_Solid(font, text, color);
}

void test_TTF_CloseFont(TTF_Font *font)
{
    SDLProvider::getInstance()->TTF_CloseFont(font);
}

void test_TTF_Quit()
{
    SDLProvider::getInstance()->TTF_Quit();
}


int test_IMG_Init(int flags)
{
    return SDLProvider::getInstance()->IMG_Init(flags);
}

SDL_Surface *test_IMG_Load(const char *path)
{
    return SDLProvider::getInstance()->IMG_Load(path);
}

void test_IMG_Quit()
{
    SDLProvider::getInstance()->IMG_Quit();
}


int test_Mix_OpenAudio(int frequency, uint16_t channel, int format,
                       int chunksize)
{
    return SDLProvider::getInstance()->Mix_OpenAudio(frequency, channel, format,
            chunksize);
}

void test_Mix_Quit()
{
    SDLProvider::getInstance()->Mix_Quit();
}
