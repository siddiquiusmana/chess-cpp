#include "include/Chess.h"

Chess::Chess(std::shared_ptr<LogManager> lm_ptr)
{
    lm = lm_ptr;
    chessLogger = lm->getLogger("Chess");
    chessLogger->debug("Initializing Chess...");

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
        status = INITIALIZED;
    chessLogger->info("Board Initialized.");
}

Chess::~Chess()
{
    chessLogger->debug("Cleaning up Chess...");

    mainWindow = nullptr;

    chessLogger->debug("Cleaned up Chess...");
}

void Chess::run()
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

/**
 * displayBanner implementation
 */
void Chess::displayBanner()
{
    chessLogger->info("*************************************************");
    chessLogger->info("**************  Chess Application  **************");
    chessLogger->info("*************************************************");
}

void Chess::initializeChessBoard()
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

    // Create vertical lines
    for(int i=0; i<=8; i++)
    {
        // Vertical lines to draw
        Geometry::Line vertical_line = {
            {   // start
                (int)boardBorderPixels + (i * (int)squareSize),             // x 
                (int)boardBorderPixels                                      // y
            },
            {   // end
                (int)boardBorderPixels + (i * (int)squareSize),             // x
                mainWindow->getWindowHeight() - (int)boardBorderPixels      // y
            }
        };

        // horizontal lines to draw
        Geometry::Line horizontal_line = {
            {   // start
                (int) boardBorderPixels,                                    // x
                (int) boardBorderPixels + ((i * (int)squareSize))           // y
            },
            {   // end
                mainWindow->getWindowWidth() - (int) boardBorderPixels,     // x
                (int) boardBorderPixels + ((i * (int)squareSize))           // y
            }
        };

        // Draw the lines
        try
        {
            mainWindow->drawLine(horizontal_line.start, horizontal_line.end, {0,0,0,0});
            mainWindow->drawLine(vertical_line.start, vertical_line.end, {0,0,0,0});
        }
        catch(const char* error)
        {
            chessLogger->critical("Unable to draw grid: {}", error);
            exit(CHESS_INIT_FAILURE);
        }
    }
        
    mainWindow->render();
}