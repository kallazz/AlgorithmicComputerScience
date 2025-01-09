import csv
from typing import List

import matplotlib.pyplot as plt

EDMONDS_KARP_EXPERIMENT_RESULT_FILENAME = "../experimentOutput/edmondsKarpResults.csv"
OUTPUT_DIR = "../plots/"


def generate_plots_for_edmonds_karp(plot_names: List[str], data_file_path: str, output_file_names: List[str]) -> None:
    xs = []
    ys1 = []
    ys2 = []
    ys3 = []

    with open(data_file_path, "r") as data_file:
        rows = csv.reader(data_file)
        names = next(rows)

        for row in rows:
            xs.append(int(row[0]))
            ys1.append(float(row[1]) / 1_000_000_000)
            ys2.append(float(row[2]))
            ys3.append(float(row[3]))

    plt.figure(figsize=(8, 6))
    plt.clf()
    plt.plot(xs, ys1, label="Czas", marker="o")
    plt.xlabel("k (wymiar hiperkostki)")
    plt.ylabel("Czas (s)")
    plt.title(plot_names[0])
    plt.legend()
    plt.grid(True)
    plt.savefig(output_file_names[0])

    plt.clf()
    plt.plot(xs, ys2, label="Maksymalny przepływ", marker="o")
    plt.xlabel("k (wymiar hiperkostki)")
    plt.ylabel("Maksymalny przepływ")
    plt.title(plot_names[1])
    plt.legend()
    plt.grid(True)
    plt.savefig(output_file_names[1])

    plt.clf()
    plt.plot(xs, ys3, label="Ilość wyliczonych ścieżek powiększających", marker="o")
    plt.xlabel("k (wymiar hiperkostki)")
    plt.ylabel("Ilość wyliczonych ścieżek powiększających")
    plt.title(plot_names[2])
    plt.legend()
    plt.grid(True)
    plt.savefig(output_file_names[2])


def main() -> None:
    plot_names = [
        "Średni czas wykonania Edmondsa-Karpa",
        "Średnia wartość maksymalnego przepływu",
        "Średnia ilość wyliczonych ścieżek powiększających",
    ]
    output_file_names = ["edmondsKarpTimePlot.png", "edmondsKarpFlowPlot.png", "edmondsKarpPathPlot.png"]
    output_file_names = [OUTPUT_DIR + file_name for file_name in output_file_names]
    generate_plots_for_edmonds_karp(plot_names, EDMONDS_KARP_EXPERIMENT_RESULT_FILENAME, output_file_names)


if __name__ == "__main__":
    main()
