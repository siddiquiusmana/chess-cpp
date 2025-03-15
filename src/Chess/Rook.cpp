#include "../include/Chess/Rook.h"

Chess::Rook::Rook(const int initRow, const int initCol, const bool initIsWhite)
{
    // Initiating the base class
    row = initRow;
    col = initCol;
    isWhite = initIsWhite;
    isCaptured = false;
    type = Type::ROOK;
}

Chess::Rook::~Rook()
{
    
}

void Chess::Rook::move(int newRow, int newCol)
{

}

bool Chess::Rook::isValidMove(std::pair<int, int> newPos)
{

    return false;   
}

std::vector<std::pair<int, int>> Chess::Rook::getValidMoves()
{
    return {};
}

std::vector<std::pair<int, int>> Chess::Rook::getCoverage()
{
    return {};
}
