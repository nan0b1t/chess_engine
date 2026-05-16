#pragma once
#include "move.hpp"
#include "board.hpp"

Move* getPsuedoMoves(const Board& board, Move* moves, bool whiteToPlay);
// Move* getLegalMoves(const Board& board, Move* moves, Move* movesEnd);
// getting legal moves in the algorithm is more efficent
