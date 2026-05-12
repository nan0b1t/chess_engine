#include "piece.hpp"
#include "move.hpp"
#include "display.hpp"
#include <string>
#include <iostream>

std::string moveToAlgebraic(const Move& move, bool debug=false) {
    // print move for debugging
    if (debug) {
        std::cout << "Move Details ----------------\n";
        std::cout << "Move: " << move.from[0] << "," << move.from[1] << " to " << move.to[0] << "," << move.to[1] << std::endl;
        std::cout << "Piece: " << pieceToStr(move.piece) << " Captured: " << pieceToStr(move.captured) << " Promotion: " << pieceToStr(move.promotion) << std::endl;
        std::cout << "Is En Passant: " << move.isEnPassant << " Is Castling: " << move.isCastling << std::endl;
    }
    std::cout << "-----------------------------" << std::endl;

    // CASTLING
    if (move.isCastling) {
        return (move.to[1] == 6) ? "O-O" : "O-O-O";
    }

    std::string notation = "";
    bool isPawn = (move.piece == Piece::W_PAWN || move.piece == Piece::B_PAWN);

    // Piece identifier
    if (!isPawn) {
        notation += pieceToStr(move.piece);
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
    notation += static_cast<char>('1' + move.to[0]);

    // Promotion
    if (move.promotion != Piece::EMPTY) {
        notation += "=";
        notation += pieceToStr(move.promotion);
    }

    return notation;
}