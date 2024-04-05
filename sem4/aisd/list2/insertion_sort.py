from typing import List
import argparse
import sys

from sorting_analyzer import SortingAnalyzer

def insertion_sort(arr: List[int]) -> None:
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and SortingAnalyzer.compare_elements(arr[j] > key):
            SortingAnalyzer.move_element(arr, j + 1, arr[j])
            j -= 1
        SortingAnalyzer.move_element(arr, j + 1, key)
        SortingAnalyzer.print_text(f"After iteration {arr}")


def main() -> None:
    parser = argparse.ArgumentParser("Insertion sort")
    parser.add_argument("arr_to_sort", nargs="*", type=int)
    args = parser.parse_args()

    if not sys.stdin.isatty():
        arr_from_stdin = [int(x) for x in sys.stdin.read().strip().split()]
        args.arr_to_sort.extend(arr_from_stdin)

    SortingAnalyzer.set_and_print_input_arr(args.arr_to_sort)
    insertion_sort(args.arr_to_sort)
    SortingAnalyzer.print_results()

if __name__ == "__main__":
    main()