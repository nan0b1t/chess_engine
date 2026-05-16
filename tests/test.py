import subprocess
import sys
from collections import defaultdict

try:
    import chess
except ImportError:
    print(
        "The 'chess' library is required to run this test. Please install it using 'pip install -r requirements.txt'."
    )
    sys.exit(1)

try:
    args = sys.argv[1]
    printBoardAfterFenLoad = sys.argv[2] if len(sys.argv) > 2 else None
    showFailedFens = sys.argv[3] if len(sys.argv) > 3 else None

    with open(args, "r") as f:
        lines = f.readlines()
except IndexError:
    print("Usage: python test.py <fen_file.fen> [print_board] [show_failed_fens]")
    sys.exit(1)

total_tests = len(lines)
successful_tests = 0

failed_fens = defaultdict(list)  # use a set

for line in lines:
    print("Testing FEN:", line.strip())

    board = chess.Board(line.strip())

    legal_moves = list(
        [
            move.uci() for move in board.pseudo_legal_moves
        ]  # remove check/checkmate [FOR NOW]
    )

    print("\n")

    cmd = ["./chess_engine", line.strip()]
    if printBoardAfterFenLoad:
        cmd.append(printBoardAfterFenLoad)
    result = subprocess.run(cmd, capture_output=True, text=True)

    # print c++ board output if requested
    if printBoardAfterFenLoad:
        print("C++ Chess Engine Board State:")
        print(result.stdout.split("-")[1].split("-")[0])

    cpp_result = result.stdout.split("START")[1].split("END")[0].strip().splitlines()

    # compare the results

    passed = True

    print("Comparing legal moves from Python and C++ outputs...")

    for move in legal_moves:
        print("Python Move:", move)
        if move in cpp_result:
            print("\x1b[92mMatch found in C++ output.\x1b[0m")
        else:
            print("\x1b[91mNo match found in C++ output.\x1b[0m")
            passed = False
            if "Python move not found in C++ output" not in failed_fens[line.strip()]:
                failed_fens[line.strip()].append("Python move not found in C++ output")

    print("\n")

    for move in cpp_result:
        print("C++ Move:", move)
        if move in legal_moves:
            print("\x1b[92mMatch found in Python output.\x1b[0m")
        else:
            print("\x1b[91mNo match found in Python output.\x1b[0m")
            passed = False
            if "C++ move not found in Python output" not in failed_fens[line.strip()]:
                failed_fens[line.strip()].append("C++ move not found in Python output")

    print("\n")

    # use ansi for green/red text
    if passed:
        print("\x1b[92mAll legal moves match between Python and C++ outputs.\x1b[0m")
        successful_tests += 1
    else:
        print(
            "\x1b[91mSome legal moves do not match between Python and C++ outputs.\x1b[0m"
        )

    print("--------------------------------------------------\n")


print(f"Test Results: {successful_tests}/{total_tests} tests passed.")

if failed_fens and showFailedFens:
    for fen, issues in failed_fens.items():
        print(f"FEN: {fen} - Issues:\n {'; '.join(issues)}")
