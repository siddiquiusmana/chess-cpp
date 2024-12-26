#include "../include/Chess/Chess.h"

Chess::GameApplication::GameApplication(std::shared_ptr<LogManager> lm_ptr)
{
    this->lm = lm_ptr;
    this->chessLogger = lm->getLogger("Chess");
    this->chessLogger->debug("Initializing Chess...");

    // Initialize the theme manager
    this->themeManager = std::make_shared<ThemeManager>(lm_ptr);

    // Display the banner
    displayBanner();

    // Create a window
    this->mainWindow = std::make_shared<SDLWindow>("Chess", lm);
    this->mainWindow->createWindow();

    // Board border value initializations
    this->boardBorder = 10;
    this->boardBorderPixels = (std::min(mainWindow->getWindowHeight(), mainWindow->getWindowWidth()) * (boardBorder / 100.0)) / 2;
    this->chessLogger->trace("boardBorderPixels: {}", boardBorderPixels);

    // Compute the size of each of the 8x8 squares to help draw the grid
    // Leaving a margin of 10% on all sides
    this->squareSize = (mainWindow->getWindowHeight() <= mainWindow->getWindowWidth() ? // find the smalller of the two dimensions
                    mainWindow->getWindowHeight() / 8.0 : // divide by 8 (number of squares)
                    mainWindow->getWindowWidth() / 8.0) * 
                    ((100.0 - boardBorder) / 100.0); // Take away the border dimensions
    this->chessLogger->trace("squareSize: {}", squareSize);

    // Initialize the chess board
    drawChessBoard();

    // Initialize the pieces
    initializeChessPieces();

    this->status = Status::INITIALIZED;
    this->chessLogger->info("Board Initialized.");
}

Chess::GameApplication::~GameApplication()
{
    this->chessLogger->debug("Cleaning up Chess...");

    this->mainWindow = nullptr;

    this->chessLogger->debug("Cleaned up Chess...");
}

void Chess::GameApplication::run()
{
    this->status = Status::RUNNING;

    // Main loop for the application
    SDL_Event event;
    while(this->status != Status::SHUTDOWN_REQUESTED)
    {
        // Poll for events
        SDL_PollEvent(&event);

        switch(event.type)
        {
            // Break the loop and exit
            case SDL_QUIT:
                this->status = Status::SHUTDOWN_REQUESTED;
                break;
        }
    }

    this->chessLogger->info("Shutdown normally.");
}

void Chess::GameApplication::displayBanner()
{
    this->chessLogger->info("*************************************************");
    this->chessLogger->info("**************  Chess Application  **************");
    this->chessLogger->info("*************************************************");
}

void Chess::GameApplication::drawChessBoard()
{
    // Create a blank background// Create a blank background
    try
    {
        this->mainWindow->renderBackground({255, 255, 255, 255});
    }
    catch(const char* e)
    {
        this->chessLogger->critical("Unable to set the background color of the window: {}", e);
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
                this->mainWindow->drawFilledRect(&square, squareColor);
            }
            catch(const char* error)
            {
                this->chessLogger->critical("Failed to initialize chess board. {}", error);
                exit(CHESS_INIT_FAILURE);
            }

            // flip the isDarkSquare var so we can alternate between dark and light squares
            isDarkSquare = !isDarkSquare;
        }

        doesRowStartDark = !doesRowStartDark;
    }
        
    this->mainWindow->render();
}

void Chess::GameApplication::initializeChessPieces()
{
    // Assumption: The board has already been initialized
    // Create pawns on each square on the first row
    for(int col=0; col<8; col++)
    {
        for(int row=0; row<8; row++)
        {
            if(row == 0)
            {
                std::shared_ptr<Chess::Pawn> pawnToDraw = std::make_shared<Chess::Pawn>(row, col, true);
                this->drawChessPiece(pawnToDraw, row, col);
            }

            if(row == 7)
            {
                std::shared_ptr<Chess::Pawn> pawnToDraw = std::make_shared<Chess::Pawn>(row, col, false);
                this->drawChessPiece(pawnToDraw, row, col);
            }
        }
    }
}

void Chess::GameApplication::drawPawn(std::shared_ptr<Chess::Pawn> piece, int row, int col)
{
    this->chessLogger->debug("Drawing a pawn at row: " + std::to_string(row) + " col: " + std::to_string(col));
}

void Chess::GameApplication::drawChessPiece(std::shared_ptr<Chess::ChessPiece> piece, int row, int col)
{
    if(row >= 8 || col >= 8 || row < 0 || col < 0)
    {
        throw "Invalid row or column provided.  Row: " + std::to_string(row) + ", Col: " + std::to_string(col);
        return;
    }

    switch (piece->getType())
    {
        case Type::PAWN:
        {
            auto pawn = std::dynamic_pointer_cast<Chess::Pawn>(piece);
            if(pawn)
            {
                this->drawPawn(pawn, row, col);
            }
            else
            {
                //throw std::format("Unable to draw the requested pawn at row: {}, col: {}", row, col);
            }
            break;
        }
        default:
            break;
    }
}