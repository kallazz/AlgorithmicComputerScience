from typing import List

class SortingAnalyzer:
    comparisons = 0
    moves = 0
    input_arr = []
    arr = []

    @staticmethod
    def initialize(input_arr: List[int] = []):
        SortingAnalyzer.comparisons = 0
        SortingAnalyzer.moves = 0
        SortingAnalyzer.input_arr = input_arr.copy()
        SortingAnalyzer.arr = input_arr

    @staticmethod
    def set_and_print_input_arr(input_arr: List[int]) -> None:
        SortingAnalyzer.input_arr = input_arr.copy()
        SortingAnalyzer.arr = input_arr
        if len(SortingAnalyzer.input_arr) < 40:
            print(f"Input array: {input_arr}")

    @staticmethod
    def compare_elements(comparison: bool) -> bool:
        SortingAnalyzer.comparisons += 1
        return comparison

    @staticmethod
    def move_element(arr: List[int], index: int, element: int) -> None:
        SortingAnalyzer.moves += 1
        arr[index] = element

    @staticmethod
    def swap_elements(arr: List[int], index1: int, index2: int) -> None:
        SortingAnalyzer.moves += 1
        arr[index1], arr[index2] = arr[index2], arr[index1]

    @staticmethod
    def print_text(text: str) -> None:
        if len(SortingAnalyzer.input_arr) < 40:
            print(text)

    @staticmethod
    def print_results() -> None:
        if len(SortingAnalyzer.input_arr) < 40:
            print(f"Input array again: {SortingAnalyzer.input_arr}")
            print(f"Sorted array: {SortingAnalyzer.arr}")
        print(f"Number of comparisons: {SortingAnalyzer.comparisons}")
        print(f"Number of moves: {SortingAnalyzer.moves}")
