#include "movegen.hpp"

#include "board.hpp"
#include "config.hpp"
#include "move.hpp"
#include "piece.hpp"
#include "rawpiece.hpp"

Move* slide(int offsetI, int offsetJ, int startI, int startJ, Move* movePtr, const Board& board);

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

bool isCapturable(Piece p1, Piece p2) {
    return p1 != Piece::EMPTY && p2 != Piece::EMPTY && (isWhite(p1) != isWhite(p2));
}

Move* getPsuedoMoves(const Board& board, Move* moves, bool whiteToPlay)
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Piece piece = board.chessboard[i][j];

            if (piece == Piece::EMPTY) {
                continue;
            }

            if (whiteToPlay != isWhite(piece)) continue; // skip pieces that arent the color to move

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
                if (j > 0 && forwardIndex >= 0 && forwardIndex < 8) {
                    Piece target = board.chessboard[forwardIndex][j - 1];

                    if (isCapturable(target, piece)) {
                        if (forwardIndex == 0 || forwardIndex == 7) {
                            addPromotionMoves(&moves, i, j, forwardIndex, j - 1, piece, target, isWhite(piece), false);
                        } else {
                            *moves = { .from = { i, j },
                                .to = { forwardIndex, j - 1 },
                                .piece = piece,
                                .captured = target,
                                .promotion = Piece::EMPTY,
                                .isEnPassant = false,
                                .isCastling = false };
                            moves++;
                        }
                    }
                }

                // check right capture
                if (j < 7 && forwardIndex >= 0 && forwardIndex < 8) {
                    Piece target = board.chessboard[forwardIndex][j + 1];

                    if (isCapturable(target, piece)) {
                        if (forwardIndex == 0 || forwardIndex == 7) {
                            addPromotionMoves(&moves, i, j, forwardIndex, j + 1, piece, target, isWhite(piece), false);
                        } else {
                            *moves = { .from = { i, j },
                                    .to = { forwardIndex, j + 1 },
                                    .piece = piece,
                                    .captured = target,
                                    .promotion = Piece::EMPTY,
                                    .isEnPassant = false,
                                    .isCastling = false };
                            moves++;
                        }
                    }
                }

                // en passant
                if (board.enPassantSquare[0] == forwardIndex
                    && ((j == board.enPassantSquare[1] - 1) || (j == board.enPassantSquare[1] + 1))) {
                    Piece epTarget = board.chessboard[i][board.enPassantSquare[1]];
                    if (isCapturable(epTarget, piece) && isPawn(epTarget) && (isCapturable(piece, board.chessboard[board.enPassantSquare[0]][board.enPassantSquare[1]]))) {
                        *moves = { .from = { i, j },
                            .to = { board.enPassantSquare[0], board.enPassantSquare[1] },
                            .piece = piece,
                            .captured = epTarget,
                            .promotion = Piece::EMPTY,
                            .isEnPassant = true,
                            .isCastling = false };
                        moves++;
                    }
                }
            }

            if (isKnight(piece)) {
                for (const int (&move)[2] : knightMoves) {
                    int capturedI = i + move[1];
                    int capturedJ = j + move[0];

                    if (capturedI < 0 || capturedI > 7  || capturedJ < 0 || capturedJ > 7) {
                        continue;
                    }

                    Piece capturedPiece = board.chessboard[capturedI][capturedJ];

                    if ((isCapturable(piece, capturedPiece) || capturedPiece == Piece::EMPTY)) {
                        *moves++ = {
                            .from = {i, j},
                            .to = {i + move[1], j + move[0]},
                            .piece = piece,
                            .captured = capturedPiece,
                            .promotion = Piece::EMPTY,
                            .isEnPassant = false,
                            .isCastling = false
                        };
                    }
                }
            }

            if (isKing(piece)) {
                for (const int (&move)[2] : kingMoves) {
                    int capturedI = i + move[1];
                    int capturedJ = j + move[0];

                    if (capturedI < 0 || capturedI > 7  || capturedJ < 0 || capturedJ > 7) {
                        continue;
                    }

                    Piece capturedPiece = board.chessboard[capturedI][capturedJ];


                    if ((isCapturable(piece, capturedPiece) || capturedPiece == Piece::EMPTY)) {
                        *moves++ = {
                            .from = {i, j},
                            .to = {i + move[1], j + move[0]},
                            .piece = piece,
                            .captured = capturedPiece,
                            .promotion = Piece::EMPTY,
                            .isEnPassant = false,
                            .isCastling = false
                        };
                    }
                }
            }

            if (isRook(piece)) {
                moves = slide(1, 0, i, j, moves, board);
                moves = slide(-1, 0, i, j, moves, board);
                moves = slide(0, 1, i, j, moves, board);
                moves = slide(0, -1, i, j, moves, board);
            }
        }
    }
    return moves; // used for iterating until end of moves
}

Move* slide(int offsetI, int offsetJ, int startI, int startJ, Move* movePtr, const Board& board) {
    Piece piece = board.chessboard[startI][startJ];

    int i = startI + offsetI;
    int j = startJ + offsetJ;

    while (i <= 7 && i >= 0 && j <= 7 && j >= 0) {
        Piece movedTo = board.chessboard[i][j];

        if (isCapturable(piece, movedTo)) {
            *movePtr = {
                .from = {startI, startJ},
                .to = {i, j},
                .piece = piece,
                .captured = movedTo,
                .promotion = Piece::EMPTY,
                .isEnPassant = false,
                .isCastling = false
            };
            movePtr++;
            return movePtr;
        }

        if (isWhite(movedTo) == isWhite(piece) && movedTo != Piece::EMPTY) {
            return movePtr;
        }

        if (movedTo == Piece::EMPTY) {
            *movePtr = {
                .from = {startI, startJ},
                .to = {i, j},
                .piece = piece,
                .captured = Piece::EMPTY,
                .promotion = Piece::EMPTY,
                .isEnPassant = false,
                .isCastling = false
            };
            movePtr++;
        }

        i += offsetI;
        j += offsetJ;
    }

    return movePtr;
}
