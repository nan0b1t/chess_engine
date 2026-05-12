#include "piece.hpp"
#include "move.hpp"
#include "display.hpp"
#include <string>

std::string moveToAlgebraic(const Move& move) {

    // CASTLING
    if (move.isCastling) {
        return (move.to[1] == 6) ? "O-O" : "O-O-O";
    }

    std::string notation = "";
    bool isPawn = (move.piece == Piece::W_PAWN || move.piece == Piece::B_PAWN);

    // Piece identifier
    if (!isPawn) {
        notation += pieceToStr(move.piece);
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
    notation += static_cast<char>('1' + move.to[0]);

    // Promotion
    if (move.promotion != Piece::EMPTY) {
        notation += "=";
        notation += pieceToStr(move.promotion);
    }

    return notation;
}