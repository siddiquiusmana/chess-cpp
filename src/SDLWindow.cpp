#include "include/SDLWindow.h"

SDLWindow::SDLWindow(string title)
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
    cout << "Checking SDL Video Initialization..." << endl;
    Uint32 was_sdl_init = SDL_WasInit(SDL_INIT_EVERYTHING);
    if(was_sdl_init & SDL_INIT_VIDEO) // If SDL is already initialized
    {
        cout << "Video is already initialized, skipping SDL initialization." << endl;
    }
    else // Otherwise initialize SDL
    {
        cout << "Initializing SDL Video..." << endl;
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
            cout << "SDL could not initialize! SDL Error: " << SDL_GetError();
            exit(-1);
        }
    }

    cout << "\nCreating a window with the following: " << endl;
    cout << "\tTitle: " << w_title << endl;
    cout << "\tXPos: " << w_xPos << "\tYPos: " << w_yPos << endl;
    cout << "\tWidth: " << w_width << "\tHeight: " << w_height << endl;
    cout << "\tFlags: " << w_flags << endl;
    window = SDL_CreateWindow(w_title.c_str(), w_xPos, w_yPos, w_width, w_height, w_flags);
    if(window == NULL)
    {
        cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
        exit(-1);
    }

    SDL_Delay(1000);
}