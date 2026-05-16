import argparse
import random
import sys

VALID_PIECES = {
    "p": ("P", "p"),
    "r": ("R", "r"),
    "n": ("N", "n"),
    "b": ("B", "b"),
    "q": ("Q", "q"),
    "k": ("K", "k"),
}


def parse_args():
    parser = argparse.ArgumentParser(
        description="Generate random FEN positions using a subset of piece types."
    )
    parser.add_argument(
        "num_fens",
        type=int,
        help="Number of random FEN positions to generate.",
    )
    parser.add_argument(
        "pieces",
        nargs="?",
        default="p",
        help="Piece types to include, e.g. prk for pawns, rooks, and kings.",
    )
    parser.add_argument(
        "--output",
        default="tests/RANDOM_TESTS.fen",
        help="Output file for generated FENs.",
    )
    return parser.parse_args()


def build_piece_pool(piece_string):
    letters = [letter.lower() for letter in piece_string]
    pieces = []

    for letter in letters:
        if letter not in VALID_PIECES:
            print(
                f"Invalid piece character '{letter}'. Use only: {''.join(VALID_PIECES.keys())}."
            )
            sys.exit(1)
        pieces.extend(VALID_PIECES[letter])

    if not pieces:
        print("No valid pieces specified.")
        sys.exit(1)

    return pieces


def generate_random_fen(piece_pool):
    board = []
    fen = ""
    en_passant_square = "-"

    for rank in range(8):
        row = []
        for _ in range(8):
            piece = random.choice(piece_pool + [" "])

            if (rank == 0 or rank == 7) and piece in ["P", "p"]:
                piece = " "

            row.append(piece)
        board.append(row)

    for row_index, row in enumerate(board):
        for cell_index, cell in enumerate(row):
            en_passant_square = "-"

            match cell:
                case "P":
                    fen += "P"
                    if row_index == 4 and random.random() < 0.9:
                        en_passant_square = chr(ord("a") + cell_index) + "3"
                case "p":
                    fen += "p"
                    if row_index == 3 and random.random() < 0.9:
                        en_passant_square = chr(ord("a") + cell_index) + "6"
                case " ":
                    fen += "1"
                case _:
                    fen += cell
        fen += "/"

    fen = fen[:-1]

    collapsed_fen = ""
    empty_count = 0
    for char in fen:
        if char == "1":
            empty_count += 1
        else:
            if empty_count > 0:
                collapsed_fen += str(empty_count)
                empty_count = 0
            collapsed_fen += char
    if empty_count > 0:
        collapsed_fen += str(empty_count)

    fen = collapsed_fen
    to_move = random.choice(["w", "b"])
    castling = ""

    if random.choice([True, False]):
        castling += "K"
    if random.choice([True, False]):
        castling += "Q"
    if random.choice([True, False]):
        castling += "k"
    if random.choice([True, False]):
        castling += "q"

    if castling == "":
        castling = "-"

    fen += f" {to_move} {castling} {en_passant_square} 0 1"
    return fen


def main():
    args = parse_args()
    piece_pool = build_piece_pool(args.pieces)

    with open(args.output, "a") as file:
        for _ in range(args.num_fens):
            fen = generate_random_fen(piece_pool)
            file.write(fen + "\n")


if __name__ == "__main__":
    main()
