# nanobit's chess engine

This is a simple chess engine I am working on, written in C++23.

---

## Completed Features

- 8x8 board representation with full piece tracking
- FEN string parsing and loading
- Board display with ANSI color output in the terminal
- Castling rights, en passant square, and fifty-move rule tracking
- Pseudo-legal move generation for pawns (including promotions and en passant)
- Move struct with promotion, castling, and en passant metadata
- Algebraic notation conversion for moves

---

## Planned Features

- Move generation for all remaining pieces (knights, bishops, rooks, queens, kings)
- Legal move generation (filter out moves that leave the king in check)
- Upgrade board representation from 8x8 array to bitboards
- Search algorithm (e.g. minimax with alpha-beta pruning)
- Position evaluation function
- UCI protocol support

---

## Testing

Move generation is tested against the [python-chess](https://python-chess.readthedocs.io/) library. The test script takes a file of FEN strings (one per line) and compares the engine's output moves against python-chess's legal move list.

**Requirements:**
- Python 3
- `python-chess` (`pip install chess`)

**Run tests with Make:**
```bash
make test
```

**Run tests with a custom test file:**
```bash
make test TEST_FILE=your_test_file.fen
```

The default test file is `tests/pawntest.fen` and the script runs `tests/test.py`.

For example, using the included pawn test positions:
```bash
make test
```

To also print the board state after each FEN is loaded, run the script directly:
```bash
python tests/test.py tests/pawntest.fen print_board_after_fen_load
```

---

## Installation

**Requirements:**
- A C++23-compatible compiler (e.g. `clang++` or `g++`)
- `make` (e.g. via [MinGW](https://www.mingw-w64.org/) or [MSYS2](https://www.msys2.org/) on Windows)
- [`mold`](https://github.com/rui314/mold) *(optional, Linux only)* - a significantly faster linker that speeds up incremental builds

**Build (release):**
```bash
git clone https://github.com/nan0b1t/chess_engine.git
cd chess_engine
make
```

**Build with mold (faster linking on Linux):**
```bash
make MOLD=1
```

**Build (debug):**
```bash
make MODE=debug
```

**Run:**
```bash
./chess_engine "<fen_string>" [print_board_after_fen_load]
```

**Clean:**
```bash
make clean
```