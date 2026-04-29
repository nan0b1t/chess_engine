#pragma once
#include "piece.hpp"

struct Move {
    int from[2];
    int to[2];
    
    Piece piece;
    Piece captured;

    Piece promotion; // empty if none

    bool isEnPassant;
    bool isCastling;
};

