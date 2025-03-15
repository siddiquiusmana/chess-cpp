#pragma once

#include "ChessPiece.h"


namespace Chess
{
    /**
     * Rook extends the ChessPiece abstract class. 
     */
    class Rook : public ChessPiece
    {
        public:
            // Constructor for Rook.
            Rook(const int initRow, const int initCol, const bool initIsWhite);

            // Destructor for Rook.
            ~Rook();

            // 
            void move(int newRow, int newCol) override;

            bool isValidMove(std::pair<int, int> newPos) override;

            std::vector<std::pair<int, int>> getValidMoves() override;

            std::vector<std::pair<int, int>> getCoverage() override;
    };
};