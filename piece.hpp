#pragma once
#include <stdexcept>

enum class Piece{
    EMPTY,
    W_PAWN,
    W_KNIGHT,
    W_BISHOP,
    W_ROOK,
    W_QUEEN,
    W_KING,
    B_PAWN,
    B_KNIGHT,
    B_BISHOP,
    B_ROOK,
    B_QUEEN,
    B_KING
};

inline bool isPawn(Piece piece) {
    return (piece == Piece::W_PAWN || piece == Piece::B_PAWN);
}
inline bool isKnight(Piece piece) {
    return (piece == Piece::W_KNIGHT || piece == Piece::B_KNIGHT);
}

inline bool isBishop(Piece piece) {
    return (piece == Piece::W_BISHOP || piece == Piece::B_BISHOP);
}

inline bool isRook(Piece piece) {
    return (piece == Piece::W_ROOK || piece == Piece::B_ROOK);
}

inline bool isQueen(Piece piece) {
    return (piece == Piece::W_QUEEN || piece == Piece::B_QUEEN);
}

inline bool isKing(Piece piece) {
    return (piece == Piece::W_KING || piece == Piece::B_KING);
}

inline bool isWhite(Piece piece) {
    if (piece == Piece::EMPTY) throw std::invalid_argument("Empty squares not allowed!");

    return (
        !(piece == Piece::B_BISHOP ||
          piece == Piece::B_KING   ||
          piece == Piece::B_KNIGHT ||
          piece == Piece::B_PAWN   ||
          piece == Piece::B_QUEEN  ||
          piece == Piece::B_ROOK
        )
    );
}