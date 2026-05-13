#include "display.hpp"
#include <string>
#include "piece.hpp"

std::string pieceToStr(Piece piece) {
    if (piece == Piece::EMPTY) return "  \x1b[0m";

    std::string result = "";

    switch (piece) {
        case Piece::W_PAWN:   case Piece::B_PAWN:   result.append("P "); break;
        case Piece::W_KNIGHT: case Piece::B_KNIGHT: result.append("N "); break;
        case Piece::W_BISHOP: case Piece::B_BISHOP: result.append("B "); break;
        case Piece::W_ROOK:   case Piece::B_ROOK:   result.append("R "); break;
        case Piece::W_QUEEN:  case Piece::B_QUEEN:  result.append("Q "); break;
        case Piece::W_KING:   case Piece::B_KING:   result.append("K "); break;
        case Piece::EMPTY:                          result.append("this should never happen"); break;
    }

    if (isWhite(piece)) {
        result.insert(0, "\x1b[97m"); // the ansi escape for white
    } else {
        result.insert(0, "\x1b[30m"); // ansi escape for dark black
    }

    result.append("\x1b[39m");
    return result;
}

std::string pieceToAlgebraic(Piece piece) {
    switch (piece) {
        case Piece::W_PAWN:   case Piece::B_PAWN:   return "P";
        case Piece::W_KNIGHT: case Piece::B_KNIGHT: return "N";
        case Piece::W_BISHOP: case Piece::B_BISHOP: return "B";
        case Piece::W_ROOK:   case Piece::B_ROOK:   return "R";
        case Piece::W_QUEEN:  case Piece::B_QUEEN:  return "Q";
        case Piece::W_KING:   case Piece::B_KING:   return "K";
        default: return "";
    }
}
