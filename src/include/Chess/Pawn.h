#pragma once

#include "Chess.h"

namespace Chess
{
    /**
     * Pawn extends the ChessPiece abstract class. 
     */
    class Pawn : ChessPiece
    {
        public:
            // Constructor for Pawn.
            Pawn(const int& row, const int& col, const bool& color, GameApplication& gameApp);

            // Destructor for Pawn.
            ~Pawn();
    };
};