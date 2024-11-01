#pragma once

#include "Logger/LogManager.h"
#include "SDL/SDLWindow.h"

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
class Chess
{
    public:
        // Constructor that initializes the app
        // Still need to invoke the run method to actually execute.
        Chess(std::shared_ptr<LogManager> lm_ptr);

        // Destructor. Performs clean up
        ~Chess();

        // Method that starts the application
        void run();

    private:
        // Log manager
        std::shared_ptr<LogManager> lm;

        // The main window for the application
        std::shared_ptr<SDLWindow> mainWindow;

        // The class logger
        std::shared_ptr<spdlog::logger> chessLogger;

        // Status of the chess application
        Status status;

        // The width of the border/empty space around the board
        // expressed as a percentage
        int boardBorder;

        // The actual pixel conversion of the boardBorder
        float boardBorderPixels;

        // The size of each of the 8x8 squares on the board
        float squareSize;

        // Displays the app banner
        void displayBanner();

        // Initializes the chess board by drawing it onto the window
        void initializeChessBoard();
};