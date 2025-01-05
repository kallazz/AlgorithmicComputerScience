import csv
from typing import List

import matplotlib.pyplot as plt

DATA_DIR = "../experimentOutput/"
TIME_RESULTS_FILENAME = "timeResults.csv"
MEMORY_RESULTS_FILENAME = "memoryResults.csv"

OUTPUT_DIR = "../plots/"


def plot_data(plot_name: str, column_names: List[str], y_name: str, data_file_path: str, output_file_name: str) -> None:
    xs = []
    ys1 = []
    ys2 = []

    with open(data_file_path, "r") as data_file:
        rows = csv.reader(data_file, delimiter=";")

        for row in rows:
            xs.append(int(row[0]))
            ys1.append(float(row[1]))
            ys2.append(float(row[2]))

    plt.clf()
    plt.plot(xs, ys1, label=column_names[1], marker="o")
    plt.plot(xs, ys2, label=column_names[2], marker="o")
    plt.xlabel(column_names[0])
    plt.ylabel(y_name)
    plt.title(plot_name)
    plt.legend()
    plt.savefig(output_file_name)


def main() -> None:
    plot_data(
        "Czas wykonania zoptymalizowanych algorytmów eliminacji Gaussa",
        ["Rozmiar macierzy", "Zoptymalizowany Gauss", "Zoptymalizowany Gauss z wyborem el. głównego"],
        "Czas (s)",
        DATA_DIR + TIME_RESULTS_FILENAME,
        OUTPUT_DIR + "timePlot.png",
    )
    plot_data(
        "Zużycie pamięci przez zoptymalizowane algorytmy eliminacji Gaussa",
        ["Rozmiar macierzy", "Zoptymalizowany Gauss", "Zoptymalizowany Gauss z wyborem el. głównego"],
        "Ilość pamięci (B)",
        DATA_DIR + MEMORY_RESULTS_FILENAME,
        OUTPUT_DIR + "memoryPlot.png",
    )


if __name__ == "__main__":
    main()
