#pragma once

#include "../SDL/SDLWindow.h"

// The theme object
typedef struct Theme
{
    // The dark square color
    SDL_Color darkSqaureColor;

    // The light square color
    SDL_Color lightSquareColor;

    // The chess piece theme. This is the
    // name of the theme folder
    std::string pieceTheme;

}Theme;