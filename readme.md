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
- Algebraic notation conversion for moves (doesn't differentiate though)

---

## Planned Features

- Move generation for all remaining pieces (knights, bishops, rooks, queens, kings)
- Legal move generation (filter out moves that leave the king in check)
- Upgrade board representation from 8x8 array to bitboards
- Search algorithm (e.g. minimax with alpha-beta pruning)
- Position evaluation function
- UCI protocol support
- Add differentiation to algebraic notation (low priority)
 
---

## Installation

**Requirements:**
- A C++23-compatible compiler (e.g. `clang++` or `g++`)
- [`mold`](https://github.com/rui314/mold) linker
- `make`

**Build (release):**
```bash
git clone https://github.com/nan0b1t/chess_engine.git
cd chess_engine
make
```

**Build (debug):**
```bash
make MODE=debug
```

**Run:**
```bash
./chess_engine
```

**Clean:**
```bash
make clean
```