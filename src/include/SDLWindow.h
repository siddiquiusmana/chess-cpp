#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <SDL2/SDL.h>
#include "SDLErrorCodes.h"

/**
 * The window class for creating an SDLWindow. The constructor only initializes
 * the object but createWindow() must be called to actually create a window.
 */
class SDLWindow
{
    private:
        // The SDL_Window ptr to the window
        SDL_Window* window;

        // The window title
        std::string w_title;

        // The window width
        int w_width;

        // The window height
        int w_height;

        // The window x position on screen
        int w_xPos;

        // The window y position on screen
        int w_yPos;

        // The window flags
        Uint32 w_flags;

    public:
        // Constructor for the SDLWindow class, takes in the title of the window.
        SDLWindow(std::string title);

        // Sets the window size of the SDLWindow
        void setWindowSize(int width, int height);

        // Sets the window position of the SDLWindow
        void setWindowPosition(int xPos, int yPos);

        // Sets the window flags of the SDLWindow
        void setWindowFlags(Uint32 flags);

        // Creates the SDLWindow.
        // If windowSize, windowPosition or windowFlags are not set when createWindow is called,
        // the following default values will be used when creating the window:
        // windowSize: 800x800
        // windowPosition: unknown (OS decides)
        // windowFlags: shown
        void createWindow();

        // Destructor for the SDLWindow class, deletes the window ptr when it is destroyed.
        ~SDLWindow();

        // The getter for SDL_Window
        SDL_Window* getSDLWindow();

    protected:
};

#endif // WINDOW_H