from typing import List, Tuple
import argparse
import sys

from sorting_analyzer import SortingAnalyzer

DUAL_PIVOT_QUICKSORT_COMPARISONS = 0
DUAL_PIVOT_QUICKSORT_SWAPS = 0


def reset_counters_d():
    global DUAL_PIVOT_QUICKSORT_COMPARISONS, DUAL_PIVOT_QUICKSORT_SWAPS
    DUAL_PIVOT_QUICKSORT_COMPARISONS = 0
    DUAL_PIVOT_QUICKSORT_SWAPS = 0


def partition(arr: List[int], low: int, high: int) -> Tuple[int, int]:
    global DUAL_PIVOT_QUICKSORT_COMPARISONS, DUAL_PIVOT_QUICKSORT_SWAPS
    if arr[low] > arr[high]:
        arr[low], arr[high] = arr[high], arr[low]
        DUAL_PIVOT_QUICKSORT_SWAPS += 1
    DUAL_PIVOT_QUICKSORT_COMPARISONS += 1
    less_than_left_pivot_index = arr_index = low + 1
    more_than_right_pivot_index = high - 1
    left_pivot, right_pivot = arr[low], arr[high]

    while arr_index <= more_than_right_pivot_index:
        if arr[arr_index] < left_pivot:
            arr[arr_index], arr[less_than_left_pivot_index] = (
                arr[less_than_left_pivot_index],
                arr[arr_index],
            )
            DUAL_PIVOT_QUICKSORT_SWAPS += 1
            less_than_left_pivot_index += 1
        elif arr[arr_index] >= right_pivot:
            while (
                arr[more_than_right_pivot_index] > right_pivot
                and arr_index < more_than_right_pivot_index
            ):
                DUAL_PIVOT_QUICKSORT_COMPARISONS += 1
                more_than_right_pivot_index -= 1
            DUAL_PIVOT_QUICKSORT_COMPARISONS += 1

            arr[arr_index], arr[more_than_right_pivot_index] = (
                arr[more_than_right_pivot_index],
                arr[arr_index],
            )
            DUAL_PIVOT_QUICKSORT_SWAPS
            more_than_right_pivot_index -= 1

            if arr[arr_index] < left_pivot:
                arr[arr_index], arr[less_than_left_pivot_index] = (
                    arr[less_than_left_pivot_index],
                    arr[arr_index],
                )
                DUAL_PIVOT_QUICKSORT_SWAPS += 1
                less_than_left_pivot_index += 1
            DUAL_PIVOT_QUICKSORT_COMPARISONS += 1
        arr_index += 1
        DUAL_PIVOT_QUICKSORT_COMPARISONS += 1
    less_than_left_pivot_index -= 1
    more_than_right_pivot_index += 1

    arr[low], arr[less_than_left_pivot_index] = (
        arr[less_than_left_pivot_index],
        arr[low],
    )
    arr[high], arr[more_than_right_pivot_index] = (
        arr[more_than_right_pivot_index],
        arr[high],
    )
    DUAL_PIVOT_QUICKSORT_COMPARISONS += 2

    SortingAnalyzer.print_text(f"After partition {arr}")
    return less_than_left_pivot_index, more_than_right_pivot_index


def dual_pivot_quicksort(arr: List[int], low: int, high: int) -> Tuple[int, int]:
    global DUAL_PIVOT_QUICKSORT_COMPARISONS, DUAL_PIVOT_QUICKSORT_SWAPS
    if low < high:
        left_pivot_index, right_pivot_index = partition(arr, low, high)
        dual_pivot_quicksort(arr, low, left_pivot_index - 1)
        dual_pivot_quicksort(arr, left_pivot_index + 1, right_pivot_index - 1)
        dual_pivot_quicksort(arr, right_pivot_index + 1, high)
    return DUAL_PIVOT_QUICKSORT_COMPARISONS, DUAL_PIVOT_QUICKSORT_SWAPS


def main() -> None:
    parser = argparse.ArgumentParser("Hybrid sort")
    parser.add_argument("arr_to_sort", nargs="*", type=int)
    args = parser.parse_args()

    if not sys.stdin.isatty():
        arr_from_stdin = [int(x) for x in sys.stdin.read().strip().split()]
        args.arr_to_sort.extend(arr_from_stdin)

    SortingAnalyzer.set_and_print_input_arr(args.arr_to_sort)
    dual_pivot_quicksort(args.arr_to_sort, 0, len(args.arr_to_sort) - 1)
    SortingAnalyzer.print_results(
        DUAL_PIVOT_QUICKSORT_COMPARISONS, DUAL_PIVOT_QUICKSORT_SWAPS
    )


if __name__ == "__main__":
    main()
