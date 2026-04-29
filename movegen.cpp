#include "movegen.hpp"

#include "board.hpp"
#include "config.hpp"
#include "move.hpp"
#include "piece.hpp"

enum class RawPiece { PAWN,
    ROOK,
    BISHOP,
    KING,
    QUEEN,
    KNIGHT };

Piece getFullPiece(RawPiece raw, bool isWhite)
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
        }
    }
}

void addPromotionMoves(Move** moves, int fromI, int fromJ, int toI, int toJ, Piece piece, Piece captured, bool isWhite, bool isEnPassant)
{
    RawPiece promotionChoices[] = { RawPiece::QUEEN, RawPiece::ROOK, RawPiece::BISHOP, RawPiece::KNIGHT };

    for (RawPiece rp : promotionChoices) {
        **moves = {
            .from = { fromI, fromJ },
            .to = { toI, toJ },
            .piece = piece,
            .captured = captured,
            .promotion = getFullPiece(rp, isWhite),
            .isEnPassant = isEnPassant,
            .isCastling = false
        };
        (*moves)++; // increment the pointer
    }
}

bool isCapturable(Piece p1, Piece p2) { return (isWhite(p1) != isWhite(p2)); }

Move* getPsuedoMoves(const Board& board, Move* moves)
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Piece piece = board.chessboard[i][j];

            if (piece == Piece::EMPTY) {
                continue;
            }

            if (isPawn(piece)) {
                int forwardIndex;
                int doubleIndex;

                bool canDouble = ((isWhite(piece) && (i == 6)) || (!isWhite(piece) && (i == 1)));

                if (isWhite(piece)) {
                    forwardIndex = i - 1;
                    doubleIndex = i - 2;
                } else {
                    forwardIndex = i + 1;
                    doubleIndex = i + 2;
                }

                if (board.chessboard[forwardIndex][j] == Piece::EMPTY) { // Empty square in front of piece
                    if ((forwardIndex == 0 && isWhite(piece)) || (forwardIndex == 7 && !isWhite(piece))) { // on promoting square
                        addPromotionMoves(&moves, i, j, forwardIndex, j, piece, Piece::EMPTY, isWhite(piece), false);
                    } else {
                        *moves = { .from = { i, j },
                            .to = { forwardIndex, j },
                            .piece = piece,
                            .captured = Piece::EMPTY,
                            .promotion = Piece::EMPTY,
                            .isEnPassant = false,
                            .isCastling = false };
                        moves++;
                    }

                    if (board.chessboard[doubleIndex][j] == Piece::EMPTY && canDouble) {
                        *moves = { .from = { i, j },
                            .to = { doubleIndex, j },
                            .piece = piece,
                            .captured = Piece::EMPTY,
                            .promotion = Piece::EMPTY,
                            .isEnPassant = false,
                            .isCastling = false };
                        moves++;
                    }
                }

                // check left capture
                if (j > 0 && i != 7 && i != 0 && isCapturable(board.chessboard[forwardIndex][j - 1], piece)) {

                    if (forwardIndex == 0 || forwardIndex == 7) {
                        addPromotionMoves(&moves, i, j, forwardIndex, j - 1, piece, board.chessboard[forwardIndex][j - 1], isWhite(piece), false);

                        *moves = { .from = { i, j },
                            .to = { forwardIndex, j - 1 },
                            .piece = piece,
                            .captured = board.chessboard[forwardIndex][j - 1],
                            .promotion = Piece::EMPTY,
                            .isEnPassant = false,
                            .isCastling = false };
                        moves++;
                    }

                    // check right capture
                    if (j < 7 && i != 7 && i != 0 && isCapturable(board.chessboard[forwardIndex][j + 1], piece)) {
                        *moves = { .from = { i, j },
                            .to = { forwardIndex, j + 1 },
                            .piece = piece,
                            .captured = board.chessboard[forwardIndex][j + 1],
                            .promotion = Piece::EMPTY,
                            .isEnPassant = false,
                            .isCastling = false };
                        moves++;
                    }

                    if (board.enPassantSquare[0] == i && ((j == board.enPassantSquare[1] - 1) || (j == board.enPassantSquare[1] + 1))) {
                        *moves = { .from = { i, j },
                            .to = { forwardIndex, board.enPassantSquare[1] },
                            .piece = piece,
                            .captured = board.chessboard[board.enPassantSquare[0]]
                                                        [board.enPassantSquare[1]],
                            .promotion = Piece::EMPTY,
                            .isEnPassant = true,
                            .isCastling = false };
                        moves++;
                    }
                }
            }
        }
    }
    return moves; // used for iterating until end of moves
}