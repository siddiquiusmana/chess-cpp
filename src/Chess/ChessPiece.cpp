#include "../include/Chess/ChessPiece.h"

int Chess::ChessPiece::getCol()
{
    return this->col;
}

int Chess::ChessPiece::getRow()
{
    return this->row;
}

Chess::Type Chess::ChessPiece::getType()
{
    return this->type;
}

bool Chess::ChessPiece::isWhitePiece()
{
    return this->isWhite;
}

std::vector<Chess::ChessPiece::MoveLog> Chess::ChessPiece::getMoveHistory()
{
    return this->moveHistory;
}