#include "board.hpp"
#include "config.hpp"
#include "piece.hpp"
#include <cstdint>

struct Score;

Score evaluateBoard(const Board& board) {
    int16_t absResult = 0;


    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            Piece piece = board.chessboard[row][col];

            if (piece == Piece::EMPTY) {
                continue;
            }

            int index = static_cast<int>(piece);

            absResult += pieceValues[index] * ISWHITE[index];
        }
    }
    return board.whiteToMove ? Score{absResult} : Score{static_cast<int16_t>(-absResult)};
}
