#pragma once

#include <iostream>
#include <string>
#include "piece.hpp"


struct Board {
    Piece chessboard[8][8] = {}; // will upgrade to bitboard later

    bool whiteToMove = true;
    bool canCastleWk, canCastleWq, CanCastleBk, canCastleBq;
    int enPassantSquare[2] = {-1, -1};

    Board();
    friend std::ostream& operator<<(std::ostream& os, const Board& obj);
    void display();
    
    private:
        std::string pieceToStr(Piece piece) const;
        /**
        *@brief returns true for white, false for black
        */
        bool getColor(Piece piece) const;
};