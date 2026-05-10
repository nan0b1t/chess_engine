import chess
import subprocess
import sys

args = sys.argv[1]
printBoardAfterFenLoad = sys.argv[2] if len(sys.argv) > 2 else None

with open(args, 'r') as f:
    lines = f.readlines()

total_tests = len(lines)
successful_tests = 0

for line in lines:

    print("Testing FEN:", line.strip())

    board = chess.Board(line.strip())

    legal_moves = list([board.san(move) for move in board.legal_moves])

    
    print("\n")


    cmd = ['./chess_engine', line.strip()]
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
            print("Match found in C++ output.")
        else:
            print("No match found in C++ output.")
            passed = False

    print("\n")

    for move in cpp_result:
        print("C++ Move:", move)
        if move in legal_moves:
            print("Match found in Python output.")
        else:
            print("No match found in Python output.")
            passed = False
    
    print("\n")
    
    # use ansi for green/red text
    if passed:
        print("\x1b[92mAll legal moves match between Python and C++ outputs.\x1b[0m")
        successful_tests += 1
    else:
        print("\x1b[91mSome legal moves do not match between Python and C++ outputs.\x1b[0m")
    
    print("--------------------------------------------------\n")


print(f"Test Results: {successful_tests}/{total_tests} tests passed.")