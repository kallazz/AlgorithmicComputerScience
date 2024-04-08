from typing import List, Tuple
import argparse
import sys

from sorting_analyzer import SortingAnalyzer

HYBRID_SORT_COMPARISONS = 0
HYBRID_SORT_SWAPS = 0


def reset_counters_h():
    global HYBRID_SORT_COMPARISONS, HYBRID_SORT_SWAPS
    HYBRID_SORT_COMPARISONS = 0
    HYBRID_SORT_SWAPS = 0


def h_insertion_sort(arr: List[int], low: int, high: int) -> None:
    global HYBRID_SORT_COMPARISONS, HYBRID_SORT_SWAPS
    for i in range(low, high + 1):
        key = arr[i]
        j = i - 1
        while j >= low and arr[j] > key:
            HYBRID_SORT_COMPARISONS += 1
            HYBRID_SORT_SWAPS += 1
            arr[j + 1] = arr[j]
            j -= 1
        HYBRID_SORT_COMPARISONS += 1
        HYBRID_SORT_SWAPS += 1
        arr[j + 1] = key


def partition(arr: List[int], low: int, high: int) -> int:
    global HYBRID_SORT_COMPARISONS, HYBRID_SORT_SWAPS
    pivot = arr[high]
    i = low - 1

    for j in range(low, high + 1):
        if arr[j] < pivot:
            HYBRID_SORT_SWAPS += 1
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
        HYBRID_SORT_COMPARISONS += 1
    HYBRID_SORT_SWAPS += 1
    arr[i + 1], arr[high] = arr[high], arr[i + 1]

    SortingAnalyzer.print_text(f"After partition {arr}")
    return i + 1


def hybrid_sort(
    arr: List[int], low: int, high: int, switch: int = 10
) -> Tuple[int, int]:
    while low < high:
        if high - low + 1 < switch:
            h_insertion_sort(arr, low, high)
            break
        else:
            pivot_index = partition(arr, low, high)
            if pivot_index - low < high - pivot_index:
                hybrid_sort(arr, low, pivot_index - 1, switch)
                low = pivot_index + 1
            else:
                hybrid_sort(arr, pivot_index + 1, high, switch)
                high = pivot_index - 1

    return HYBRID_SORT_COMPARISONS, HYBRID_SORT_SWAPS


def main() -> None:
    parser = argparse.ArgumentParser("Hybrid sort")
    parser.add_argument("arr_to_sort", nargs="*", type=int)
    args = parser.parse_args()

    if not sys.stdin.isatty():
        arr_from_stdin = [int(x) for x in sys.stdin.read().strip().split()]
        args.arr_to_sort.extend(arr_from_stdin)

    SortingAnalyzer.set_and_print_input_arr(args.arr_to_sort)
    hybrid_sort(args.arr_to_sort, 0, len(args.arr_to_sort) - 1)
    SortingAnalyzer.print_results(HYBRID_SORT_COMPARISONS, HYBRID_SORT_SWAPS)


if __name__ == "__main__":
    main()
