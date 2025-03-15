#include "../include/Chess/Queen.h"

Chess::Queen::Queen(const int initRow, const int initCol, const bool initIsWhite)
{
    // Initiating the base class
    row = initRow;
    col = initCol;
    isWhite = initIsWhite;
    isCaptured = false;
    type = Type::QUEEN;
}

Chess::Queen::~Queen()
{
    
}

void Chess::Queen::move(int newRow, int newCol)
{

}

bool Chess::Queen::isValidMove(std::pair<int, int> newPos)
{

    return false;   
}

std::vector<std::pair<int, int>> Chess::Queen::getValidMoves()
{
    return {};
}

std::vector<std::pair<int, int>> Chess::Queen::getCoverage()
{
    return {};
}
