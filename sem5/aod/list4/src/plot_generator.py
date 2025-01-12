import matplotlib.pyplot as plt
import pandas as pd
from matplotlib.ticker import MaxNLocator

EDMONDS_KARP_EXPERIMENT_RESULT_FILENAME = "../experimentOutput/edmondsKarpResults.csv"
MAXIMUM_BIPARTITE_MATCHING_EXPERIMENT_RESULT_FILENAME = "../experimentOutput/maximumBipartiteMatchingResults.csv"
OUTPUT_DIR = "../plots/"


def generate_plots_for_edmonds_karp(data_file_path: str, output_dir: str) -> None:
    plotting_data = pd.read_csv(data_file_path)

    plt.figure(figsize=(8, 6))

    plt.clf()
    duration_in_seconds = plotting_data["Duration"] / 1_000_000_000
    plt.plot(plotting_data["Hypercube Size"], duration_in_seconds, label="Czas", marker="o")
    plt.xlabel("k (wymiar hiperkostki)")
    plt.ylabel("Czas (s)")
    plt.title("Średni czas wykonania Edmondsa-Karpa")
    plt.legend()
    plt.grid(True)
    plt.savefig(output_dir + "edmondsKarpTimePlot.png")

    plt.clf()
    plt.plot(plotting_data["Hypercube Size"], plotting_data["Max Flow"], label="Maksymalny przepływ", marker="o")
    plt.xlabel("k (wymiar hiperkostki)")
    plt.ylabel("Maksymalny przepływ")
    plt.title("Średnia wartość maksymalnego przepływu")
    plt.legend()
    plt.grid(True)
    plt.savefig(output_dir + "edmondsKarpFlowPlot.png")

    plt.clf()
    plt.plot(
        plotting_data["Hypercube Size"],
        plotting_data["Number of Augmenting Paths"],
        label="Ilość wyliczonych ścieżek powiększających",
        marker="o",
    )
    plt.xlabel("k (wymiar hiperkostki)")
    plt.ylabel("Ilość wyliczonych ścieżek powiększających")
    plt.title("Średnia ilość wyliczonych ścieżek powiększających")
    plt.legend()
    plt.grid(True)
    plt.savefig(output_dir + "edmondsKarpPathPlot.png")


def generate_plots_for_maximum_bipartite_matching(data_file_path: str, output_dir: str) -> None:
    plotting_data = pd.read_csv(data_file_path)

    unique_ks = plotting_data["Graph Size"].unique()
    unique_is = plotting_data["Degree"].unique()

    plt.figure(figsize=(8, 6))

    for unique_k in unique_ks:
        unique_k_data = plotting_data[plotting_data["Graph Size"] == unique_k]
        plt.clf()
        plt.plot(
            unique_k_data["Degree"], unique_k_data["Max Matching Size"], label="Maksymalne skojarzenie", marker="o"
        )
        plt.xlabel("i (Stopień każdego wierzchołka)")
        plt.ylabel("Maksymalne skojarzenie")
        plt.title(f"Średnia wielkość maksymalnego skojarzenia dla k={unique_k}")
        plt.legend()
        plt.ylim(0, max(unique_k_data["Max Matching Size"]) * 1.5)
        plt.grid(True)
        plt.gca().xaxis.set_major_locator(MaxNLocator(integer=True))
        plt.savefig(output_dir + f"maximumBipartiteMatchingMaxMatchingPlot{unique_k}.png")

    for unique_i in unique_is:
        unique_i_data = plotting_data[plotting_data["Degree"] == unique_i]
        plt.clf()
        duration_in_seconds = unique_i_data["Duration"] / 1_000_000_000
        plt.plot(unique_i_data["Graph Size"], duration_in_seconds, label="Czas", marker="o")
        plt.xlabel("k (Rozmiar grafu)")
        plt.ylabel("Czas (s)")
        plt.title(f"Średni czas wykonania algorytmu dla i={unique_i}")
        plt.legend()
        plt.grid(True)
        plt.savefig(output_dir + f"maximumBipartiteMatchingTimePlot{unique_i}.png")


def main() -> None:
    generate_plots_for_edmonds_karp(EDMONDS_KARP_EXPERIMENT_RESULT_FILENAME, OUTPUT_DIR)
    generate_plots_for_maximum_bipartite_matching(MAXIMUM_BIPARTITE_MATCHING_EXPERIMENT_RESULT_FILENAME, OUTPUT_DIR)


if __name__ == "__main__":
    main()
