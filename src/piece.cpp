#include "piece.hpp"
#include "move.hpp"
#include "display.hpp"
#include <string>


std::string moveToAlgebraic(const Move& move) {
    // CASTLING
    if (move.isCastling) {
        return (move.to[1] == 6) ? "O-O" : "O-O-O";
    }

    // for some reason en passant is only triggered once in the entire pawn test, at 8/8/8/6pP/8/8/8/8 b - g6 0 1
    // the movegen is probably wrong - not this function

    if (move.isEnPassant) {
        return std::string(1, static_cast<char>('a' + move.from[1])) + "x" +
               static_cast<char>('a' + move.to[1]) + std::to_string(8 - move.to[0]);
    }

    std::string notation = "";
    bool isPawn = (move.piece == Piece::W_PAWN || move.piece == Piece::B_PAWN);

    // Piece identifier
    if (!isPawn) {
        notation += pieceToAlgebraic(move.piece);
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