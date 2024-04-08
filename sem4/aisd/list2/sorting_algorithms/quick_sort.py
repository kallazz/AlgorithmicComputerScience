from typing import List, Tuple
import argparse
import sys

from sorting_analyzer import SortingAnalyzer

QUICK_SORT_COMPARISONS = 0
QUICK_SORT_SWAPS = 0


def reset_counters_q():
    global QUICK_SORT_COMPARISONS, QUICK_SORT_SWAPS
    QUICK_SORT_COMPARISONS = 0
    QUICK_SORT_SWAPS = 0


def partition(arr: List[int], low: int, high: int) -> int:
    global QUICK_SORT_COMPARISONS, QUICK_SORT_SWAPS
    pivot = arr[high]
    i = low - 1

    for j in range(low, high + 1):
        if arr[j] < pivot:
            QUICK_SORT_SWAPS += 1
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
        QUICK_SORT_COMPARISONS += 1
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    QUICK_SORT_SWAPS += 1

    SortingAnalyzer.print_text(f"After partition {arr}")
    return i + 1


def quick_sort(arr: List[int], low: int, high: int) -> Tuple[int, int]:
    if low >= high:
        return QUICK_SORT_COMPARISONS, QUICK_SORT_SWAPS

    pivot_index = partition(arr, low, high)
    quick_sort(arr, low, pivot_index - 1)
    quick_sort(arr, pivot_index + 1, high)

    return QUICK_SORT_COMPARISONS, QUICK_SORT_SWAPS


def main() -> None:
    parser = argparse.ArgumentParser("Quick sort")
    parser.add_argument("arr_to_sort", nargs="*", type=int)
    args = parser.parse_args()

    if not sys.stdin.isatty():
        arr_from_stdin = [int(x) for x in sys.stdin.read().strip().split()]
        args.arr_to_sort.extend(arr_from_stdin)

    SortingAnalyzer.set_and_print_input_arr(args.arr_to_sort)
    quick_sort(args.arr_to_sort, 0, len(args.arr_to_sort) - 1)
    SortingAnalyzer.print_results(QUICK_SORT_COMPARISONS, QUICK_SORT_SWAPS)


if __name__ == "__main__":
    main()
