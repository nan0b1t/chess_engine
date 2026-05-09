#include "board.hpp"
#include <iostream>
//#include "piece.hpp"

int main(){
    Board board = Board();
    std::cout << board;

    // for (auto item : board.getPsuedoMoves()) {
    //     std::cout << moveToAlgebraic(item) << '\n';
    // }

   board.loadFen("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1") ;
   std::cout << board;

    return 0;
}
