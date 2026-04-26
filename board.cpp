#include "board.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

Board::Board() {
    Piece initialChessboard[8][8] = {{Piece::B_ROOK, Piece::B_KNIGHT, Piece::B_BISHOP, Piece::B_QUEEN, Piece::B_KING, Piece::B_BISHOP, Piece::B_KNIGHT, Piece::B_ROOK},
                                {Piece::B_PAWN, Piece::B_PAWN,   Piece::B_PAWN,   Piece::B_PAWN,  Piece::B_PAWN, Piece::B_PAWN,   Piece::B_PAWN,   Piece::B_PAWN},
                                {Piece::EMPTY,  Piece::EMPTY,    Piece::EMPTY,    Piece::EMPTY,   Piece::EMPTY,  Piece::EMPTY,    Piece::EMPTY,    Piece::EMPTY},
                                {Piece::EMPTY,  Piece::EMPTY,    Piece::EMPTY,    Piece::EMPTY,   Piece::EMPTY,  Piece::EMPTY,    Piece::EMPTY,    Piece::EMPTY},
                                {Piece::EMPTY,  Piece::EMPTY,    Piece::EMPTY,    Piece::EMPTY,   Piece::EMPTY,  Piece::EMPTY,    Piece::EMPTY,    Piece::EMPTY},
                                {Piece::EMPTY,  Piece::EMPTY,    Piece::EMPTY,    Piece::EMPTY,   Piece::EMPTY,  Piece::EMPTY,    Piece::EMPTY,    Piece::EMPTY},
                                {Piece::W_PAWN, Piece::W_PAWN,   Piece::W_PAWN,   Piece::W_PAWN,  Piece::W_PAWN, Piece::W_PAWN,   Piece::W_PAWN,   Piece::W_PAWN},
                                {Piece::W_ROOK, Piece::W_KNIGHT, Piece::W_BISHOP, Piece::W_QUEEN, Piece::W_KING, Piece::W_BISHOP, Piece::W_KNIGHT, Piece::W_ROOK}};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chessboard[i][j] = initialChessboard[i][j];
        }
    }
}

// returns true for white false for black
bool Board::getColor(Piece piece) const{
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

std::string Board::pieceToStr(Piece piece) const {
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

    if (getColor(piece)) {
        result.insert(0, "\x1b[97m"); // the ansi escape for white
    } else {
        result.insert(0, "\x1b[30m"); // ansi escape for dark black
    }

    result.append("\x1b[39m");
    return result;
}

std::string getSquareBgEscapeCode(int x, int y) {
    if ((x & 1) == (y & 1)) return "\x1b[48;2;150;75;0m";
    else {return "\x1b[48;2;196;164;132m";} 
}

std::ostream& operator<<(std::ostream& os, const Board& obj) {
    os << "  a b c d e f g h\n";
    for (int i = 0; i < 8; ++i) {
        os << 8 - i << " ";
        for (int j = 0; j < 8; ++j) {
            os << getSquareBgEscapeCode(j, i) << obj.pieceToStr(obj.chessboard[i][j]) << "\x1b[0m";
        }
        os << "\n";
    }
    return os;
}
