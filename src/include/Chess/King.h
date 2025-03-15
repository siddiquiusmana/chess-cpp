#pragma once

#include "ChessPiece.h"


namespace Chess
{
    /**
     * King extends the ChessPiece abstract class. 
     */
    class King : public ChessPiece
    {
        public:
            // Constructor for King.
            King(const int initRow, const int initCol, const bool initIsWhite);

            // Destructor for King.
            ~King();

            // 
            void move(int newRow, int newCol) override;

            bool isValidMove(std::pair<int, int> newPos) override;

            std::vector<std::pair<int, int>> getValidMoves() override;

            std::vector<std::pair<int, int>> getCoverage() override;
    };
};