///@author Kaupper

#include "Core.h"
#include <iostream>

//singleton
Core Core::instance;
bool Core::instantiated = false;
bool Core::depsInited = false;

Core::Core()
{
}

#define copy(core) \
    { \
        windowTitle = core.windowTitle; \
        windowHeight = core.windowHeight; \
        windowWidth = core.windowWidth; \
        renderer = core.renderer; \
        window = core.window; \
        largeFont = core.largeFont; \
        mediumFont = core.mediumFont; \
        smallFont = core.smallFont; \
        isValid = core.isValid; \
        core.renderer = NULL; \
        core.window = NULL; \
        core.largeFont = NULL; \
        core.mediumFont = NULL; \
        core.smallFont = NULL; \
        core.isValid = false; \
    }

Core &Core::operator=(Core &&core)
{
    copy(core);
    core.isValid = false;
    return *this;
}

Core::Core(Core &&core)
{
    copy(core);
    core.isValid = false;
}

Core::Core(int width, int height, const std::string &windowTitle) :
    windowTitle(windowTitle),
    windowHeight(height),
    windowWidth(width)
{
    instantiated = true;
}

Core::~Core()
{
    if (!window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    if (!renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }

    if (!largeFont) {
        TTF_CloseFont(largeFont);
        largeFont = NULL;
    }

    if (!mediumFont) {
        TTF_CloseFont(mediumFont);
        mediumFont = NULL;
    }

    if (!smallFont) {
        TTF_CloseFont(smallFont);
        smallFont = NULL;
    }
}

void Core::quit()
{
    instance = Core();
    instantiated = false;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    Mix_Quit();
}

int Core::init()
{
    //initialisiert sdl, sdl_image, sdl_ttf, sdl_mixer
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        return -1;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        SDL_Quit();
        return -2;
    }

    int imgFlags = IMG_INIT_PNG;

    if (!(IMG_Init(imgFlags) & imgFlags)) {
        SDL_Quit();
        return -3;
    }

    if (TTF_Init() == -1) {
        SDL_Quit();
        IMG_Quit();
        return -4;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Quit();
        IMG_Quit();
        TTF_Quit();
        return -5;
    }

    depsInited = true;
    return 0;
}

int Core::setup()
{
    if (!depsInited) {
        int status = init();

        if (status != 0) {
            return status;
        }
    }

    if (!inited) {
        //erstellt ein sdl fenster mit titel weite und h�he
        window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, windowWidth,
                                  windowHeight, SDL_WINDOW_SHOWN);

        if (window == NULL) {
            return -6;
        }

        SDL_Surface *iconSurface = IMG_Load("icon.ico");
        SDL_SetWindowIcon(window, iconSurface);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (renderer == NULL) {
            return -7;
        }

        //setzt den standard hintergrund
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        int size = 50;

        // TODO: make font size relative
        if (windowHeight == 480) {
            size = 40;
        } else if (windowHeight == 600) {
            size = 48;
        } else if (windowHeight == 768) {
            size = 58;
        }

        largeFont = TTF_OpenFont("FUTURAB.ttf", size);
        mediumFont = TTF_OpenFont("FUTURAB.ttf", size / 2);
        smallFont = TTF_OpenFont("FUTURAB.ttf", size / 4);

        if (largeFont == NULL || mediumFont == NULL || smallFont == NULL) {
            std::cout << "font fail" << std::endl;
            return -8;
        }

        inited = true;
    }

    return 0;
}

bool Core::isInstantiated()
{
    return instantiated;
}

Core &Core::getInstance()
{
    if (!instantiated) {
        throw "No core instance created";
    }

    return instance;
}

Core &Core::getInstance(int width, int height, const std::string &windowTitle)
{
    //singleton
    if (!instantiated) {
        return (instance = std::move(Core(width, height, windowTitle)));
    }

    return instance;
}




SDL_Renderer *Core::getRenderer()
{
    return renderer;
}

int Core::getWindowHeight()
{
    return windowHeight;
}

int Core::getWindowWidth()
{
    return windowWidth;
}

std::string Core::getWindowTitle()
{
    return windowTitle;
}

TTF_Font *Core::getFont(FontSize size)
{
    switch (size) {
        case FontSize::SMALL:
            return smallFont;

        case FontSize::MEDIUM:
            return mediumFont;

        case FontSize::LARGE:
            return largeFont;
    }
}
