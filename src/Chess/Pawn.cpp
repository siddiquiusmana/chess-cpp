#include "../include/Chess/Pawn.h"

Chess::Pawn::Pawn(const int initRow, const int initCol, const bool initIsWhite)
{
    // Initiating the base class
    row = initRow;
    col = initCol;
    isWhite = initIsWhite;
    isCaptured = false;
    type = Type::PAWN;
}

Chess::Pawn::~Pawn()
{
    
}

void Chess::Pawn::move(int newRow, int newCol)
{

}

bool Chess::Pawn::isValidMove(std::pair<int, int> newPos)
{

    return false;   
}

std::vector<std::pair<int, int>> Chess::Pawn::getValidMoves()
{
    return {};
}

std::vector<std::pair<int, int>> Chess::Pawn::getCoverage()
{
    return {};
}
