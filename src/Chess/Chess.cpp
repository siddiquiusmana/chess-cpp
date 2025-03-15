#include "../include/Chess/Chess.h"
#include "ChessUtils.cpp"

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
        bool changeDetected = false;

        // Poll for events
        SDL_PollEvent(&event);

        // Keep the chess board updated
        if (changeDetected)
        {
            this->drawChessBoard();
            this->drawChessPiecesFromLatestPositions();

            changeDetected = !changeDetected;
        }

        switch(event.type)
        {
            // Break the loop and exit
            case SDL_QUIT:
                this->status = Status::SHUTDOWN_REQUESTED;
                break;
            case SDL_MOUSEBUTTONDOWN:
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Determine the row and col of the click
                int row = (mouseY - this->boardBorderPixels) / this->squareSize;
                int col = (mouseX - this->boardBorderPixels) / this->squareSize;
                this->chessLogger->debug("started dragging the mouse ({}, {})", row, col);

                // Grab the chess piece at that square
                std::shared_ptr<Chess::ChessPiece> chessPiece = this->positionToPieceMap.at({row, col});
                //this->pieceToLocationMap.insert(chessPiece, std::pair<int, int>(mouseX, mouseY));

                bool stoppedDragging = false;
                while(stoppedDragging != true)
                {
                    SDL_PollEvent(&event);
                    if(event.type == SDL_MOUSEBUTTONUP)
                    {
                        SDL_GetMouseState(&mouseX, &mouseY);
                        row = (mouseY - this->boardBorderPixels) / this->squareSize;
                        col = (mouseX - this->boardBorderPixels) / this->squareSize;
                        this->chessLogger->debug("Stopped dragging the mouse ({}, {})", row, col);
                        //this->pieceToLocationMap.insert(chessPiece, convertFromLocationToPosition(std::make_pair(mouseX, mouseY), this->boardBorderPixels, this->squareSize));
                        stoppedDragging = true;
                        break;
                    }
                }

                this->chessLogger->trace("Square Clicked: {}, {}", row, col);
                changeDetected = true;

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
            if(row == 1)
            {
                std::shared_ptr<Chess::Pawn> pawnToDraw = std::make_shared<Chess::Pawn>(row, col, true);
                this->positionToPieceMap.insert_or_assign(std::pair<int, int>(row, col), pawnToDraw);

                const std::pair<int, int> loc = convertFromPositionToLocation(std::pair<int, int>(row, col), this->boardBorderPixels, this->squareSize);
                this->pieceToLocationMap.insert_or_assign(pawnToDraw, loc);
            }

            if(row == 6)
            {
                std::shared_ptr<Chess::Pawn> pawnToDraw = std::make_shared<Chess::Pawn>(row, col, false);
                this->positionToPieceMap.insert_or_assign(std::pair<int, int>(row, col), pawnToDraw);

                const std::pair<int, int> loc = convertFromPositionToLocation(std::pair<int, int>(row, col), this->boardBorderPixels, this->squareSize);
                this->pieceToLocationMap.insert_or_assign(pawnToDraw, loc);
            }

            if(col == 0 || col == 7)
            {
                if(row == 0)
                {
                    std::shared_ptr<Chess::Rook> rookToDraw = std::make_shared<Chess::Rook>(row, col, true);
                    this->positionToPieceMap.insert_or_assign(std::pair<int, int>(row, col), rookToDraw);

                    const std::pair<int, int> loc = convertFromPositionToLocation(std::pair<int, int>(row, col), this->boardBorderPixels, this->squareSize);
                    this->pieceToLocationMap.insert_or_assign(rookToDraw, loc);
                }

                if(row == 7)
                {
                    std::shared_ptr<Chess::Rook> rookToDraw = std::make_shared<Chess::Rook>(row, col, false);
                    this->positionToPieceMap.insert_or_assign(std::pair<int, int>(row, col), rookToDraw);

                    const std::pair<int, int> loc = convertFromPositionToLocation(std::pair<int, int>(row, col), this->boardBorderPixels, this->squareSize);
                    this->pieceToLocationMap.insert_or_assign(rookToDraw, loc);
                }
            }

            if(col == 1 || col == 6)
            {
                if(row == 0)
                {
                    std::shared_ptr<Chess::Knight> knightToDraw = std::make_shared<Chess::Knight>(row, col, true);
                    this->positionToPieceMap.insert_or_assign(std::pair<int, int>(row, col), knightToDraw);

                    const std::pair<int, int> loc = convertFromPositionToLocation(std::pair<int, int>(row, col), this->boardBorderPixels, this->squareSize);
                    this->pieceToLocationMap.insert_or_assign(knightToDraw, loc);
                }

                if(row == 7)
                {
                    std::shared_ptr<Chess::Knight> knightToDraw = std::make_shared<Chess::Knight>(row, col, false);
                    this->positionToPieceMap.insert_or_assign(std::pair<int, int>(row, col), knightToDraw);

                    const std::pair<int, int> loc = convertFromPositionToLocation(std::pair<int, int>(row, col), this->boardBorderPixels, this->squareSize);
                    this->pieceToLocationMap.insert_or_assign(knightToDraw, loc);
                }
            }

            if(col == 2 || col == 5)
            {
                if(row == 0)
                {
                    std::shared_ptr<Chess::Bishop> bishopToDraw = std::make_shared<Chess::Bishop>(row, col, true);
                    this->positionToPieceMap.insert_or_assign(std::pair<int, int>(row, col), bishopToDraw);

                    const std::pair<int, int> loc = convertFromPositionToLocation(std::pair<int, int>(row, col), this->boardBorderPixels, this->squareSize);
                    this->pieceToLocationMap.insert_or_assign(bishopToDraw, loc);
                }

                if(row == 7)
                {
                    std::shared_ptr<Chess::Bishop> bishopToDraw = std::make_shared<Chess::Bishop>(row, col, false);
                    this->positionToPieceMap.insert_or_assign(std::pair<int, int>(row, col), bishopToDraw);

                    const std::pair<int, int> loc = convertFromPositionToLocation(std::pair<int, int>(row, col), this->boardBorderPixels, this->squareSize);
                    this->pieceToLocationMap.insert_or_assign(bishopToDraw, loc);
                }
            }

            if(col == 3)
            {
                if(row == 0)
                {
                    std::shared_ptr<Chess::Queen> queenToDraw = std::make_shared<Chess::Queen>(row, col, true);
                    this->positionToPieceMap.insert_or_assign(std::pair<int, int>(row, col), queenToDraw);

                    const std::pair<int, int> loc = convertFromPositionToLocation(std::pair<int, int>(row, col), this->boardBorderPixels, this->squareSize);
                    this->pieceToLocationMap.insert_or_assign(queenToDraw, loc);
                }

                if(row == 7)
                {
                    std::shared_ptr<Chess::Queen> queenToDraw = std::make_shared<Chess::Queen>(row, col, false);
                    this->positionToPieceMap.insert_or_assign(std::pair<int, int>(row, col), queenToDraw);

                    const std::pair<int, int> loc = convertFromPositionToLocation(std::pair<int, int>(row, col), this->boardBorderPixels, this->squareSize);
                    this->pieceToLocationMap.insert_or_assign(queenToDraw, loc);
                }
            }

            if(col == 4)
            {
                if(row == 0)
                {
                    std::shared_ptr<Chess::King> kingToDraw = std::make_shared<Chess::King>(row, col, true);
                    this->positionToPieceMap.insert_or_assign(std::pair<int, int>(row, col), kingToDraw);

                    const std::pair<int, int> loc = convertFromPositionToLocation(std::pair<int, int>(row, col), this->boardBorderPixels, this->squareSize);
                    this->pieceToLocationMap.insert_or_assign(kingToDraw, loc);
                }

                if(row == 7)
                {
                    std::shared_ptr<Chess::King> kingToDraw = std::make_shared<Chess::King>(row, col, false);
                    this->positionToPieceMap.insert_or_assign(std::pair<int, int>(row, col), kingToDraw);

                    const std::pair<int, int> loc = convertFromPositionToLocation(std::pair<int, int>(row, col), this->boardBorderPixels, this->squareSize);
                    this->pieceToLocationMap.insert_or_assign(kingToDraw, loc);
                }
            }
        }
    }

    this->drawChessPiecesFromLatestPositions();
    this->mainWindow->render();
}

void Chess::GameApplication::drawChessPiecesFromLatestPositions()
{
    this->chessLogger->debug("Drawing chess pieces from the location map");
    
    for(auto& keyValue: this->pieceToLocationMap)
    {
        std::shared_ptr<Chess::ChessPiece> piece = keyValue.first;
        std::pair<int, int> loc = keyValue.second;

        this->drawChessPiece(piece, piece->getRow(), piece->getCol(), piece->isWhitePiece());
    }
}

void Chess::GameApplication::drawPawn(std::shared_ptr<Chess::Pawn> piece, int row, int col, bool isWhite)
{
    SDL_Rect pawnPos;
    float scalingFactor = 0.75; // Need this to center the pawn so it doesn't take the whole square
    pawnPos.w = (int) squareSize * scalingFactor * 0.8;
    pawnPos.h = (int) squareSize * scalingFactor;
    pawnPos.x = boardBorderPixels + ((int) squareSize * col) + (squareSize * ((1 - (scalingFactor * 0.8)) / 2));
    pawnPos.y = boardBorderPixels + ((int) squareSize * row) + (squareSize * ((1 - scalingFactor) / 2));

    // Automatically gets the appropriate image to draw based on the themes set by the user
    std::string imageFilePath = this->themeManager->getCurrentChessPieceThemePath(isWhite) + "pawn.png";
    try
    {
        this->mainWindow->drawImage(&imageFilePath, &pawnPos);
    }
    catch(const char *e)
    {
        this->chessLogger->critical("Failed to draw a pawn at row: {} and col: {}\n\tException: {}\n\tCurrent Working Directory: {}", std::to_string(row), std::to_string(col), e, SDL_GetBasePath());
        exit(CHESS_INIT_FAILURE);
    }

    this->chessLogger->trace("Drawing a pawn at row: " + std::to_string(row) + " col: " + std::to_string(col));
}

void Chess::GameApplication::drawBishop(std::shared_ptr<Chess::Bishop> piece, int row, int col, bool isWhite)
{
    SDL_Rect bishopPos;
    float scalingFactor = 0.8; // Need this to center the bishop so it doesn't take the whole square
    bishopPos.w = bishopPos.h = (int) squareSize * scalingFactor;
    bishopPos.x = boardBorderPixels + ((int) squareSize * col) + (squareSize * ((1 - scalingFactor) / 2));
    bishopPos.y = boardBorderPixels + ((int) squareSize * row) + (squareSize * ((1 - scalingFactor) / 2));

    // Automatically gets the appropriate image to draw based on the themes set by the user
    std::string imageFilePath = this->themeManager->getCurrentChessPieceThemePath(isWhite) + "bishop.png";
    try
    {
        this->mainWindow->drawImage(&imageFilePath, &bishopPos);
    }
    catch(const char *e)
    {
        this->chessLogger->critical("Failed to draw a bishop at row: {} and col: {}\n\tException: {}", std::to_string(row), std::to_string(col), e);
        exit(CHESS_INIT_FAILURE);
    }

    this->chessLogger->trace("Drawing a bishop at row: " + std::to_string(row) + " col: " + std::to_string(col));
}

void Chess::GameApplication::drawKnight(std::shared_ptr<Chess::Knight> piece, int row, int col, bool isWhite)
{
    SDL_Rect knightPos;
    float scalingFactor = 0.8; // Need this to center the knight so it doesn't take the whole square
    knightPos.w = knightPos.h = (int) squareSize * scalingFactor;
    knightPos.x = boardBorderPixels + ((int) squareSize * col) + (squareSize * ((1 - scalingFactor) / 2));
    knightPos.y = boardBorderPixels + ((int) squareSize * row) + (squareSize * ((1 - scalingFactor) / 2));

    // Automatically gets the appropriate image to draw based on the themes set by the user
    std::string imageFilePath = this->themeManager->getCurrentChessPieceThemePath(isWhite) + "knight.png";
    try
    {
        this->mainWindow->drawImage(&imageFilePath, &knightPos);
    }
    catch(const char *e)
    {
        this->chessLogger->critical("Failed to draw a knight at row: {} and col: {}\n\tException: {}", std::to_string(row), std::to_string(col), e);
        exit(CHESS_INIT_FAILURE);
    }

    this->chessLogger->trace("Drawing a knight at row: " + std::to_string(row) + " col: " + std::to_string(col));
}

void Chess::GameApplication::drawRook(std::shared_ptr<Chess::Rook> piece, int row, int col, bool isWhite)
{
    SDL_Rect rookPos;
    float scalingFactor = 0.8; // Need this to center the rook so it doesn't take the whole square
    rookPos.w = rookPos.h = (int) squareSize * scalingFactor;
    rookPos.x = boardBorderPixels + ((int) squareSize * col) + (squareSize * ((1 - scalingFactor) / 2));
    rookPos.y = boardBorderPixels + ((int) squareSize * row) + (squareSize * ((1 - scalingFactor) / 2));

    // Automatically gets the appropriate image to draw based on the themes set by the user
    std::string imageFilePath = this->themeManager->getCurrentChessPieceThemePath(isWhite) + "rook.png";
    try
    {
        this->mainWindow->drawImage(&imageFilePath, &rookPos);
    }
    catch(const char *e)
    {
        this->chessLogger->critical("Failed to draw a rook at row: {} and col: {}\n\tException: {}", std::to_string(row), std::to_string(col), e);
        exit(CHESS_INIT_FAILURE);
    }

    this->chessLogger->trace("Drawing a rook at row: " + std::to_string(row) + " col: " + std::to_string(col));
}

void Chess::GameApplication::drawQueen(std::shared_ptr<Chess::Queen> piece, int row, int col, bool isWhite)
{
    SDL_Rect queenPos;
    float scalingFactor = 0.8; // Need this to center the bishop so it doesn't take the whole square
    queenPos.w = queenPos.h = (int) squareSize * scalingFactor;
    queenPos.x = boardBorderPixels + ((int) squareSize * col) + (squareSize * ((1 - scalingFactor) / 2));
    queenPos.y = boardBorderPixels + ((int) squareSize * row) + (squareSize * ((1 - scalingFactor) / 2));

    // Automatically gets the appropriate image to draw based on the themes set by the user
    std::string imageFilePath = this->themeManager->getCurrentChessPieceThemePath(isWhite) + "queen.png";
    try
    {
        this->mainWindow->drawImage(&imageFilePath, &queenPos);
    }
    catch(const char *e)
    {
        this->chessLogger->critical("Failed to draw a queen at row: {} and col: {}\n\tException: {}", std::to_string(row), std::to_string(col), e);
        exit(CHESS_INIT_FAILURE);
    }

    this->chessLogger->trace("Drawing a queen at row: " + std::to_string(row) + " col: " + std::to_string(col));
}

void Chess::GameApplication::drawKing(std::shared_ptr<Chess::King> piece, int row, int col, bool isWhite)
{
    SDL_Rect kingPos;
    float scalingFactor = 0.8; // Need this to center the bishop so it doesn't take the whole square
    kingPos.w = kingPos.h = (int) squareSize * scalingFactor;
    kingPos.x = boardBorderPixels + ((int) squareSize * col) + (squareSize * ((1 - scalingFactor) / 2));
    kingPos.y = boardBorderPixels + ((int) squareSize * row) + (squareSize * ((1 - scalingFactor) / 2));

    // Automatically gets the appropriate image to draw based on the themes set by the user
    std::string imageFilePath = this->themeManager->getCurrentChessPieceThemePath(isWhite) + "king.png";
    try
    {
        this->mainWindow->drawImage(&imageFilePath, &kingPos);
    }
    catch(const char *e)
    {
        this->chessLogger->critical("Failed to draw a king at row: {} and col: {}\n\tException: {}", std::to_string(row), std::to_string(col), e);
        exit(CHESS_INIT_FAILURE);
    }

    this->chessLogger->trace("Drawing a king at row: " + std::to_string(row) + " col: " + std::to_string(col));
}

void Chess::GameApplication::drawChessPiece(std::shared_ptr<Chess::ChessPiece> piece, int row, int col, bool isWhite)
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
            std::shared_ptr<Chess::Pawn> pawn = std::dynamic_pointer_cast<Chess::Pawn>(piece);
            if(pawn)
            {
                this->drawPawn(pawn, row, col, isWhite);
            }
            else
            {
                throw "Unable to draw the requested pawn at row: " + std::to_string(row) + " col: " + std::to_string(col);
            }
            break;
        }
        case Type::BISHOP:
        {
            std::shared_ptr<Chess::Bishop> bishop = std::dynamic_pointer_cast<Chess::Bishop>(piece);
            if(bishop)
            {
                this->drawBishop(bishop, row, col, isWhite);
            }
            else
            {
                throw "Unable to draw the requested bishop at row: " + std::to_string(row) + " col: " + std::to_string(col);
            }
            break;
        }
        case Type::KNIGHT:
        {
            std::shared_ptr<Chess::Knight> knight = std::dynamic_pointer_cast<Chess::Knight>(piece);
            if(knight)
            {
                this->drawKnight(knight, row, col, isWhite);
            }
            else
            {
                throw "Unable to draw the requested knight at row: " + std::to_string(row) + " col: " + std::to_string(col);
            }
            break;
        }
        case Type::QUEEN:
        {
            std::shared_ptr<Chess::Queen> queen = std::dynamic_pointer_cast<Chess::Queen>(piece);
            if(queen)
            {
                this->drawQueen(queen, row, col, isWhite);
            }
            else
            {
                throw "Unable to draw the requested queen at row: " + std::to_string(row) + " col: " + std::to_string(col);
            }
            break;
        }
        case Type::KING:
        {
            std::shared_ptr<Chess::King> king = std::dynamic_pointer_cast<Chess::King>(piece);
            if(king)
            {
                this->drawKing(king, row, col, isWhite);
            }
            else
            {
                throw "Unable to draw the requested king at row: " + std::to_string(row) + " col: " + std::to_string(col);
            }
            break;
        }
        case Type::ROOK:
        {
            std::shared_ptr<Chess::Rook> rook = std::dynamic_pointer_cast<Chess::Rook>(piece);
            if(rook)
            {
                this->drawRook(rook, row, col, isWhite);
            }
            else
            {
                throw "Unable to draw the requested rook at row: " + std::to_string(row) + " col: " + std::to_string(col);
            }
            break;
        }
        default:
            break;
    }


    this->pieceToPositionMap[piece] = {row, col};
    this->positionToPieceMap[{row, col}] = piece;
}