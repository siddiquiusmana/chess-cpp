#include "../include/Chess/Chess.h"

Chess::GameApplication::GameApplication(std::shared_ptr<LogManager> lm_ptr)
{
    lm = lm_ptr;
    chessLogger = lm->getLogger("Chess");
    chessLogger->debug("Initializing Chess...");

    // Initialize the theme manager
    themeManager = std::make_shared<ThemeManager>(lm_ptr);

    // Display the banner
    displayBanner();

    // Create a window
    mainWindow = std::make_shared<SDLWindow>("Chess", lm);
    mainWindow->createWindow();

    // Board border value initializations
    boardBorder = 10;
    boardBorderPixels = (std::min(mainWindow->getWindowHeight(), mainWindow->getWindowWidth()) * (boardBorder / 100.0)) / 2;
    chessLogger->trace("boardBorderPixels: {}", boardBorderPixels);

    // Compute the size of each of the 8x8 squares to help draw the grid
    // Leaving a margin of 10% on all sides
    squareSize = (mainWindow->getWindowHeight() <= mainWindow->getWindowWidth() ? // find the smalller of the two dimensions
                    mainWindow->getWindowHeight() / 8.0 : // divide by 8 (number of squares)
                    mainWindow->getWindowWidth() / 8.0) * 
                    ((100.0 - boardBorder) / 100.0); // Take away the border dimensions
    chessLogger->trace("squareSize: {}", squareSize);

    // Initialize the chess board
    initializeChessBoard();

    // Initialize the pieces
    initializeChessPieces();

    status = INITIALIZED;
    chessLogger->info("Board Initialized.");
}

Chess::GameApplication::~GameApplication()
{
    chessLogger->debug("Cleaning up Chess...");

    mainWindow = nullptr;

    chessLogger->debug("Cleaned up Chess...");
}

void Chess::GameApplication::run()
{
    status = RUNNING;

    // Main loop for the application
    SDL_Event event;
    while(status != SHUTDOWN_REQUESTED)
    {
        // Poll for events
        SDL_PollEvent(&event);

        switch(event.type)
        {
            // Break the loop and exit
            case SDL_QUIT:
                status = SHUTDOWN_REQUESTED;
                break;
        }
    }
}

void Chess::GameApplication::displayBanner()
{
    chessLogger->info("*************************************************");
    chessLogger->info("**************  Chess Application  **************");
    chessLogger->info("*************************************************");
}

void Chess::GameApplication::initializeChessBoard()
{
    // Create a blank background// Create a blank background
    try
    {
        mainWindow->renderBackground({255, 255, 255, 255});
    }
    catch(const char* e)
    {
        chessLogger->critical("Unable to set the background color of the window: {}", e);
        exit(CHESS_INIT_FAILURE);
    }

    // Initial board square
    int mainBoardSize = (int) squareSize * 8;
    SDL_Rect mainBoardRect;
    mainBoardRect.h = mainBoardRect.w = mainBoardSize;
    mainBoardRect.x = boardBorderPixels;
    mainBoardRect.y = boardBorderPixels;
    mainWindow->drawRect(&mainBoardRect, {0,0,0,0});

    // Variable to track dark and light squares
    bool isDarkSquare = true;
    bool doesRowStartDark = true;
    SDL_Color darkSquare = themeManager->getCurrentTheme().darkSqaureColor;
    SDL_Color lightSquare = themeManager->getCurrentTheme().lightSquareColor;

    // Draw the rest of the board squares
    for(int row=0; row<8; row++)
    {
        isDarkSquare = doesRowStartDark;

        for(int col=0; col<8; col++)
        {
            SDL_Rect square;
            square.w = square.h = (int) squareSize;
            square.x = boardBorderPixels + ((int) squareSize * col);
            square.y = boardBorderPixels + ((int) squareSize * row);

            // Set the right color for the square
            SDL_Color squareColor = isDarkSquare ? darkSquare : lightSquare;
            try
            {
                mainWindow->drawFilledRect(&square, squareColor);
            }
            catch(const char* error)
            {
                chessLogger->critical("Failed to initialize chess board. {}", error);
                exit(CHESS_INIT_FAILURE);
            }

            // flip the isDarkSquare var so we can alternate between dark and light squares
            isDarkSquare = !isDarkSquare;
        }

        doesRowStartDark = !doesRowStartDark;
    }
        
    mainWindow->render();
}

void Chess::GameApplication::initializeChessPieces()
{
    // Assumption: The board has already been initialized
    // Create pawns on each square on the first row
    for(int col=0; col<8; col++)
    {
        
    }
}