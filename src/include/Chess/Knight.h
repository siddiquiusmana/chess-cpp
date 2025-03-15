#pragma once

#include "ChessPiece.h"


namespace Chess
{
    /**
     * Knight extends the ChessPiece abstract class. 
     */
    class Knight : public ChessPiece
    {
        public:
            // Constructor for Knight.
            Knight(const int initRow, const int initCol, const bool initIsWhite);

            // Destructor for Knight.
            ~Knight();

            // 
            void move(int newRow, int newCol) override;

            bool isValidMove(std::pair<int, int> newPos) override;

            std::vector<std::pair<int, int>> getValidMoves() override;

            std::vector<std::pair<int, int>> getCoverage() override;
    };
};