#include "../include/Chess/Knight.h"

Chess::Knight::Knight(const int initRow, const int initCol, const bool initIsWhite)
{
    // Initiating the base class
    row = initRow;
    col = initCol;
    isWhite = initIsWhite;
    isCaptured = false;
    type = Type::KNIGHT;
}

Chess::Knight::~Knight()
{
    
}

void Chess::Knight::move(int newRow, int newCol)
{

}

bool Chess::Knight::isValidMove(std::pair<int, int> newPos)
{

    return false;   
}

std::vector<std::pair<int, int>> Chess::Knight::getValidMoves()
{
    return {};
}

std::vector<std::pair<int, int>> Chess::Knight::getCoverage()
{
    return {};
}
