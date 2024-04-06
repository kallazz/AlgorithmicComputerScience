import matplotlib.pyplot as plt
import numpy as np

from insertion_sort import insertion_sort, reset_counters_i
from quick_sort import quick_sort, reset_counters_q
from hybrid_sort import hybrid_sort, reset_counters_h
from list_generator import generate_random_list

PLOTS_DIR = "./plots"


def plot_data(
    comparisons_data: np.ndarray,
    moves_data: np.ndarray,
    k: int,
    start: int,
    end: int,
    increment: int,
    without_insertion_sort: bool,
) -> None:
    if not without_insertion_sort:
        algorithms = ["Quick Sort", "Hybrid Sort", "Insertion Sort"]
    else:
        algorithms = ["Quick Sort", "Hybrid Sort"]

    plt.figure(figsize=(10, 5))
    plt.subplot(1, 2, 1)
    for n in range(len(comparisons_data)):
        plt.plot(
            range(start, end + 1, increment),
            comparisons_data[n],
            marker="o",
            label=algorithms[n],
        )
    plt.xlabel("Array Size")
    plt.ylabel("Average Comparisons")
    plt.title(f"Sorting - Average Comparisons, k={k}")
    plt.legend()
    without_insertion_sort_text = "without_insertion_sort_" if without_insertion_sort else ""
    plt.savefig(f"{PLOTS_DIR}/comparisons_{without_insertion_sort_text}{k}.png")

    plt.figure(figsize=(10, 5))
    plt.subplot(1, 2, 1)
    for n in range(len(moves_data)):
        plt.plot(
            range(start, end + 1, increment),
            moves_data[n],
            marker="o",
            label=algorithms[n],
        )
    plt.xlabel("Array Size")
    plt.ylabel("Average Moves")
    plt.title(f"Sorting - Average Moves, k={k}")
    plt.legend()
    without_insertion_sort_text = "without_insertion_sort_" if without_insertion_sort else ""
    plt.savefig(f"{PLOTS_DIR}/moves_{without_insertion_sort_text}{k}.png")

def run_experiment(
    start: int, end: int, increment: int, without_insertion_sort: bool
) -> None:
    range_size = int(((end - start) / increment) + 1)
    if not without_insertion_sort:
        algorithms_amount = 3
    else:
        algorithms_amount = 2
    average_comparisons = np.zeros((algorithms_amount, range_size))
    average_moves = np.zeros((algorithms_amount, range_size))

    for k in (1, 10, 100):
        for index, n in enumerate(range(start, end + 1, increment)):
            print(f"k={k}, n={n}")
            for tester in range(k):
                arr = generate_random_list(n)

                comparisons, swaps = quick_sort(arr.copy(), 0, len(arr) - 1)
                if tester == k - 1:
                    average_comparisons[0][index] += comparisons
                    average_moves[0][index] += swaps
                    reset_counters_q()

                comparisons, swaps = hybrid_sort(arr.copy(), 0, len(arr) - 1, switch=n//2)
                if tester == k - 1:
                    average_comparisons[1][index] += comparisons
                    average_moves[1][index] += swaps
                    reset_counters_h()

                if not without_insertion_sort:
                    comparisons, swaps = insertion_sort(arr.copy())
                    if tester == k - 1:
                        average_comparisons[2][index] += comparisons
                        average_moves[2][index] += swaps
                        reset_counters_i()

        comparisons_data = [comparison / k for comparison in average_comparisons]
        moves_data = [move / k for move in average_moves]
        plot_data(
            comparisons_data,
            moves_data,
            k,
            start,
            end,
            increment,
            without_insertion_sort,
        )


def main() -> None:
    #SortingAnalyzer.initialize(generate_random_list(40))
    run_experiment(10, 50, 10, without_insertion_sort=False)
    run_experiment(1000, 50000, 1000, without_insertion_sort=True)


if __name__ == "__main__":
    main()
