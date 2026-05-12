#include "board.hpp"
#include <iostream>
#include "piece.hpp"
#include <string>

// Usage: ./chess_engine [fen_string] [optional: print_board_after_fen_load]
int main(int argc, char* argv[]){

    std::string fen;
    if (argc > 1) {
        fen = argv[1];
    } else {
        std::cout << "No arguments provided. "<< "Usage: ./chess_engine [fen_string]\n";
        return 1;
    }

    Board board = Board();
    board.loadFen(fen);

    std::cout << "START\n";
    for (auto item : board.getPsuedoMoves()) {
        std::cout << moveToAlgebraic(item) << '\n';
    }
    std::cout << "END\n";

    std::cout << "-\n";
    if (argc > 2 && std::string(argv[2]) == "print_board_after_fen_load") {
       std::cout << board;
    }
    std::cout << "-\n";


    return 0;
}
