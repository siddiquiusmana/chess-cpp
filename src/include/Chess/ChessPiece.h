#pragma once

#include <vector>

namespace Chess
{
    /**
     * The tpe of chess pieces
     */
    enum class Type
    {
        PAWN,
        KNIGHT,
        BISHOP,
        ROOK,
        QUEEN,
        KING
    };

    /** 
     * Each Chess piece will have common methods so this is an abstract class
     * that defines the interface for each chess piece.
     */
    class ChessPiece
    {
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
        
        protected:

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

            // Move history for this piece. A list of positions and the position of the piece it took. NULL means the move 
            // didn't take a piece
            std::vector<MoveLog> moveHistory;

        public:

            // Virtual destructor to allow for implementation of child classes
            virtual ~ChessPiece() = default;

            // Functionality to move the chess piece to a new location
            virtual void move(int newRow, int newCol) = 0;

            // Functionality to see whether a new move is legal for this chess piece.
            virtual bool isValidMove(std::pair<int, int> newPos) = 0;

            // Functionality to see all valid moves for this chess piece. This is an abstract method that will be 
            // implemented by each chess piece class.
            virtual std::vector<std::pair<int, int>> getValidMoves() = 0;

            // Functionality to see the coverage of open spaces for this chess piece. This is an abstract method that
            // will be implemented by each chess piece class.
            virtual std::vector<std::pair<int, int>> getCoverage() = 0;

            // Getter for the row of the chess piece. Returns -1 if it is not on the board
            int getRow();

            // Getter for the column of the chess piece. Returns -1 if it is not on the board
            int getCol();

            // Getter for the type of this chess piece
            Type getType();

            // Getter for whether or not this chess piece is white
            bool isWhitePiece();

            std::vector<MoveLog> getMoveHistory();
    };
};