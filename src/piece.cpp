#include "piece.hpp"
#include "board.hpp"
#include "move.hpp"
#include "display.hpp"
#include <string>
#include "movegen.hpp"
#include "config.hpp"
#include <optional>

bool checkForAmbiguation(Piece piece, int rowTo, int fileTo, const Board& board, std::optional<int> rankFrom, std::optional<int> fileFrom, int rowReal, int fileReal);


std::string moveToAlgebraic(const Move& move, const Board& board) {
    // CASTLING
    if (move.isCastling) {
        return (move.to[1] == 6) ? "O-O" : "O-O-O";
    }

    if (move.isEnPassant) {
        return std::string(1, static_cast<char>('a' + move.from[1])) + "x" +
               static_cast<char>('a' + move.to[1]) + std::to_string(8 - move.to[0]);
    }

    std::string notation = "";
    bool isPawn = (move.piece == Piece::W_PAWN || move.piece == Piece::B_PAWN);

    // Piece identifier
    if (!isPawn) {
        notation += pieceToAlgebraic(move.piece);

        bool isAmbiguous = checkForAmbiguation(move.piece, move.to[0], move.to[1], board, std::nullopt, std::nullopt, move.from[0], move.from[1]);

        if (isAmbiguous) {
            bool fileIsAmbiguous = checkForAmbiguation(move.piece, move.to[0], move.to[1], board, std::nullopt, move.from[1], move.from[0], move.from[1]);

            bool rankIsAmbiguous = checkForAmbiguation(move.piece, move.to[0], move.to[1], board, move.from[0], std::nullopt, move.from[0], move.from[1]);

            if (fileIsAmbiguous && rankIsAmbiguous) {
                notation += (move.from[1] + 'a');
                notation += ('8' - move.from[0]);
            } else if (!fileIsAmbiguous) {
                notation += (move.from[1] + 'a');
            } else {
                notation += ('8' - move.from[0]);
            }
        }
    }

    // Capture indicator
    if (move.captured != Piece::EMPTY || move.isEnPassant) {
        if (isPawn) {
            notation += static_cast<char>('a' + move.from[1]);
        }
        notation += 'x';
    }

    // Destination square
    notation += static_cast<char>('a' + move.to[1]);
    notation += std::to_string(8 - move.to[0]);

    // Promotion
    if (move.promotion != Piece::EMPTY) {
        notation += "=";
        notation += pieceToAlgebraic(move.promotion);
    }

    return notation;
}


bool checkForAmbiguation(Piece piece, int rowTo, int fileTo, const Board& board, std::optional<int> rankFrom, std::optional<int> fileFrom, int rowReal, int fileReal) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board.chessboard[row][col] == piece && canMoveTo(board.chessboard[row][col], row, col, rowTo, fileTo, board) && !(row == rowReal && col == fileReal)) {
                if ((rankFrom.has_value() && (row != *rankFrom)) || (fileFrom.has_value() && (col != *fileFrom))) {
                    continue;
                }
                return true;
            }
        }
    }

    return false;
}

bool canMoveTo(Piece piece, int rankFrom, int fileFrom, int rankTo, int fileTo, const Board &board) {
    Move moveBuf[LEGAL_MOVES_BUFFER_MAX];
    Move* end = getPsuedoMoves(board, moveBuf, board.whiteToMove);

    for (Move* begin = moveBuf; begin < end; begin++) {
        Move move = *begin;

        if (move.piece == piece && move.to[0] == rankTo && move.to[1] == fileTo &&
            move.from[0] == rankFrom && move.from[1] == fileFrom) {
            return true;
        }
    }

    return false;
}
