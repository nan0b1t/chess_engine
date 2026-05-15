#include "piece.hpp"
#include "board.hpp"
#include "move.hpp"
#include "display.hpp"
#include <string>
#include "movegen.hpp"
#include "config.hpp"

std::string moveToAlgebraic(const Move& move, const Board& board) {
    // CASTLING
    if (move.isCastling) {
        return (move.to[1] == 6) ? "O-O" : "O-O-O";
    }

    if (move.isEnPassant) {
        return std::string(1, static_cast<char>('a' + move.from[1])) + "x" +
               static_cast<char>('a' + move.to[1]) + std::to_string(8 - move.to[0]);
    }

    std::string notation = "";
    bool isPawn = (move.piece == Piece::W_PAWN || move.piece == Piece::B_PAWN);

    // Piece identifier
    if (!isPawn) {
        notation += pieceToAlgebraic(move.piece);
        
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int col = 0; col < BOARD_SIZE; col++) {
                if (canMoveTo(board.chessboard[row][col], row, col, move.to[0], move.to[1], board)) {

                }
            }
        }
    }

    // Capture indicator
    if (move.captured != Piece::EMPTY || move.isEnPassant) {
        if (isPawn) {
            notation += static_cast<char>('a' + move.from[1]);
        }
        notation += 'x';
    }

    // Destination square
    notation += static_cast<char>('a' + move.to[1]);
    notation += std::to_string(8 - move.to[0]);

    // Promotion
    if (move.promotion != Piece::EMPTY) {
        notation += "=";
        notation += pieceToAlgebraic(move.promotion);
    }

    return notation;
}

bool checkForAmbiguation(const Move& move, const Board& board) {

}

bool canMoveTo(Piece piece, int rankFrom, int fileFrom, int rankTo, int fileTo, const Board &board) {
    Move moveBuf[LEGAL_MOVES_BUFFER_MAX];
    Move* end = getPsuedoMoves(board, moveBuf, board.whiteToMove);

    for (Move* begin = moveBuf; begin < end; begin++) {
        Move move = *begin;

        if (move.piece == piece && move.to[0] == rankTo && move.to[1] == fileTo &&
            move.from[0] == rankFrom && move.from[1] == fileFrom) {
            return true;
        }
    }

    return false;
}