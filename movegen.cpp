#include "movegen.hpp"
#include "board.hpp"
#include "config.hpp"
#include "piece.hpp"
#include "move.hpp"

enum class RawPiece {
    PAWN,
    ROOK,
    BISHOP,
    KING,
    QUEEN,
    KNIGHT
};

Piece getFullPiece(RawPiece raw, bool isWhite) {
    if (isWhite) {
        switch (raw) {
            case RawPiece::PAWN:   return Piece::W_PAWN;
            case RawPiece::ROOK:   return Piece::W_ROOK;
            case RawPiece::BISHOP: return Piece::W_BISHOP;
            case RawPiece::KING:   return Piece::W_KING;
            case RawPiece::QUEEN:  return Piece::W_QUEEN;
            case RawPiece::KNIGHT: return Piece::W_KNIGHT;
        }
    } else {
        switch (raw) {
            case RawPiece::PAWN:   return Piece::B_PAWN;
            case RawPiece::ROOK:   return Piece::B_ROOK;
            case RawPiece::BISHOP: return Piece::B_BISHOP;
            case RawPiece::KING:   return Piece::B_KING;
            case RawPiece::QUEEN:  return Piece::B_QUEEN;
            case RawPiece::KNIGHT: return Piece::B_KNIGHT;
        }
    }
}

Move* getPsuedoMoves(const Board& board, Move* moves) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Piece piece = board.chessboard[i][j];

            if (piece == Piece::EMPTY) {
               continue;
            }

            if (isPawn(piece)) {
                int forwardIndex;
                if (isWhite(piece)) forwardIndex = i - 1; else forwardIndex = i + 1;

                if (board.chessboard[forwardIndex][j] == Piece::EMPTY) { // Empty square in front of piece
                    if ((forwardIndex == 0 && isWhite(piece)) || (forwardIndex == 7 && !isWhite(piece))) { // on promoting square
                        *moves = {
                            .from = {i, j},
                            .to = {forwardIndex, j},
                            .piece = piece,
                            .captured = Piece::EMPTY,
                            .promotion = getFullPiece(RawPiece::QUEEN, isWhite(piece)),
                            .isEnPassant = false,
                            .isCastling = false
                        };
                        moves++;

                        *moves = {
                            .from = {i, j},
                            .to = {forwardIndex, j},
                            .piece = piece,
                            .captured = Piece::EMPTY,
                            .promotion = getFullPiece(RawPiece::ROOK, isWhite(piece)),
                            .isEnPassant = false,
                            .isCastling = false
                        };
                        moves++;


                        *moves = {
                            .from = {i, j},
                            .to = {forwardIndex, j},
                            .piece = piece,
                            .captured = Piece::EMPTY,
                            .promotion = getFullPiece(RawPiece::BISHOP, isWhite(piece)),
                            .isEnPassant = false,
                            .isCastling = false
                        };
                        moves++;

                        *moves = {
                            .from = {i, j},
                            .to = {forwardIndex, j},
                            .piece = piece,
                            .captured = Piece::EMPTY,
                            .promotion = getFullPiece(RawPiece::KNIGHT, isWhite(piece)),
                            .isEnPassant = false,
                            .isCastling = false
                        };
                        moves++;

                    } else {
                        if ()
                        *moves = {.from = {i, j}, .to = {forwardIndex, j}, .piece = piece, .captured = Piece::EMPTY, .promotion = Piece::EMPTY, .isEnPassant = false, .isCastling = false};
                    }
                }
            }
        }
    }
}