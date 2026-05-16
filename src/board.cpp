#include "board.hpp"
#include "config.hpp"
#include "move.hpp"
#include "movegen.hpp"
#include <cctype>
#include "rawpiece.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include "display.hpp"
#include <vector>
#include "cctype"
#include <cstring>

Board::Board() {
    canCastleWk = canCastleWq = CanCastleBk = canCastleBq = false;
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

    Move moveBuffer[LEGAL_MOVES_BUFFER_MAX];
}

// Board::~Board() {
//     delete[] moveBuffer;
// }

std::vector<Move> Board::getPsuedoMoves() {
    Move* end = ::getPsuedoMoves(*this, moveBuffer, whiteToMove);
    Move* beginning = moveBuffer;

    return std::vector<Move>(beginning, end);
}

std::string getSquareBgEscapeCode(int x, int y) {
    if ((x & 1) == (y & 1)) return "\x1b[48;2;150;75;0m";
    else {return "\x1b[48;2;196;164;132m";}
}

using std::string;
void Board::loadFen(string fen) {
    std::stringstream data(fen);

    string board;
    char color;
    string castleRights;
    string enPassant;
    int halfmoves;
    int fullmoves;

    data >> board >> color >> castleRights >> enPassant >> halfmoves >> fullmoves;

    // BOARD
    memset(chessboard, 0, sizeof(chessboard)); // clear the board first

    std::stringstream boardData(board);
    std::string segment;
    std::vector<std::string> rowlist;

    while(std::getline(boardData, segment, '/')) {
        rowlist.push_back(segment);
    }

    int row = 0;
    for (const std::string& rowStr : rowlist) {
        int col = 0;
        for (char c : rowStr) {
            if (isdigit(c)) {
                col += (c - '0');
            } else {
                if (isupper(c)) {
                    chessboard[row][col] = getFullPiece(charToPiece(c), true);
                } else {
                    chessboard[row][col] = getFullPiece(charToPiece(c), false);
                }
                col++;
            }
        }
        row++;
    }


    // COLOR
    if (color == 'w') {
        whiteToMove = true;
    } else {
        whiteToMove = false;
    }

    // CASTLE RIGHTS
    canCastleWk = canCastleWq = CanCastleBk = canCastleBq = false;
    for (char c : castleRights) {
        switch (c) {
            case 'K': canCastleWk = true; break;
            case 'Q': canCastleWq = true; break;
            case 'k': CanCastleBk = true; break;
            case 'q': canCastleBq = true; break;
        }
    }

    // EN PASSANT
    if (enPassant == "-") {
        enPassantSquare[0] = enPassantSquare[1] = -1;
    } else {
        enPassantSquare[1] = enPassant[0] - 'a';
        enPassantSquare[0] = 8 - (enPassant[1] - '0');
    }

    // HALFMOVES
    fiftyMoveRuleCounter = halfmoves;

    // FULLMOVES
    moves = fullmoves;
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

    os << "Side to move: " << (obj.whiteToMove ? "White" : "Black") << "\n";

    os << "Castling Rights: ";
    if (obj.canCastleWk) os << "K";
    if (obj.canCastleWq) os << "Q";
    if (obj.CanCastleBk) os << "k";
    if (obj.canCastleBq) os << "q";
    if (!(obj.canCastleWk || obj.canCastleWq || obj.CanCastleBk || obj.canCastleBq)) os << "-";
    os << "\n";

    os << "En Passant: ";
    if (obj.enPassantSquare[0] != -1) {
        os << (char)('a' + obj.enPassantSquare[1]) << (8 - obj.enPassantSquare[0]);
    } else {
        os << "-";
    }
    os << "\n";

    os << "Fifty Move Rule: " << obj.fiftyMoveRuleCounter << "\n";
    os << "Move Number: " << obj.moves << "\n";

    return os;
}
