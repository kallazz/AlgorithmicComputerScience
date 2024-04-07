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

def partition(arr: List[int], start: int, end: int) -> int:
    global QUICK_SORT_COMPARISONS, QUICK_SORT_SWAPS
    pivot = arr[end]
    i = start - 1

    for j in range(start, end + 1):
        if (arr[j] < pivot):
            QUICK_SORT_SWAPS += 1
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
        QUICK_SORT_COMPARISONS += 1
    arr[i + 1], arr[end] = arr[end], arr[i + 1]
    QUICK_SORT_SWAPS += 1

    #SortingAnalyzer.print_text(f"After partition {arr}")
    return i + 1

def quick_sort(arr: List[int], start: int, end: int) -> Tuple[int, int]:
    if start >= end:
        return

    pivot_index = partition(arr, start, end)
    quick_sort(arr, start, pivot_index - 1)
    quick_sort(arr, pivot_index + 1, end)

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