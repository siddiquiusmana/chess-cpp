#include "../include/Themes/ThemeManager.h"

ThemeManager::ThemeManager(std::shared_ptr<LogManager> lm)
{
    // Initialize the logger
    themeManagerLogger = lm->getLogger("ThemeManager");

    // Initialize the themes
    ThemeManager::initializeAvailableBoardThemes();
    ThemeManager::loadInitialPieceTheme();
}

void ThemeManager::initializeAvailableBoardThemes()
{
    // Hardcode some themes
    Theme standardBlackAndWhiteTheme;
    standardBlackAndWhiteTheme.darkSqaureColor = {0,0,0,0};
    standardBlackAndWhiteTheme.lightSquareColor = {255,255,255,255};

    Theme chessDotComTheme;
    chessDotComTheme.darkSqaureColor = {119, 148, 85, 100};
    chessDotComTheme.lightSquareColor = {235, 235, 208, 100};

    Theme oldSchoolGreenAndWhiteTheme;
    oldSchoolGreenAndWhiteTheme.darkSqaureColor = {67, 97, 87, 100};
    oldSchoolGreenAndWhiteTheme.lightSquareColor = {233, 227, 203, 100};

    Theme brownAndWhiteTheme;
    brownAndWhiteTheme.darkSqaureColor = {134, 92, 93, 100};
    brownAndWhiteTheme.lightSquareColor = {221, 212, 195, 100};

    currentAvailableBoardThemes.push_back(standardBlackAndWhiteTheme);
    currentAvailableBoardThemes.push_back(chessDotComTheme);
    currentAvailableBoardThemes.push_back(oldSchoolGreenAndWhiteTheme);
    currentAvailableBoardThemes.push_back(brownAndWhiteTheme);

    // TODO read in more themes somehow

    themeManagerLogger->trace("Added the following themes: ");
    int i=0;
    for(auto theme: currentAvailableBoardThemes)
    {
        themeManagerLogger->trace("Theme {}\n \
                                   \t\t\tDark Square Color: r{}g{}b{}a{}\n \
                                   \t\t\tLight Square Color: r{}g{}b{}a{}", 
                                   i,
                                   theme.darkSqaureColor.r, theme.darkSqaureColor.g, theme.darkSqaureColor.b, theme.darkSqaureColor.a,
                                   theme.lightSquareColor.r, theme.lightSquareColor.g, theme.lightSquareColor.b, theme.lightSquareColor.a);

        i++;
    }

    // Either read the user preference or set default.
    loadInitialBoardTheme();
}

void ThemeManager::setCurrentBoardTheme(int theme)
{
    // Check whether its a valid theme to be set
    if(theme < 0 || theme >= currentAvailableBoardThemes.size())
    {
        themeManagerLogger->error("Requesting to set an invalid theme {}, defaulting to 0", theme);
        currentTheme.darkSqaureColor = currentAvailableBoardThemes.at(0).darkSqaureColor;
        currentTheme.lightSquareColor = currentAvailableBoardThemes.at(0).lightSquareColor;
        return;
    }
    
    // Set the theme
    currentTheme.darkSqaureColor = currentAvailableBoardThemes.at(theme).darkSqaureColor;
    currentTheme.lightSquareColor = currentAvailableBoardThemes.at(theme).lightSquareColor;
}

void ThemeManager::loadInitialBoardTheme()
{
    // Read an environment variable. If one doesn't exst, default to 0
    char* environmentSetTheme = std::getenv(boardThemePreferenceEnvVarName.c_str());
    if(environmentSetTheme == nullptr)
    {
        themeManagerLogger->debug("No environment variable of name {} set. Using default board theme of 0", boardThemePreferenceEnvVarName);
        setCurrentBoardTheme(0);
        return;
    }

    // Otherwise try to set the user preference
    try
    {
        int theme = std::stoi(environmentSetTheme);
        themeManagerLogger->debug("Found an environment variable for setting board theme. Setting it to {}", theme);
        setCurrentBoardTheme(theme);
    }
    catch(std::invalid_argument &e)
    {
        themeManagerLogger->error("Error converting the board theme from environment variables. Not a valid theme. Setting the board theme to the default of 0.");
        setCurrentBoardTheme(0);
        return;
    }
    catch(std::out_of_range &e)
    {
        themeManagerLogger->error("Error converting the board theme from environment variables. Integer out of range. Setting the boardtheme to the default of 0.");
        setCurrentBoardTheme(0);
        return;
    }
}

Theme ThemeManager::getCurrentTheme()
{
    return currentTheme;
}

void ThemeManager::loadInitialPieceTheme()
{
    // Read an environment variable. If one doesn't exst, default to "default"
    char* environmentPieceTheme = std::getenv(pieceThemePreferenceEnvVarName.c_str());
    if(environmentPieceTheme == nullptr)
    {
        themeManagerLogger->debug("No environment variable of name {} set. Using default theme of 'default'", pieceThemePreferenceEnvVarName);
        setCurrentPieceTheme("default");
        return;
    }

    themeManagerLogger->debug("Found an environment variable for setting piece theme. Setting it to {}", environmentPieceTheme);
    setCurrentPieceTheme(environmentPieceTheme);
}

void ThemeManager::setCurrentPieceTheme(std::string theme)
{
    // If a theme is empty, log an error
    if(theme.empty())
    {
        themeManagerLogger->error("Unable to set theme as its an empty string. Leaving it unchanged");
        return;
    }

    currentTheme.pieceTheme = theme;
}