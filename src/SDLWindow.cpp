#include "include/SDL/SDLWindow.h"

SDLWindow::SDLWindow(std::string title, LogManager lm)
{
    // Initialize the logger
    w_logger = lm.getLogger("SDLWindow");

    // Only require the title, the rest, set to default
    w_title = title;

    w_width = 800;
    w_height = 800;
    w_xPos = SDL_WINDOWPOS_UNDEFINED;
    w_yPos = SDL_WINDOWPOS_UNDEFINED;
    w_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
}

SDLWindow::~SDLWindow()
{
    // If window exists, delete
    if(window != NULL){
        SDL_DestroyWindow(window);
        window = NULL;
    }

    // Quit SDL and free up memory
    SDL_Quit();
}

void SDLWindow::setWindowSize(int width, int height)
{
    w_width = width;
    w_height = height;
}

void SDLWindow::setWindowPosition(int xPos, int yPos)
{
    w_xPos = xPos;
    w_yPos = yPos;
}

void SDLWindow::setWindowFlags(Uint32 flags)
{
    w_flags = flags;
}

void SDLWindow::createWindow()
{
    // Only initialize SDL if it isn't already initialized.
    // This is to avoid multiple initializations of SDL.
    w_logger->debug("Checking SDL Video Initialization...");
    Uint32 was_sdl_init = SDL_WasInit(SDL_INIT_EVERYTHING);
    if(was_sdl_init & SDL_INIT_VIDEO) // If SDL is already initialized
    {
        w_logger->debug("Video is already initialized, skipping SDL initialization.");
    }
    else // Otherwise initialize SDL
    {
        w_logger->debug("Initializing SDL Video...");
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
            w_logger->critical("SDL could not initialize! SDL Error: {}", SDL_GetError());
            exit(SDL_INIT_ERROR);
        }
    }

    w_logger->debug("Creating a window with the following: \
                      \t\t\tTitle: {} \
                    \n\t\t\tXPos: {}\tYPos: {} \
                    \n\t\t\tWidth: {}\tHeight: {} \
                    \n\t\t\tFlags: {}",
                    w_title, w_xPos, w_yPos, w_width, w_height, w_flags);
    window = SDL_CreateWindow(w_title.c_str(), w_xPos, w_yPos, w_width, w_height, w_flags);
    if(window == NULL)
    {
        w_logger->critical("Window could not be created! SDL Error: {}", SDL_GetError());
        exit(SDL_WINDOW_ERROR);
    }

    SDL_Delay(10000);
}