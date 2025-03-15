#pragma once

#include "ChessPiece.h"


namespace Chess
{
    /**
     * Queen extends the ChessPiece abstract class. 
     */
    class Queen : public ChessPiece
    {
        public:
            // Constructor for Queen.
            Queen(const int initRow, const int initCol, const bool initIsWhite);

            // Destructor for Queen.
            ~Queen();

            // 
            void move(int newRow, int newCol) override;

            bool isValidMove(std::pair<int, int> newPos) override;

            std::vector<std::pair<int, int>> getValidMoves() override;

            std::vector<std::pair<int, int>> getCoverage() override;
    };
};