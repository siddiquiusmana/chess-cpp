#pragma once

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <SDL2/SDL.h>

#include "../Logger/LogManager.h"
#include "Geometry.h"
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

        // The class logger
        std::shared_ptr<spdlog::logger> w_logger;

        // The renderer specific to this window, allowing for 
        // drawing to the window
        SDL_Renderer *renderer;

    public:
        // Constructor for the SDLWindow class, takes in the title of the window and a logger
        SDLWindow(std::string title, std::shared_ptr<LogManager> lm);

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
        SDL_Window* getWindow();
        
        // Retrieve the width of the window
        int getWindowWidth();

        // Retrieve the height of the window
        int getWindowHeight();
        
        // Retrieve the renderer for this window which allows you to draw on the waindow
        SDL_Renderer* getRenderer();

        // Draws a line on the window using the given start/end points.
        void drawLine(Geometry::Point start, Geometry::Point end);

        // Draws a line on the window using the given color, start/end points
        void drawLine(Geometry::Point start, Geometry::Point end, SDL_Color color);

        // Draws a rectangle to the window given the top left point and the bottom right points
        void drawRect(SDL_Rect *rect);

        // Draws a rectangle to the window given the top left point and the bottom right points with
        // color specified
        void drawRect(SDL_Rect *rect, SDL_Color color);

        // Draws a rectangle filled with a solid color to the window given a rectangle object
        void drawFilledRect(SDL_Rect *rect);

        // Draws a rectangle filled with a solid color to the window given a rectangle object 
        // and a specific color
        void drawFilledRect(SDL_Rect *rect, SDL_Color color);

        // Renders the background for the window
        void renderBackground(SDL_Color color);

        // Renders the changes made so far
        void render();
};

#endif // WINDOW_H