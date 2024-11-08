#include "../include/Themes/ThemeManager.h"

ThemeManager::ThemeManager(std::shared_ptr<LogManager> lm)
{
    // Initialize the logger
    themeManagerLogger = lm->getLogger("ThemeManager");

    // Initialize the themes
    ThemeManager::intializeAvailableThemes();
}

void ThemeManager::intializeAvailableThemes()
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

    currentAvailableThemes.push_back(standardBlackAndWhiteTheme);
    currentAvailableThemes.push_back(chessDotComTheme);
    currentAvailableThemes.push_back(oldSchoolGreenAndWhiteTheme);
    currentAvailableThemes.push_back(brownAndWhiteTheme);

    // TODO read in more themes somehow

    themeManagerLogger->trace("Added the following themes: ");
    int i=0;
    for(auto theme: currentAvailableThemes)
    {
        themeManagerLogger->trace("Theme {}\n \
                                   \t\t\tDark Piece Color: r{}g{}b{}a{}\n \
                                   \t\t\tLight Piece Color: r{}g{}b{}a{}\n \
                                   \t\t\tDark Square Color: r{}g{}b{}a{}\n \
                                   \t\t\tLight Square Color: r{}g{}b{}a{}", 
                                   i,
                                   theme.darkPieceColor.r, theme.darkPieceColor.g, theme.darkPieceColor.b, theme.darkPieceColor.a,
                                   theme.lightPieceColor.r, theme.lightPieceColor.g, theme.lightPieceColor.b, theme.lightPieceColor.a,
                                   theme.darkSqaureColor.r, theme.darkSqaureColor.g, theme.darkSqaureColor.b, theme.darkSqaureColor.a,
                                   theme.lightSquareColor.r, theme.lightSquareColor.g, theme.lightSquareColor.b, theme.lightSquareColor.a);

        i++;
    }

    // Either read the user preference or set default.
    loadInitialTheme();
}

void ThemeManager::setCurrentTheme(int theme)
{
    // Check whether its a valid theme to be set
    if(theme < 0 || theme >= currentAvailableThemes.size())
    {
        themeManagerLogger->error("Requesting to set an invalid theme {}, defaulting to 0", theme);
        currentTheme = currentAvailableThemes.at(0);
        return;
    }
    
    // Set the theme
    currentTheme = currentAvailableThemes.at(theme);
}

void ThemeManager::loadInitialTheme()
{
    // Read an environment variable. If one doesn't exst, default to 0
    char* environmentSetTheme = std::getenv(environmentVarName.c_str());
    if(environmentSetTheme == nullptr)
    {
        themeManagerLogger->debug("No environment variable of name {} set. Using default theme of 0", environmentVarName);
        setCurrentTheme(0);
        return;
    }

    // Otherwise try to set the user preference
    try
    {
        int theme = std::stoi(environmentSetTheme);
        themeManagerLogger->debug("Found an environment variable for setting theme. Setting it to {}", theme);
        setCurrentTheme(theme);
    }
    catch(std::invalid_argument &e)
    {
        themeManagerLogger->error("Error converting the theme from environment variables. Not a valid theme. Setting the theme to the default of 0.");
        setCurrentTheme(0);
        return;
    }
    catch(std::out_of_range &e)
    {
        themeManagerLogger->error("Error converting the theme from environment variables. Integer out of range. Setting the theme to the default of 0.");
        setCurrentTheme(0);
        return;
    }
}

Theme ThemeManager::getCurrentTheme()
{
    return currentTheme;
}