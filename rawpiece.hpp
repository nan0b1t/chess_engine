#include "piece.hpp"
#include <cctype>

enum class RawPiece { PAWN,
    ROOK,
    BISHOP,
    KING,
    QUEEN,
    KNIGHT,
    NONE
};

inline Piece getFullPiece(RawPiece raw, bool isWhite)
{
    if (isWhite) {
        switch (raw) {
        case RawPiece::PAWN:
            return Piece::W_PAWN;
        case RawPiece::ROOK:
            return Piece::W_ROOK;
        case RawPiece::BISHOP:
            return Piece::W_BISHOP;
        case RawPiece::KING:
            return Piece::W_KING;
        case RawPiece::QUEEN:
            return Piece::W_QUEEN;
        case RawPiece::KNIGHT:
            return Piece::W_KNIGHT;
        default: return Piece::EMPTY;
        }
    } else {
        switch (raw) {
        case RawPiece::PAWN:
            return Piece::B_PAWN;
        case RawPiece::ROOK:
            return Piece::B_ROOK;
        case RawPiece::BISHOP:
            return Piece::B_BISHOP;
        case RawPiece::KING:
            return Piece::B_KING;
        case RawPiece::QUEEN:
            return Piece::B_QUEEN;
        case RawPiece::KNIGHT:
            return Piece::B_KNIGHT;
        default: return Piece::EMPTY;
        }
    }
    throw "Impossible error";
}

inline RawPiece charToPiece(char p) {
    // Convert to lowercase to handle both 'P' and 'p'
    switch (std::tolower(p)) {
        case 'p': return RawPiece::PAWN;
        case 'r': return RawPiece::ROOK;
        case 'b': return RawPiece::BISHOP;
        case 'k': return RawPiece::KING;
        case 'q': return RawPiece::QUEEN;
        case 'n': return RawPiece::KNIGHT;
        default: return RawPiece::NONE;
    }
}
