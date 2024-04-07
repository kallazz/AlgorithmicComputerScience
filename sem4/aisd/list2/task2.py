import matplotlib.pyplot as plt
import numpy as np

from insertion_sort import insertion_sort, reset_counters_i
from quick_sort import quick_sort, reset_counters_q
from hybrid_sort import hybrid_sort, reset_counters_h
from list_generator import generate_random_list

PLOTS_DIR = "./plots"

def plot_data(
    average_comparisons: np.ndarray,
    average_swaps: np.ndarray,
    k: int,
    start: int,
    end: int,
    increment: int,
    is_big_n: bool,
    is_over_n: bool,
) -> None:
    if not is_big_n:
        algorithms = [
            "Quick Sort",
            "Hybrid Sort",
            "Insertion Sort",
        ]
    else:
        algorithms = [
            "Quick Sort",
            "Hybrid Sort",
        ]

    over_n_text = " / n" if is_over_n else ""
    big_n_filename_text = "big_n_" if is_big_n else ""
    over_n_filename_text = "over_n_" if is_over_n else ""

    algorithms = [algorithm + over_n_text for algorithm in algorithms]

    plt.figure(figsize=(15, 5))
    plt.subplot(1, 2, 1)
    plt.grid(True, linestyle='--', zorder=0)
    for n in range(len(average_comparisons)):
        plt.plot(
            range(start, end + 1, increment),
            average_comparisons[n],
            label=algorithms[n],
        )
    plt.xlabel("Array Size (n)")
    plt.ylabel(f"Average Comparisons (c){over_n_text}")
    plt.title(f"Sorting - Average Comparisons{over_n_text}, k={k}")
    plt.legend()
    plt.savefig(f"{PLOTS_DIR}/comparisons_{big_n_filename_text}{over_n_filename_text}{k}.png")

    plt.figure(figsize=(10, 5))
    plt.subplot(1, 2, 1)
    plt.grid(True, linestyle='--', zorder=0)
    for n in range(len(average_swaps)):
        plt.plot(
            range(start, end + 1, increment),
            average_swaps[n],
            label=algorithms[n],
        )
    plt.xlabel("Array Size (n)")
    plt.ylabel(f"Average Swaps (s){over_n_text}")
    plt.title(f"Sorting - Average Swaps{over_n_text}, k={k}")
    plt.legend()
    plt.savefig(f"{PLOTS_DIR}/swaps_{big_n_filename_text}{over_n_filename_text}{k}.png")


def run_experiment(start: int, end: int, increment: int, is_big_n: bool) -> None:
    range_size = int(((end - start) / increment) + 1)
    if not is_big_n:
        algorithms_amount = 3
    else:
        algorithms_amount = 2
    comparison_sums = np.zeros((algorithms_amount, range_size))
    swap_sums = np.zeros((algorithms_amount, range_size))
    comparison_sums_over_n = np.zeros((algorithms_amount, range_size))
    swap_sums_over_n = np.zeros((algorithms_amount, range_size))

    for k in (1, 10, 100):
        for index, n in enumerate(range(start, end + 1, increment)):
            print(f"k={k}, n={n}")
            for tester in range(k):
                arr = generate_random_list(n)

                comparisons, swaps = quick_sort(arr.copy(), 0, len(arr) - 1)
                if tester == k - 1:
                    comparison_sums[0][index] += comparisons
                    swap_sums[0][index] += swaps
                    comparison_sums_over_n[0][index] += comparisons / n
                    swap_sums_over_n[0][index] += swaps / n
                    reset_counters_q()

                # switch 1000 -> wolno, switch 100 -> całkiem wolno, switch 10 - OK
                comparisons, swaps = hybrid_sort(arr.copy(), 0, len(arr) - 1, switch=10)
                if tester == k - 1:
                    comparison_sums[1][index] += comparisons
                    swap_sums[1][index] += swaps
                    comparison_sums_over_n[1][index] += comparisons / n
                    swap_sums_over_n[1][index] += swaps / n
                    reset_counters_h()

                if not is_big_n:
                    comparisons, swaps = insertion_sort(arr.copy())
                    if tester == k - 1:
                        comparison_sums[2][index] += comparisons
                        swap_sums[2][index] += swaps
                        comparison_sums_over_n[2][index] += comparisons / n
                        swap_sums_over_n[2][index] += swaps / n
                        reset_counters_i()

        average_comparisons = [comparison / k for comparison in comparison_sums]
        average_comparisons_over_n = [comparison / k for comparison in comparison_sums_over_n]
        average_swaps = [swap / k for swap in swap_sums]
        average_swaps_over_n = [swap / k for swap in swap_sums_over_n]
        plot_data(
            average_comparisons,
            average_swaps,
            k,
            start,
            end,
            increment,
            is_big_n,
            is_over_n=False,
        )
        plot_data(
            average_comparisons_over_n,
            average_swaps_over_n,
            k,
            start,
            end,
            increment,
            is_big_n,
            is_over_n=True,
        )


def main() -> None:
    run_experiment(10, 50, 10, is_big_n=False)
    run_experiment(1000, 50000, 1000, is_big_n=True)


if __name__ == "__main__":
    main()
