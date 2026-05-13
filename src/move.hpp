#pragma once
#include "piece.hpp"
#include <iostream>
#include <string>
#include "display.hpp"

enum class Piece;

inline std::string squareToAlgebraic(int row, int col) {
    return std::string(1, static_cast<char>('a' + col)) + std::to_string(8 - row);
}

struct Move {
    int from[2];
    int to[2];
    
    Piece piece;
    Piece captured;

    Piece promotion; // empty if none

    bool isEnPassant;
    bool isCastling;

    void debugPrint() const {
        std::cout << "Move from " << squareToAlgebraic(from[0], from[1])
                  << " to " << squareToAlgebraic(to[0], to[1]) << "\n";

        std::cout << "Piece: " << pieceToStr(piece) << ", Captured: " << pieceToStr(captured) 
                  << ", Promotion: " << pieceToStr(promotion) 
                  << ", En Passant: " << (isEnPassant ? "Yes" : "No") 
                  << ", Castling: " << (isCastling ? "Yes" : "No") << "\n";
    }
};

