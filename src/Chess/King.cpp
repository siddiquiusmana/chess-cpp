#include "../include/Chess/King.h"

Chess::King::King(const int initRow, const int initCol, const bool initIsWhite)
{
    // Initiating the base class
    row = initRow;
    col = initCol;
    isWhite = initIsWhite;
    isCaptured = false;
    type = Type::KING;
}

Chess::King::~King()
{
    
}

void Chess::King::move(int newRow, int newCol)
{

}

bool Chess::King::isValidMove(std::pair<int, int> newPos)
{

    return false;   
}

std::vector<std::pair<int, int>> Chess::King::getValidMoves()
{
    return {};
}

std::vector<std::pair<int, int>> Chess::King::getCoverage()
{
    return {};
}
