#pragma once

#include "../Logger/LogManager.h"
#include "../SDL/SDLWindow.h"
#include "../Themes/ThemeManager.h"

namespace Chess 
{

    /**
     * Different statuses for the chess application
     */
    enum Status
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

        private:
            // Log manager
            std::shared_ptr<LogManager> lm;

            // The main window for the application
            std::shared_ptr<SDLWindow> mainWindow;

            // The class logger
            std::shared_ptr<spdlog::logger> chessLogger;

            // The theme manager
            std::shared_ptr<ThemeManager> themeManager;

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
            void initializeChessBoard();

            // Initializes and places chess pieces in their appropriate places
            void initializeChessPieces(); 
    };

    /** 
     * Each Chess piece will have common methods so this is an abstract class
     * that defines the interface for each chess piece.
     */
    class ChessPiece
    {
        /**
         * The tpe of chess pieces
         */
        enum Type
        {
            PAWN,
            KNIGHT,
            BISHOP,
            ROOK,
            QUEEN,
            KING
        };

        /**
         * This struct defines a single log of a chess move. Where the piece moved from
         * and where to, as well as whether it was a capture.
         */
        struct MoveLog
        {
            std::pair<int, int> from;
            std::pair<int, int> to;
            bool isCapture;
        };
        
        private:
            // The color of the chess piece. True means white, false means black
            bool isWhite;

            // The type of chess piece that this is.
            Type type;

            // The row on which this chess piece is located
            int row;

            // The column on which this chess piece is located
            int col;

            // Whether the piece has been captured or not
            bool isCaptured;

            // This will be used to track legal moves for each chess piece
            std::vector<std::pair<int, int>> legalMoves;

            // The game application that this chess piece belongs to
            std::shared_ptr<GameApplication> gameAppPtr;

        public:
            // Move history for this piece. A list of positions and the position of the piece it took. NULL means the move 
            // didn't take a piece
            std::vector<MoveLog> moveHistory;

            // Functionality to move the chess piece to a new location
            virtual void move(int newRow, int newCol);

            // Functionality to see whether a new move is legal for this chess piece.
            virtual bool isValidMove(std::pair<int, int> newPos);

            // Functionality to see all valid moves for this chess piece. This is an abstract method that will be 
            // implemented by each chess piece class.
            virtual std::vector<std::pair<int, int>> getValidMoves();

            // Functionality to see the coverage of open spaces for this chess piece. This is an abstract method that
            // will be implemented by each chess piece class.
            virtual std::vector<std::pair<int, int>> getCoverage();
            // Getter for the row of the chess piece. Returns -1 if it is not on the board
            int getRow();

            // Getter for the column of the chess piece. Returns -1 if it is not on the board
            int getCol();

            // Getter for the type of this chess piece
            Type getType();

            // Getter for whether or not this chess piece is white
            bool isWhitePiece();
    };
};