#include "../SDL/SDLWindow.h"

// The theme object
typedef struct Theme
{
    // The dark square color
    SDL_Color darkSqaureColor;

    // The light square color
    SDL_Color lightSquareColor;

    // The dark piece color
    SDL_Color darkPieceColor;

    // The light piece color
    SDL_Color lightPieceColor;
}Theme;