#ifndef SDL_MOCK_H
#define SDL_MOCK_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "gmock/gmock.h"
#include "SDLWrapper.h"

using namespace ::testing;

class SDLMock : public SDL
{
    public:
        SDLMock() {}

        MOCK_METHOD0(SDL_GetError, const char *());
        MOCK_METHOD1(SDL_DestroyRenderer, void (SDL_Renderer *));
        MOCK_METHOD1(SDL_DestroyWindow, void (SDL_Window *));
        MOCK_METHOD0(SDL_Quit, void ());
        MOCK_METHOD1(SDL_Init, int (uint32_t));
        MOCK_METHOD2(SDL_SetHint, SDL_bool(const char *, const char *));
        MOCK_METHOD6(SDL_CreateWindow, SDL_Window * (const char *, int, int, int, int,
                     uint32_t));
        MOCK_METHOD2(SDL_SetWindowIcon, void (SDL_Window *, SDL_Surface *));
        MOCK_METHOD1(SDL_FreeSurface, void (SDL_Surface *));
        MOCK_METHOD3(SDL_CreateRenderer, SDL_Renderer * (SDL_Window *, int, uint32_t));
        MOCK_METHOD5(SDL_SetRenderDrawColor, int (SDL_Renderer *, uint8_t, uint8_t,
                     uint8_t, uint8_t));
        MOCK_METHOD1(SDL_PollEvent, int (SDL_Event *));
        MOCK_METHOD1(SDL_Delay, void (uint32_t));
        MOCK_METHOD1(SDL_RenderClear, int (SDL_Renderer *));
        MOCK_METHOD1(SDL_RenderPresent, void (SDL_Renderer *));
        MOCK_METHOD1(SDL_DestroyTexture, void (SDL_Texture *));
        MOCK_METHOD2(SDL_CreateTextureFromSurface, SDL_Texture * (SDL_Renderer *,
                     SDL_Surface *));
        MOCK_METHOD5(SDL_QueryTexture, int (SDL_Texture *, uint32_t *, int *, int *,
                                            int *));
        MOCK_METHOD7(SDL_RenderCopyEx, int (SDL_Renderer *, SDL_Texture *,
                                            const SDL_Rect *,
                                            const SDL_Rect *, const double, const SDL_Point *, const SDL_RendererFlip));
        MOCK_METHOD4(SDL_RenderCopy, int (SDL_Renderer *, SDL_Texture *,
                                          const SDL_Rect *,
                                          const SDL_Rect *));
        MOCK_METHOD0(SDL_GetTicks, uint32_t ());
};

#endif
