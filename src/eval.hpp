#pragma once
#include <cstdint>
#include "board.hpp"

struct Score {
    int16_t value;
    static constexpr int16_t VALUE_INFINITE = 32767;
    static constexpr int16_t VALUE_MATE_MIN= 32001;
    static constexpr int16_t VALUE_MATE_MAX= 32766;
};

Score evaluateBoard(const Board& board);
