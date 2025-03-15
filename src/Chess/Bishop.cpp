#include "../include/Chess/Bishop.h"

Chess::Bishop::Bishop(const int initRow, const int initCol, const bool initIsWhite)
{
    // Initiating the base class
    row = initRow;
    col = initCol;
    isWhite = initIsWhite;
    isCaptured = false;
    type = Type::BISHOP;
}

Chess::Bishop::~Bishop()
{
    
}

void Chess::Bishop::move(int newRow, int newCol)
{

}

bool Chess::Bishop::isValidMove(std::pair<int, int> newPos)
{

    return false;   
}

std::vector<std::pair<int, int>> Chess::Bishop::getValidMoves()
{
    return {};
}

std::vector<std::pair<int, int>> Chess::Bishop::getCoverage()
{
    return {};
}
