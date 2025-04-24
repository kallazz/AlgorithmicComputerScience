import csv
import subprocess
from pathlib import Path
from typing import Any, Generator, List, Tuple

EXECUTABLE = "./puzzleSolver"
RESULTS_DIR = Path("results")
SIZES = [3, 4]
MOVE_SETTINGS = [20, 0]
RUNS_PER_CASE = 10

RESULTS_DIR.mkdir(exist_ok=True)


def run_test(size: int, moves_count: int, test_index: int) -> Generator[Tuple[str, List], None, None]:
    args = [EXECUTABLE, str(size), str(moves_count)]
    if size == 4 and moves_count == 0:
        args.append("--ignore-misplaced")

    result = subprocess.run(args, capture_output=True, text=True, check=True)
    output = result.stdout
    for section in output.split("\n\n"):
        if section.startswith("Solving with"):
            lines = section.splitlines()
            heuristic = lines[0].split("with ")[1].strip().replace(" ", "_").lower()
            moves_line = next(line for line in lines if line.startswith("Amount of moves"))
            nodes_line = next(line for line in lines if line.startswith("Nodes visited"))
            time_line = next(line for line in lines if line.startswith("Time taken"))
            moves = int(moves_line.split(":")[1].strip())
            nodes = int(nodes_line.split(":")[1].strip())
            time_taken = float(time_line.split(":")[1].strip().split()[0])
            yield heuristic, [test_index, moves, nodes, time_taken]


def calculate_averages(results: List[Any]) -> Tuple[float, float, float]:
    total_moves = 0
    total_nodes = 0
    total_time = 0.0
    count = len(results)

    for result in results:
        total_moves += result[1]
        total_nodes += result[2]
        total_time += result[3]

    avg_moves = total_moves / count if count > 0 else 0
    avg_nodes = total_nodes / count if count > 0 else 0
    avg_time = total_time / count if count > 0 else 0.0

    return avg_moves, avg_nodes, avg_time


def write_results_to_csv(size: int, moves_count: int, all_results) -> None:
    for heuristic, results in all_results.items():
        filename = RESULTS_DIR / f"{size}x{size}_moves{moves_count}_{heuristic}.csv"
        with open(filename, mode="w", newline="") as csvfile:
            writer = csv.writer(csvfile)
            writer.writerow(["Test Index", "Amount of Moves", "Nodes Visited", "Time Taken (s)"])
            writer.writerows(results)

            avg_moves, avg_nodes, avg_time = calculate_averages(results)
            writer.writerow(["Average", avg_moves, avg_nodes, avg_time])


def main() -> None:
    total_tests = len(SIZES) * len(MOVE_SETTINGS) * RUNS_PER_CASE
    completed_tests = 0

    for size in SIZES:
        for moves_count in MOVE_SETTINGS:
            all_results = {}
            for i in range(1, RUNS_PER_CASE + 1):
                for heuristic, result in run_test(size, moves_count, i):
                    all_results.setdefault(heuristic, []).append(result)
                completed_tests += 1
                print(f"Completed {completed_tests}/{total_tests} tests")
            write_results_to_csv(size, moves_count, all_results)


if __name__ == "__main__":
    main()
