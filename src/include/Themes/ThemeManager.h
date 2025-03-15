#pragma once

#include <vector>

#include "../Logger/LogManager.h"
#include "Theme.h"

/**
 * The theme manager for the chess game. Themes 
 */
class ThemeManager
{
    public:

        // Constructor that initializes the themes
        ThemeManager(std::shared_ptr<LogManager> lm);

        // Gets the current theme
        Theme getCurrentTheme();

        // Gets the current chess piece theme's root folder. Each theme folder requires a
        // pawn, knight, bishop, king, queen, and rook files in png format.
        std::string getCurrentChessPieceThemePath(bool isWhite);

        // Sets the current board theme
        void setCurrentBoardTheme(int theme);

        // Sets the current piece theme
        void setCurrentPieceTheme(std::string theme);

    private:
        // The class logger
        std::shared_ptr<spdlog::logger> themeManagerLogger;

        // The available current themes
        std::vector<Theme> currentAvailableBoardThemes;

        // The current them of the chess board
        Theme currentTheme;

        // The name of the environment variable for setting board theme
        const std::string boardThemePreferenceEnvVarName = "CURRENT_CHESS_BOARD_THEME";

        // The name of the environment variable for setting piece theme
        const std::string pieceThemePreferenceEnvVarName = "CURRENT_PIECE_THEME";

        // Load hardcoded themes and set current theme from environment variable if available
        // Otherwise load the first one
        // TODO: Read themes and user preference from a file instead.
        void initializeAvailableBoardThemes();

        // Looks in the environment variables for the environment
        // variable named CURRENT_CHESS_BOARD_THEME and if not present
        // Sets 0 as the current theme.
        void loadInitialBoardTheme();

        // Looks in the environment variables for the environment
        // variable named CURRENT_CHESS_PIECE_THEME and if not present
        // Sets "default" as the current theme. The string loaded here
        // is the name of the theme folder that contains the images.
        void loadInitialPieceTheme();
};