#pragma once

constexpr int LEGAL_MOVES_BUFFER_MAX = 512;
constexpr int BOARD_SIZE = 8;
constexpr int knightMoves[8][2] = {
    {2, 1},
    {2, -1},
    {1, 2},
    {1, -2},
    {-1, 2},
    {-1, -2},
    {-2, 1},
    {-2, -1}
};