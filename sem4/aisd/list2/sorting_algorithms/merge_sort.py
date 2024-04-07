from typing import List, Tuple
import argparse
import sys

from sorting_analyzer import SortingAnalyzer

MERGE_SORT_COMPARISONS = 0
MERGE_SORT_SWAPS = 0


def reset_counters_m():
    global MERGE_SORT_COMPARISONS, MERGE_SORT_SWAPS
    MERGE_SORT_COMPARISONS = 0
    MERGE_SORT_SWAPS = 0


def merge_sort(arr: List[int], left: int, right: int) -> Tuple[int, int]:
    global MERGE_SORT_COMPARISONS, MERGE_SORT_SWAPS
    if left < right:
        mid = (left + right) // 2

        merge_sort(arr, left, mid)
        merge_sort(arr, mid + 1, right)
        merge(arr, left, mid, right)

    return MERGE_SORT_COMPARISONS, MERGE_SORT_SWAPS


def merge(arr: List[int], left: int, mid: int, right: int) -> None:
    global MERGE_SORT_COMPARISONS, MERGE_SORT_SWAPS
    left_arr_size = mid - left + 1
    right_arr_size = right - mid

    left_arr = arr[left : mid + 1]
    right_arr = arr[mid + 1 : right + 1]

    left_index, right_index, merged_index = 0, 0, left

    while left_index < left_arr_size and right_index < right_arr_size:
        if left_arr[left_index] <= right_arr[right_index]:
            arr[merged_index] = left_arr[left_index]
            left_index += 1
        else:
            arr[merged_index] = right_arr[right_index]
            right_index += 1
        MERGE_SORT_COMPARISONS += 1
        MERGE_SORT_SWAPS += 1
        merged_index += 1

    while left_index < left_arr_size:
        arr[merged_index] = left_arr[left_index]
        MERGE_SORT_SWAPS += 1
        left_index += 1
        merged_index += 1
    while right_index < right_arr_size:
        arr[merged_index] = right_arr[right_index]
        MERGE_SORT_SWAPS += 1
        right_index += 1
        merged_index += 1


def main() -> None:
    parser = argparse.ArgumentParser("Insertion sort")
    parser.add_argument("arr_to_sort", nargs="*", type=int)
    args = parser.parse_args()

    if not sys.stdin.isatty():
        arr_from_stdin = [int(x) for x in sys.stdin.read().strip().split()]
        args.arr_to_sort.extend(arr_from_stdin)

    SortingAnalyzer.set_and_print_input_arr(args.arr_to_sort)
    merge_sort(args.arr_to_sort, 0, len(args.arr_to_sort) - 1)
    SortingAnalyzer.print_results(MERGE_SORT_COMPARISONS, MERGE_SORT_SWAPS)


if __name__ == "__main__":
    main()
