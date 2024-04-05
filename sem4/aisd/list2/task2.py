import matplotlib.pyplot as plt
import numpy as np

from sorting_analyzer import SortingAnalyzer
from insertion_sort import insertion_sort
from quick_sort import quick_sort
from hybrid_sort import hybrid_sort
from list_generator import generate_random_list

def plot_comparison_moves(comparisons_data, moves_data):
    algorithms = ["Insertion Sort", "Quick Sort", "Hybrid Sort"]

    plt.figure(figsize=(10, 5))
    plt.subplot(1, 2, 1)
    for n in range(len(comparisons_data)):
        plt.plot(range(10, 51, 10), comparisons_data[n], marker="o", label=algorithms[n])
    plt.xlabel("Array Size")
    plt.ylabel("Average Comparisons")
    plt.title("Sorting - Average Comparisons")
    plt.legend()
    plt.savefig("comparisons.png")

    plt.figure(figsize=(10, 5))
    plt.subplot(1, 2, 1)
    for n in range(len(moves_data)):
        plt.plot(range(10, 51, 10), moves_data[n], marker="o", label=algorithms[n])
    plt.xlabel("Array Size")
    plt.ylabel("Average Moves")
    plt.title("Sorting - Average Moves")
    plt.legend()
    plt.savefig("moves.png")

def main() -> None:
    average_comparisons = np.zeros((3, 5))
    average_moves = np.zeros((3, 5))

    for index, n in enumerate(range(10, 51, 10)):
        arr = generate_random_list(n)
        SortingAnalyzer.initialize(arr)
        insertion_sort(arr)
        average_comparisons[0][index] = SortingAnalyzer.comparisons
        average_moves[0][index] = SortingAnalyzer.moves

        arr = generate_random_list(n)
        SortingAnalyzer.initialize(arr)
        quick_sort(arr, 0, len(arr) - 1)
        average_comparisons[1][index] = SortingAnalyzer.comparisons
        average_moves[1][index] = SortingAnalyzer.moves

        arr = generate_random_list(n)
        SortingAnalyzer.initialize(arr)
        hybrid_sort(arr, 0, len(arr) - 1)
        average_comparisons[2][index] = SortingAnalyzer.comparisons
        average_moves[2][index] = SortingAnalyzer.moves

    comparisons_data = [average_comparisons[0], average_comparisons[1], average_comparisons[2]]
    moves_data = [average_moves[0], average_moves[1], average_moves[2]]
    plot_comparison_moves(comparisons_data, moves_data)

if __name__ == "__main__":
    main()