///@author Kaupper

#include "Core.h"
#include <iostream>

//singleton
Core *Core::instance = NULL;
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
    windowWidth(width),
    window(NULL),
    renderer(NULL),
    largeFont(NULL),
    mediumFont(NULL),
    smallFont(NULL),
    inited(false)
{
}

Core::~Core()
{
    if (renderer != NULL) {
        std::cout << "close renderer" << std::endl;
        MANGLE_SDL(SDL_DestroyRenderer)(renderer);
        renderer = NULL;
    }

    if (window != NULL) {
        std::cout << "close window" << std::endl;
        MANGLE_SDL(SDL_DestroyWindow)(window);
        window = NULL;
    }

    if (largeFont != NULL) {
        std::cout << "close font" << std::endl;
        TTF_CloseFont(largeFont);
        largeFont = NULL;
    }

    if (mediumFont != NULL) {
        std::cout << "close font" << std::endl;
        TTF_CloseFont(mediumFont);
        mediumFont = NULL;
    }

    if (smallFont != NULL) {
        std::cout << "close font" << std::endl;
        TTF_CloseFont(smallFont);
        smallFont = NULL;
    }

    std::cout << "core destructed" << std::endl;
}

void Core::quit()
{
    delete instance;
    instance = NULL;
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    MANGLE_SDL(SDL_Quit)();
    std::cout << "core quitted" << std::endl;
}

int Core::init()
{
    //initialisiert sdl, sdl_image, sdl_ttf, sdl_mixer
    if (MANGLE_SDL(SDL_Init)(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        return -1;
    }

    if (!MANGLE_SDL(SDL_SetHint)(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        MANGLE_SDL(SDL_Quit)();
        return -2;
    }

    int imgFlags = IMG_INIT_PNG;

    if (!(IMG_Init(imgFlags) & imgFlags)) {
        MANGLE_SDL(SDL_Quit)();
        return -3;
    }

    if (TTF_Init() == -1) {
        MANGLE_SDL(SDL_Quit)();
        IMG_Quit();
        return -4;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        MANGLE_SDL(SDL_Quit)();
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
        window = MANGLE_SDL(SDL_CreateWindow)(windowTitle.c_str(),
                                             SDL_WINDOWPOS_UNDEFINED,
                                             SDL_WINDOWPOS_UNDEFINED, windowWidth,
                                             windowHeight, SDL_WINDOW_SHOWN);

        if (window == NULL) {
            return -6;
        }

        SDL_Surface *iconSurface = IMG_Load("icon.ico");
        MANGLE_SDL(SDL_SetWindowIcon)(window, iconSurface);
        MANGLE_SDL(SDL_FreeSurface)(iconSurface);
        renderer = MANGLE_SDL(SDL_CreateRenderer)(window, -1, SDL_RENDERER_ACCELERATED);

        if (renderer == NULL) {
            return -7;
        }

        //setzt den standard hintergrund
        MANGLE_SDL(SDL_SetRenderDrawColor)(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
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

Core *Core::getInstance()
{
    if (!instance) {
        instance = new Core(800, 600, "TestWindow");
    }

    if (!instance->inited) {
        if (instance->setup() != 0) {
            throw "Core setup failed";
        }
    }

    return instance;
}

Core *Core::getInstance(int width, int height, const std::string &windowTitle)
{
    //singleton
    if (!instance) {
        return (instance = new Core(width, height, windowTitle));
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
