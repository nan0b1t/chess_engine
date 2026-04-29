#include "piece.hpp"
#include "move.hpp"
#include "display.hpp"

std::string move_to_algebraic(const Move& move) {
    if (move.isCastling) {
        // Kingside castling moves to g-file (6), queenside to c-file (2)
        return (move.to[1] == 6) ? "O-O" : "O-O-O";
    }

    std::string notation = "";
    bool isPawn = (move.piece == Piece::W_PAWN || move.piece == Piece::B_PAWN);

    // 1. Piece identifier
    if (!isPawn) {
        notation += pieceToStr(move.piece);
    }

    // 2. Capture indicator
    if (move.captured != Piece::EMPTY || move.isEnPassant) {
        if (isPawn) {
            notation += static_cast<char>('a' + move.from[1]);
        }
        notation += 'x';
    }

    // 3. Destination square
    notation += static_cast<char>('a' + move.to[1]);
    notation += static_cast<char>('1' + move.to[0]);

    // 4. Promotion
    if (move.promotion != Piece::EMPTY) {
        notation += "=";
        notation += pieceToStr(move.promotion);
    }

    return notation;
}