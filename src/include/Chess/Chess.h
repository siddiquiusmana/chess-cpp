#pragma once

#include <format>
#include <map>

#include "../Logger/LogManager.h"
#include "../SDL/SDLWindow.h"
#include "../Themes/ThemeManager.h"
#include "Bishop.h"
#include "ChessPiece.h"
#include "ChessUtils.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

namespace Chess 
{

    /**
     * Different statuses for the chess application
     */
    enum class Status
    {
        INITIALIZED,
        RUNNING,
        SHUTDOWN_REQUESTED
    };

    /**
     * The error codes associates with this class. Every error code will start with 243 (Che)
     */
    enum ErrorCodes
    {
        CHESS_INIT_FAILURE = 24301,
    };

    /**
     * The Chess Application class
     */
    class GameApplication
    {
        public:
            // Constructor that initializes the app
            // Still need to invoke the run method to actually execute.
            GameApplication(std::shared_ptr<LogManager> lm_ptr);

            // Destructor. Performs clean up
            ~GameApplication();

            // Method that starts the application
            void run();

            // Draws a chess piece at a certain row and column on the board.
            // The row and col are 0 based, meaning that the top left corner is (0,0)
            void drawChessPiece(std::shared_ptr<Chess::ChessPiece> piece, int row, int col, bool isWhite);

        private:
            // Log manager
            std::shared_ptr<LogManager> lm;

            // The main window for the application
            std::shared_ptr<SDLWindow> mainWindow;

            // The class logger
            std::shared_ptr<spdlog::logger> chessLogger;

            // The theme manager
            std::shared_ptr<ThemeManager> themeManager;

            // Map of all the pieces and their current chess position on the board
            std::map<std::shared_ptr<Chess::ChessPiece>, std::pair<int, int>> pieceToPositionMap;

            // Map of all the pieces and their current physical location on the baord
            std::map<std::shared_ptr<Chess::ChessPiece>, std::pair<int, int>> pieceToLocationMap;

            // Map of current location to the chess piece that's on that square
            std::map<std::pair<int, int>, std::shared_ptr<ChessPiece>> positionToPieceMap;

            // Status of the chess application
            Status status;

            // The width of the border/empty space around the board
            // expressed as a percentage
            int boardBorder;

            // The actual pixel conversion of the boardBorder
            float boardBorderPixels;

            // The size of each of the 8x8 squares on the board
            float squareSize;

            // A counter that counts the legal moves.
            int moveCounter;

            // Track whether this turn is for white pieces or black
            bool isWhiteTurn;

            // Displays the app banner
            void displayBanner();

            // Initializes the chess board by drawing it onto the window
            void drawChessBoard();

            // Initializes and places chess pieces in their appropriate places
            void initializeChessPieces();

            // Draws chess pieces from their positions
            void drawChessPiecesFromLatestPositions();

            // Draws board from where the pieces are on the board.
            void drawBoardFromLastPosition();

            // Draws a Pawn at a certain row and column on the board
            void drawPawn(std::shared_ptr<Chess::Pawn> piece, int row, int col, bool isWhite);

            // Draws a Bishop at a certain row and column on the board
            void drawBishop(std::shared_ptr<Chess::Bishop> piece, int row, int col, bool isWhite);
            
            // Draws a King at a certain row and column on the board
            void drawKing(std::shared_ptr<Chess::King> piece, int row, int col, bool isWhite);

            // Draws a Knight at a certain row and column on the board
            void drawKnight(std::shared_ptr<Chess::Knight> piece, int row, int col, bool isWhite);

            // Draws a Queen at a certain row and column on the board
            void drawQueen(std::shared_ptr<Chess::Queen> piece, int row, int col, bool isWhite);

            // Draws a Rook at a certain row and column on the board
            void drawRook(std::shared_ptr<Chess::Rook> piece, int row, int col, bool isWhite);
    };
};