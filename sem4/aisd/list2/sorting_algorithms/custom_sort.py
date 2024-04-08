from typing import List, Tuple
import argparse
import sys

from sorting_analyzer import SortingAnalyzer

CUSTOM_SORT_COMPARISONS = 0
CUSTOM_SORT_SWAPS = 0

MIN_MERGE = 32


def reset_counters_c():
    global CUSTOM_SORT_COMPARISONS, CUSTOM_SORT_SWAPS
    CUSTOM_SORT_COMPARISONS = 0
    CUSTOM_SORT_SWAPS = 0


def calculate_min_run(arr_length: int) -> int:
    remainder = 0
    while arr_length >= MIN_MERGE:
        remainder |= arr_length & 1
        arr_length >>= 1
    return arr_length + remainder


def custom_sort(arr: List[int]) -> Tuple[int, int]:
    global CUSTOM_SORT_COMPARISONS, CUSTOM_SORT_SWAPS
    arr_length = len(arr)
    min_run = calculate_min_run(arr_length)
    for i in range(0, arr_length, min_run):
        c_insertion_sort(arr, i, min(i + min_run - 1, arr_length - 1))
    SortingAnalyzer.print_text(f"After insertion sort {arr}")

    merged_array_size = min_run
    while merged_array_size < arr_length:
        for left in range(0, arr_length, 2 * merged_array_size):
            mid = min(left + merged_array_size - 1, arr_length - 1)
            right = min(left + 2 * merged_array_size - 1, arr_length - 1)
            merge(arr, left, mid, right)
            SortingAnalyzer.print_text(f"After merge {arr}")

        merged_array_size *= 2

    return CUSTOM_SORT_COMPARISONS, CUSTOM_SORT_SWAPS


def c_insertion_sort(arr: List[int], low: int, high: int) -> None:
    global CUSTOM_SORT_COMPARISONS, CUSTOM_SORT_SWAPS
    for i in range(low, high + 1):
        key = arr[i]
        j = i - 1
        while j >= low and arr[j] > key:
            CUSTOM_SORT_COMPARISONS += 1
            CUSTOM_SORT_SWAPS += 1
            arr[j + 1] = arr[j]
            j -= 1
        CUSTOM_SORT_COMPARISONS += 1
        CUSTOM_SORT_SWAPS += 1
        arr[j + 1] = key


def merge(arr: List[int], left: int, mid: int, right: int) -> None:
    global CUSTOM_SORT_COMPARISONS, CUSTOM_SORT_SWAPS
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
        CUSTOM_SORT_COMPARISONS += 1
        CUSTOM_SORT_SWAPS += 1
        merged_index += 1

    while left_index < left_arr_size:
        arr[merged_index] = left_arr[left_index]
        CUSTOM_SORT_SWAPS += 1
        left_index += 1
        merged_index += 1
    while right_index < right_arr_size:
        arr[merged_index] = right_arr[right_index]
        CUSTOM_SORT_SWAPS += 1
        right_index += 1
        merged_index += 1


def main() -> None:
    parser = argparse.ArgumentParser("Hybrid sort")
    parser.add_argument("arr_to_sort", nargs="*", type=int)
    args = parser.parse_args()

    if not sys.stdin.isatty():
        arr_from_stdin = [int(x) for x in sys.stdin.read().strip().split()]
        args.arr_to_sort.extend(arr_from_stdin)

    SortingAnalyzer.set_and_print_input_arr(args.arr_to_sort)
    custom_sort(args.arr_to_sort)
    SortingAnalyzer.print_results(CUSTOM_SORT_COMPARISONS, CUSTOM_SORT_SWAPS)


if __name__ == "__main__":
    main()
