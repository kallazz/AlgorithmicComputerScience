import matplotlib.pyplot as plt
import numpy as np
from typing import List

from sorting_algorithms.custom_sort import custom_sort, reset_counters_c
from sorting_algorithms.insertion_sort import insertion_sort, reset_counters_i
from sorting_algorithms.quick_sort import quick_sort, reset_counters_q
from sorting_algorithms.hybrid_sort import hybrid_sort, reset_counters_h
from sorting_algorithms.merge_sort import merge_sort, reset_counters_m
from list_generator import generate_random_list

PLOTS_DIR = "./plots"
ALGORITHMS_TO_CHECK_AMOUNT = 5


def plot_data(
    average_comparisons: np.ndarray,
    average_swaps: np.ndarray,
    k: int,
    start: int,
    end: int,
    increment: int,
    algorithm_names: List[str],
    is_big_n: bool,
    is_over_n: bool,
    filename_addition: str = "",
) -> None:
    over_n_text = " / n" if is_over_n else ""
    big_n_filename_text = "big_n_" if is_big_n else ""
    over_n_filename_text = "over_n_" if is_over_n else ""
    filename_addition = (
        f"{filename_addition}_" if filename_addition else filename_addition
    )

    algorithm_names = [name + over_n_text for name in algorithm_names]

    plt.figure(figsize=(15, 5))
    plt.subplot(1, 2, 1)
    plt.grid(True, linestyle="--", zorder=0)
    for n in range(len(average_comparisons)):
        plt.plot(
            range(start, end + 1, increment),
            average_comparisons[n],
            label=algorithm_names[n],
        )
    plt.xlabel("Array Size (n)")
    plt.ylabel(f"Average Comparisons (c){over_n_text}")
    plt.title(f"Sorting - Average Comparisons{over_n_text}, k={k}")
    plt.legend()
    plt.savefig(
        f"{PLOTS_DIR}/comparisons_{filename_addition}{big_n_filename_text}{over_n_filename_text}{k}.png"
    )

    plt.figure(figsize=(10, 5))
    plt.subplot(1, 2, 1)
    plt.grid(True, linestyle="--", zorder=0)
    for n in range(len(average_swaps)):
        plt.plot(
            range(start, end + 1, increment),
            average_swaps[n],
            label=algorithm_names[n],
        )
    plt.xlabel("Array Size (n)")
    plt.ylabel(f"Average Swaps (s){over_n_text}")
    plt.title(f"Sorting - Average Swaps{over_n_text}, k={k}")
    plt.legend()
    plt.savefig(
        f"{PLOTS_DIR}/swaps_{filename_addition}{big_n_filename_text}{over_n_filename_text}{k}.png"
    )


def run_experiment(start: int, end: int, increment: int, is_big_n: bool) -> None:
    range_size = int(((end - start) / increment) + 1)
    comparison_sums = np.zeros((ALGORITHMS_TO_CHECK_AMOUNT, range_size))
    swap_sums = np.zeros((ALGORITHMS_TO_CHECK_AMOUNT, range_size))
    comparison_sums_over_n = np.zeros((ALGORITHMS_TO_CHECK_AMOUNT, range_size))
    swap_sums_over_n = np.zeros((ALGORITHMS_TO_CHECK_AMOUNT, range_size))

    for k in (1, 10, 100):
        for index, n in enumerate(range(start, end + 1, increment)):
            print(f"k={k}, n={n}")
            for k_counter in range(k):
                arr = generate_random_list(n)
                '''
                comparisons, swaps = quick_sort(arr.copy(), 0, len(arr) - 1)
                if k_counter == k - 1:
                    comparison_sums[0][index] += comparisons
                    swap_sums[0][index] += swaps
                    comparison_sums_over_n[0][index] += comparisons / n
                    swap_sums_over_n[0][index] += swaps / n
                    reset_counters_q()

                # switch 1000 -> wolno, switch 100 -> całkiem wolno, switch 10 - OK
                comparisons, swaps = hybrid_sort(arr.copy(), 0, len(arr) - 1, switch=10)
                if k_counter == k - 1:
                    comparison_sums[1][index] += comparisons
                    swap_sums[1][index] += swaps
                    comparison_sums_over_n[1][index] += comparisons / n
                    swap_sums_over_n[1][index] += swaps / n
                    reset_counters_h()

                if not is_big_n:
                    comparisons, swaps = insertion_sort(arr.copy())
                    if k_counter == k - 1:
                        comparison_sums[2][index] += comparisons
                        swap_sums[2][index] += swaps
                        comparison_sums_over_n[2][index] += comparisons / n
                        swap_sums_over_n[2][index] += swaps / n
                        reset_counters_i()
                '''
                comparisons, swaps = merge_sort(arr.copy(), 0, len(arr) - 1)
                if k_counter == k - 1:
                    comparison_sums[3][index] += comparisons
                    swap_sums[3][index] += swaps
                    comparison_sums_over_n[3][index] += comparisons / n
                    swap_sums_over_n[3][index] += swaps / n
                    reset_counters_m()

                comparisons, swaps = custom_sort(arr.copy())
                if k_counter == k - 1:
                    comparison_sums[4][index] += comparisons
                    swap_sums[4][index] += swaps
                    comparison_sums_over_n[4][index] += comparisons / n
                    swap_sums_over_n[4][index] += swaps / n
                    reset_counters_c()

        average_comparisons = [comparison / k for comparison in comparison_sums]
        average_comparisons_over_n = [
            comparison / k for comparison in comparison_sums_over_n
        ]
        average_swaps = [swap / k for swap in swap_sums]
        average_swaps_over_n = [swap / k for swap in swap_sums_over_n]
        '''
        plot_data(
            average_comparisons[0:3] if not is_big_n else average_comparisons[0:2],
            average_swaps[0:3] if not is_big_n else average_swaps[0:2],
            k,
            start,
            end,
            increment,
            algorithm_names=(
                ["Quick Sort", "Hybrid Sort", "Insertion Sort"]
                if not is_big_n
                else ["Quick Sort", "Hybrid Sort"]
            ),
            is_big_n=is_big_n,
            is_over_n=False,
        )
        plot_data(
            (
                average_comparisons_over_n[0:3]
                if not is_big_n
                else average_comparisons_over_n[0:2]
            ),
            average_swaps_over_n[0:3] if not is_big_n else average_swaps_over_n[0:2],
            k,
            start,
            end,
            increment,
            algorithm_names=(
                ["Quick Sort", "Hybrid Sort", "Insertion Sort"]
                if not is_big_n
                else ["Quick Sort", "Hybrid Sort"]
            ),
            is_big_n=is_big_n,
            is_over_n=True,
        )
        '''
        plot_data(
            average_comparisons[3:5],
            average_swaps[3:5],
            k,
            start,
            end,
            increment,
            algorithm_names=["Merge Sort", "Custom Sort"],
            is_big_n=is_big_n,
            is_over_n=False,
            filename_addition="merge_custom",
        )
        plot_data(
            average_comparisons_over_n[3:5],
            average_swaps_over_n[3:5],
            k,
            start,
            end,
            increment,
            algorithm_names=["Merge Sort", "Custom Sort"],
            is_big_n=is_big_n,
            is_over_n=True,
            filename_addition="merge_custom",
        )


def main() -> None:
    run_experiment(10, 50, 10, is_big_n=False)
    run_experiment(1000, 50000, 1000, is_big_n=True)


if __name__ == "__main__":
    main()
