#include "board.hpp"
#include <iostream>
#include "display.hpp"

int main(){
    Board board = Board();
    std::cout << board;

    for (auto item : board.getPsuedoMoves()) {
        std::cout << move_to_algebraic(item)
    }
    return 0;
}
