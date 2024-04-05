from typing import List
import argparse
import sys

from sorting_analyzer import SortingAnalyzer

def h_insertion_sort(arr: List[int]) -> None:
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and SortingAnalyzer.compare_elements(arr[j] > key):
            SortingAnalyzer.move_element(arr, j + 1, arr[j])
            j -= 1
        SortingAnalyzer.move_element(arr, j + 1, key)
        SortingAnalyzer.print_text(f"After iteration {arr}")

def partition(arr: List[int], start: int, end: int) -> int:
    pivot = arr[end]
    i = start - 1

    for j in range(start, end + 1):
        if (SortingAnalyzer.compare_elements(arr[j] < pivot)):
            i += 1
            SortingAnalyzer.swap_elements(arr, i, j)
    SortingAnalyzer.swap_elements(arr, i + 1, end)

    SortingAnalyzer.print_text(f"After partition {arr}")
    return i + 1

def hybrid_sort(arr: List[int], start: int, end: int) -> None:
    if start >= end:
        return

    if end - start + 1 < 2:
        h_insertion_sort(arr)
    else:
        pivot_index = partition(arr, start, end)
        hybrid_sort(arr, start, pivot_index - 1)
        hybrid_sort(arr, pivot_index + 1, end)

def main() -> None:
    parser = argparse.ArgumentParser("Hybrid sort")
    parser.add_argument("arr_to_sort", nargs="*", type=int)
    args = parser.parse_args()

    if not sys.stdin.isatty():
        arr_from_stdin = [int(x) for x in sys.stdin.read().strip().split()]
        args.arr_to_sort.extend(arr_from_stdin)

    SortingAnalyzer.set_and_print_input_arr(args.arr_to_sort)
    hybrid_sort(args.arr_to_sort, 0, len(args.arr_to_sort) - 1)
    SortingAnalyzer.print_results()

if __name__ == "__main__":
    main()