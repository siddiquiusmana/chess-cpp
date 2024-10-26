#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

int main(void)
{
    SDL_Window *window = nullptr;
    
    // Initialize SDL and throw an error if it fails
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        return -1;
    }
    else
    {
        window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        if(window == NULL)
        {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            return -1;
        }
        else
        {
            SDL_Delay(2000);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}