#ifndef SDL_TEMPLATES_H
#define SDL_TEMPLATES_H

#include "SDLWrapper.h"

const char *test_SDL_GetError();
void test_SDL_DestroyRenderer(SDL_Renderer *renderer);
void test_SDL_DestroyWindow(SDL_Window *window);
void test_SDL_Quit();
int test_SDL_Init(uint32_t flags);
SDL_bool test_SDL_SetHint(const char *name, const char *value);
SDL_Window *test_SDL_CreateWindow(const char *title, int x,
                                  int y, int w, int h, uint32_t flags);
void test_SDL_SetWindowIcon(SDL_Window *window,
                            SDL_Surface *surface);
void test_SDL_FreeSurface(SDL_Surface *surface);
SDL_Renderer *test_SDL_CreateRenderer(SDL_Window *window,
                                      int index, uint32_t flags);
int test_SDL_SetRenderDrawColor(SDL_Renderer *renderer,
                                uint8_t r, uint8_t g, uint8_t b, uint8_t a);
int test_SDL_PollEvent(SDL_Event *event);
void test_SDL_Delay(uint32_t ms);
int test_SDL_RenderClear(SDL_Renderer *renderer);
void test_SDL_RenderPresent(SDL_Renderer *renderer);
void test_SDL_DestroyTexture(SDL_Texture *texture);
SDL_Texture *test_SDL_CreateTextureFromSurface(
    SDL_Renderer *renderer, SDL_Surface *surface);
int test_SDL_QueryTexture(SDL_Texture *texture,
                          uint32_t *format, int *access, int *w, int *h);
int test_SDL_RenderCopyEx(SDL_Renderer *renderer,
                          SDL_Texture *texture, const SDL_Rect *srcrect,
                          const SDL_Rect *dstrect, const double angle, const SDL_Point *center,
                          const SDL_RendererFlip flip);
int test_SDL_RenderCopy(SDL_Renderer *renderer,
                        SDL_Texture *texture, const SDL_Rect *srcrect,
                        const SDL_Rect *dstrect);
uint32_t test_SDL_GetTicks();

int test_TTF_Init();
TTF_Font *test_TTF_OpenFont(const char *, int);
SDL_Surface *test_TTF_RenderText_Solid(TTF_Font *, const char *, SDL_Color);
void test_TTF_CloseFont(TTF_Font *);
void test_TTF_Quit();

int test_IMG_Init(int);
SDL_Surface *test_IMG_Load(const char *);
void test_IMG_Quit();

int test_Mix_OpenAudio(int, uint16_t, int, int);
void test_Mix_Quit();

#endif
