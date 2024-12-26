#include "../include/SDL/SDLWindow.h"

SDLWindow::SDLWindow(std::string title, std::shared_ptr<LogManager> lm)
{
    // Initialize the logger
    w_logger = lm->getLogger("SDLWindow");
    w_logger->debug("Initializing SDL Window...");

    // Only require the title, the rest, set to default
    w_title = title;

    w_width = 800;
    w_height = 800;
    w_xPos = SDL_WINDOWPOS_UNDEFINED;
    w_yPos = SDL_WINDOWPOS_UNDEFINED;
    w_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;

    // Initialize null pointers
    this->renderer = nullptr;
    window = nullptr;

    w_logger->debug("Initialized SDL Window...");
}

SDLWindow::~SDLWindow()
{
    w_logger->debug("Cleaning up SDL Window...");

    // If this->renderer exists, delete
    if(this->renderer != NULL)
    {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = NULL;
    }

    // If window exists, delete
    if(window != NULL)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    // Quit SDL and free up memory
    SDL_Quit();

    w_logger->debug("Cleaned up SDL Window...");
}

void SDLWindow::setWindowSize(int width, int height)
{
    w_width = width;
    w_height = height;

    w_logger->debug("Window size set to {}x{}", width, height);
}

void SDLWindow::setWindowPosition(int xPos, int yPos)
{
    w_xPos = xPos;
    w_yPos = yPos;

    w_logger->debug("Window posiiton set to ({}, {})", xPos, yPos);
}

void SDLWindow::setWindowFlags(Uint32 flags)
{
    w_flags = flags;

    w_logger->debug("Window flags set to {}", flags);
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

    // Create a window.
    w_logger->debug("Creating a window with the following: \
                    \n\t\t\t\t\t\tTitle: {} \
                    \n\t\t\t\t\t\tXPos: {}\tYPos: {} \
                    \n\t\t\t\t\t\tWidth: {}\tHeight: {} \
                    \n\t\t\t\t\t\tFlags: {}",
                    w_title, w_xPos, w_yPos, w_width, w_height, w_flags);
    window = SDL_CreateWindow(w_title.c_str(), w_xPos, w_yPos, w_width, w_height, w_flags);
    if(window == NULL)
    {
        w_logger->critical("Window could not be created! SDL Error: {}", SDL_GetError());
        exit(SDL_WINDOW_ERROR);
    }
    w_logger->debug("Window created");

    // Create a render for the window so window can be drawn on
    w_logger->debug("Creating a this->renderer for the window");
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(this->renderer == NULL)
    {
        w_logger->critical("Renderer for the window failed to be created. Will be unable to draw");
        exit(SDL_WINDOW_ERROR);
    }
    w_logger->debug("Renderer created");
}

SDL_Window* SDLWindow::getWindow()
{
    return window;
}

SDL_Renderer* SDLWindow::getRenderer()
{
    return this->renderer;
}

int SDLWindow::getWindowWidth()
{
    return w_width;
}

int SDLWindow::getWindowHeight()
{
    return w_height;
}

void SDLWindow::drawLine(Geometry::Point start, Geometry::Point end)
{
    // Draw the line
    if(SDL_RenderDrawLine(this->renderer, start.x, start.y, end.x, end.y) < 0)
    {
        throw SDL_GetError();
    }
}

void SDLWindow::drawLine(Geometry::Point start, Geometry::Point end, SDL_Color color)
{
    // Store the current this->renderer color and set it back once we have drawn the line
    SDL_Color currentRendererColor;
    SDL_GetRenderDrawColor(this->renderer, &(currentRendererColor.r), &(currentRendererColor.g), &(currentRendererColor.b), &(currentRendererColor.a));
    
    // Draw the line with the desired color and set the color back to what it was
    if( SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a) < 0 || 
        SDL_RenderDrawLine(this->renderer, start.x, start.y, end.x, end.y) < 0 || 
        SDL_SetRenderDrawColor(this->renderer, currentRendererColor.r, currentRendererColor.g, currentRendererColor.b, currentRendererColor.a) < 0)
    {
        throw SDL_GetError();
    }
}

void SDLWindow::drawRect(SDL_Rect *rect)
{
    // Draw the rectangle and throw an error if an issue arises
    if(SDL_RenderDrawRect(this->renderer, rect) < 0)
    {
        throw SDL_GetError();
    }
}

void SDLWindow::drawRect(SDL_Rect *rect, SDL_Color color)
{
    // Store the current this->renderer color and set it back once we have drawn the line
    SDL_Color currentRendererColor;
    SDL_GetRenderDrawColor(this->renderer, &(currentRendererColor.r), &(currentRendererColor.g), &(currentRendererColor.b), &(currentRendererColor.a));
    
    // Draw the rectangle with the desired color and set the color back to what it was
    if( SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a) < 0 || 
        SDL_RenderDrawRect(this->renderer, rect) < 0 || 
        SDL_SetRenderDrawColor(this->renderer, currentRendererColor.r, currentRendererColor.g, currentRendererColor.b, currentRendererColor.a) < 0)
    {
        throw SDL_GetError();
    }
}

void SDLWindow::drawFilledRect(SDL_Rect *rect)
{

    // Draw the rectangle and throw an error if an issue arises
    if(SDL_RenderFillRect(this->renderer, rect) < 0)
    {
        throw SDL_GetError();
    }
}

void SDLWindow::drawFilledRect(SDL_Rect *rect, SDL_Color color)
{
    // Store the current this->renderer color and set it back once we have drawn the line
    SDL_Color currentRendererColor;
    SDL_GetRenderDrawColor(this->renderer, &(currentRendererColor.r), &(currentRendererColor.g), &(currentRendererColor.b), &(currentRendererColor.a));
    
    // Draw the rectangle with the desired color and set the color back to what it was
    if( SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a) < 0 || 
        SDL_RenderFillRect(this->renderer, rect) < 0 || 
        SDL_SetRenderDrawColor(this->renderer, currentRendererColor.r, currentRendererColor.g, currentRendererColor.b, currentRendererColor.a) < 0)
    {
        throw SDL_GetError();
    }
}

void SDLWindow::render()
{   
    // Render the buffer
    SDL_RenderPresent(this->renderer);
}

void SDLWindow::renderBackground(SDL_Color color)
{
    // Clear the window with a given color.
    if(SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a) < 0 ||
       SDL_RenderClear(this->renderer) < 0 )
     {
        throw SDL_GetError();
     }
}

void SDLWindow::drawImage(std::string *imageFilePath, SDL_Rect *rect)
{
    // Load the image from the path to Memory
    SDL_Surface *imageSurface = IMG_Load(imageFilePath->c_str());
    if(imageSurface == NULL)
    {
        throw SDL_GetError();
    }

    // Load it into the VRAM
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer, imageSurface);
    if (texture == NULL)
    {
        throw SDL_GetError();
    }

    // Render the image
    if (SDL_RenderCopy (this->renderer, texture, NULL, rect) < 0)
    {
        throw SDL_GetError();
    }
}