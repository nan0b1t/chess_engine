#pragma once
#include "move.hpp"
#include "board.hpp"

Move* getPsuedoMoves(const Board& board, Move* moves);
Move* getLegalMoves(const Board& board, Move* moves);

