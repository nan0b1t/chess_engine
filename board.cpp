#include "board.hpp"
#include "config.hpp"
#include "move.hpp"
#include "movegen.hpp"
#include <iostream>
#include <string>
#include "display.hpp"

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

    moveBuffer = new Move[LEGAL_MOVES_BUFFER_MAX];
}

Board::~Board() {
    delete[] moveBuffer;
}

std::vector<Move> Board::getPsuedoMoves() {
    Move* end = ::getPsuedoMoves(*this, moveBuffer);
    Move* beginning = moveBuffer;

    return std::vector<Move>(beginning, end);
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
            os << getSquareBgEscapeCode(j, i) << pieceToStr(obj.chessboard[i][j]) << "\x1b[0m";
        }
        os << "\n";
    }
    return os;
}
