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

        // Sets the current theme
        void setCurrentTheme(int theme);

    private:
        // The class logger
        std::shared_ptr<spdlog::logger> themeManagerLogger;

        // The available current themes
        std::vector<Theme> currentAvailableThemes;

        // The current them of the chess board
        Theme currentTheme;

        // The name of the environment variable for setting theme
        const std::string environmentVarName = "CURRENT_CHESS_THEME";

        // Apart from hardcoded themes, reads in other 
        // user configured themes
        void intializeAvailableThemes();

        // Looks in the environment variables for the environment
        // variable named CURRENT_CHESS_THEME and if not present
        // Sets 0 as the current theme.
        void loadInitialTheme();
};