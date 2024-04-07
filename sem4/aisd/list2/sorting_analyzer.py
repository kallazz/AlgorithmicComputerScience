from typing import List


class SortingAnalyzer:
    input_arr = []
    arr = []

    @staticmethod
    def set_and_print_input_arr(input_arr: List[int]) -> None:
        SortingAnalyzer.input_arr = input_arr.copy()
        SortingAnalyzer.arr = input_arr
        if len(SortingAnalyzer.input_arr) < 40:
            print(f"Input array: {input_arr}")

    @staticmethod
    def print_text(text: str) -> None:
        if len(SortingAnalyzer.input_arr) < 40:
            print(text)

    @staticmethod
    def print_results(comparisons: int, swaps: int) -> None:
        if len(SortingAnalyzer.input_arr) < 40:
            print(f"Input array again: {SortingAnalyzer.input_arr}")
            print(f"Sorted array: {SortingAnalyzer.arr}")
        print(f"Number of comparisons: {comparisons}")
        print(f"Number of moves: {swaps}")
