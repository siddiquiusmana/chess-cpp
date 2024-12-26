#pragma once

#include "ChessPiece.h"


namespace Chess
{
    /**
     * Pawn extends the ChessPiece abstract class. 
     */
    class Pawn : public ChessPiece
    {
        public:
            // Constructor for Pawn.
            Pawn(const int initRow, const int initCol, const bool initIsWhite);

            // Destructor for Pawn.
            ~Pawn();

            // 
            void move(int newRow, int newCol) override;

            bool isValidMove(std::pair<int, int> newPos) override;

            std::vector<std::pair<int, int>> getValidMoves() override;

            std::vector<std::pair<int, int>> getCoverage() override;
    };
};