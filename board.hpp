#pragma once

#include <iostream>
#include <string>
#include "piece.hpp"
#include "move.hpp"
#include <vector>

struct Board {
    Piece chessboard[8][8] = {}; // will upgrade to bitboard later

    bool whiteToMove = true;
    bool canCastleWk, canCastleWq, CanCastleBk, canCastleBq;
    int fiftyMoveRuleCounter = 0;
    int moves = 0;

    Move* moveBuffer;
    int enPassantSquare[2] = {-1, -1};

    Board();
    ~Board();
    friend std::ostream& operator<<(std::ostream& os, const Board& obj); // so i can cout it
    void display();
    std::vector<Move> getPsuedoMoves(); // for user friendly stuff, not high-performance internal enigne calculation
    void loadFen(std::string fen);

    private:
        std::string pieceToStr(Piece piece) const;
        /**
        *@brief returns true for white, false for black
        */
        bool getColor(Piece piece) const;
};