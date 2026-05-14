import random

arg = input("Enter the number of random FENs to generate: ")
try:
    num_fens = int(arg)
except ValueError:
    print("Invalid input. Please enter a valid integer.")
    exit(1)


def generate_random_fen():
    board = []
    fen = ''
    en_passant_square = '-'

    for i in range(8):
        row = []
        for _ in range(8):
            piece = random.choice(['P', 'p', ' '])

            if (i == 0 or i == 7) and piece in ['P', 'p']:
                piece = ' '
            
            row.append(piece)
        board.append(row)

    for row_index, row in enumerate(board):
        for cell_index, cell in enumerate(row):
            match cell:
                case 'P':
                    fen += 'P'
                    if (row_index == 4) and random.random() < 0.8: # add en passant square for white pawn on 5th rank
                        en_passant_square = chr(ord('a') + cell_index) + '3'
                case 'p':
                    fen += 'p'
                    if (row_index == 3) and random.random() < 0.8: # add en passant square for black pawn on 4th rank
                        en_passant_square = chr(ord('a') + cell_index) + '6'
                case ' ':
                    fen += '1'
        fen += '/'
    
    fen = fen[:-1]  # Remove the trailing '/'

    # collapse consecutive empty squares
    collapsed_fen = ''
    empty_count = 0
    for char in fen:
        if char == '1':
            empty_count += 1
        else:
            if empty_count > 0:
                collapsed_fen += str(empty_count)
                empty_count = 0
            collapsed_fen += char
    if empty_count > 0:
        collapsed_fen += str(empty_count)

    fen = collapsed_fen

    to_move = random.choice(['w', 'b'])
    castleling = ''

    if random.choice([True, False]):
        castleling += 'K'
    if random.choice([True, False]):
        castleling += 'Q'
    if random.choice([True, False]):
        castleling += 'k'
    if random.choice([True, False]):
        castleling += 'q'    

    if castleling == '':
        castleling = '-'
    
    fen += f" {to_move} {castleling} {en_passant_square} 0 1"
    return fen

with open("tests/RANDOM_TESTS.fen", "a") as file:
    for _ in range(num_fens):
        fen = generate_random_fen()
        file.write(fen + "\n")
