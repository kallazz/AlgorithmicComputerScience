from typing import List, Tuple
import argparse
import sys

from sorting_analyzer import SortingAnalyzer

INSERTION_SORT_COMPARISONS = 0
INSERTION_SORT_SWAPS = 0

def reset_counters_i():
    global INSERTION_SORT_COMPARISONS, INSERTION_SORT_SWAPS
    INSERTION_SORT_COMPARISONS = 0
    INSERTION_SORT_SWAPS = 0

def insertion_sort(arr: List[int]) -> Tuple[int, int]:
    global INSERTION_SORT_COMPARISONS, INSERTION_SORT_SWAPS
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            INSERTION_SORT_COMPARISONS += 1
            INSERTION_SORT_SWAPS += 1
            arr[j + 1] = arr[j]
            j -= 1
        INSERTION_SORT_COMPARISONS += 1
        INSERTION_SORT_SWAPS += 1
        arr[j + 1] = key
        #SortingAnalyzer.print_text(f"After iteration {arr}")

    return INSERTION_SORT_COMPARISONS, INSERTION_SORT_SWAPS


def main() -> None:
    parser = argparse.ArgumentParser("Insertion sort")
    parser.add_argument("arr_to_sort", nargs="*", type=int)
    args = parser.parse_args()

    if not sys.stdin.isatty():
        arr_from_stdin = [int(x) for x in sys.stdin.read().strip().split()]
        args.arr_to_sort.extend(arr_from_stdin)

    SortingAnalyzer.set_and_print_input_arr(args.arr_to_sort)
    insertion_sort(args.arr_to_sort)
    SortingAnalyzer.print_results(INSERTION_SORT_COMPARISONS, INSERTION_SORT_SWAPS)

if __name__ == "__main__":
    main()