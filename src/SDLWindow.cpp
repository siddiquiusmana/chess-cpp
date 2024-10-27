#include "include/SDLWindow.h"

SDLWindow::SDLWindow(std::string title)
{
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
    std::cout << "Checking SDL Video Initialization..." << std::endl;
    Uint32 was_sdl_init = SDL_WasInit(SDL_INIT_EVERYTHING);
    if(was_sdl_init & SDL_INIT_VIDEO) // If SDL is already initialized
    {
        std::cout << "Video is already initialized, skipping SDL initialization." << std::endl;
    }
    else // Otherwise initialize SDL
    {
        std::cout << "Initializing SDL Video..." << std::endl;
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
            std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError();
            exit(SDL_INIT_ERROR);
        }
    }

    std::cout << "\nCreating a window with the following: " << std::endl;
    std::cout << "\tTitle: " << w_title << std::endl;
    std::cout << "\tXPos: " << w_xPos << "\tYPos: " << w_yPos << std::endl;
    std::cout << "\tWidth: " << w_width << "\tHeight: " << w_height << std::endl;
    std::cout << "\tFlags: " << w_flags << std::endl;
    window = SDL_CreateWindow(w_title.c_str(), w_xPos, w_yPos, w_width, w_height, w_flags);
    if(window == NULL)
    {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        exit(SDL_WINDOW_ERROR);
    }

    SDL_Delay(10000);
}