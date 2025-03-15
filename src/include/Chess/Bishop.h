#pragma once

#include "ChessPiece.h"


namespace Chess
{
    /**
     * Bishop extends the ChessPiece abstract class. 
     */
    class Bishop : public ChessPiece
    {
        public:
            // Constructor for Bishop.
            Bishop(const int initRow, const int initCol, const bool initIsWhite);

            // Destructor for Bishop.
            ~Bishop();

            // 
            void move(int newRow, int newCol) override;

            bool isValidMove(std::pair<int, int> newPos) override;

            std::vector<std::pair<int, int>> getValidMoves() override;

            std::vector<std::pair<int, int>> getCoverage() override;
    };
};