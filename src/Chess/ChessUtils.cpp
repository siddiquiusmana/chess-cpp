#include "../include/Chess/ChessUtils.h"

/**
 * Given the chess position of the chess piece, give x, y coordinates of where it should be drawn
 * 
 * @param position The chess position of the chess piece
 * @return the physical location of the chess piece
 */
inline std::pair<int, int> convertFromPositionToLocation(const std::pair<int, int> position, 
    const int boardBorderPixels, const int squareSize)
{
    int x = (position.first * squareSize) + boardBorderPixels;
    int y = (position.second * squareSize) + boardBorderPixels;

    return std::pair<int, int>(x, y);
}

/**
 * Gives the row and column of the chesspiece, given its physical location
 * 
 * @param location The location of the chess piece
 * @return the row and column of the chess piece
 */
inline std::pair<int, int> convertFromLocationToPosition(const std::pair<int, int> location,
    const int boardBorderPixels, const int squareSize)
{
    int row = (location.first - boardBorderPixels) / squareSize;
    int col = (location.second - boardBorderPixels) / squareSize;

    return std::pair<int, int>(row, col);
}