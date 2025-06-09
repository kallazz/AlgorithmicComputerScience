import warnings
from collections import Counter

import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
from sklearn.cluster import KMeans
from sklearn.datasets import fetch_openml
from sklearn.preprocessing import StandardScaler

warnings.filterwarnings("ignore")

PLOT_DIR = "../img"


class EMNISTClusteringAnalyzer:
    def __init__(self):
        self.X = None
        self.y = None
        self.scaler = StandardScaler()
        self.clustering_results = {}

    def load_data(self):
        print("Wczytywanie danych MNIST...")
        mnist = fetch_openml("mnist_784", version=1, as_frame=False, parser="auto")

        self.X = mnist.data
        self.y = mnist.target.astype(int)
        print("Używanie wszystkich danych MNIST (może zająć więcej czasu)...")

        self.X = self.X / 255.0

        print(f"Wczytano {len(self.X)} próbek")
        return self.X, self.y

    def perform_clustering(self, n_clusters, n_trials=10):
        print(f"\nWykonywanie klastrowania dla {n_clusters} klastrów...")

        best_kmeans = None
        best_inertia = float("inf")

        for trial in range(n_trials):
            kmeans = KMeans(n_clusters=n_clusters, init="k-means++", n_init=1, max_iter=300, random_state=trial)

            kmeans.fit(self.X)

            if kmeans.inertia_ < best_inertia:
                best_inertia = kmeans.inertia_
                best_kmeans = kmeans

        self.clustering_results[n_clusters] = {
            "kmeans": best_kmeans,
            "inertia": best_inertia,
            "labels": best_kmeans.labels_,
        }

        print(f"Najlepsza inercja dla {n_clusters} klastrów: {best_inertia:.2f}")
        return best_kmeans

    def create_assignment_matrix(self, n_clusters):
        if n_clusters not in self.clustering_results:
            raise ValueError(f"Brak wyników dla {n_clusters} klastrów")

        labels = self.clustering_results[n_clusters]["labels"]

        assignment_matrix = np.zeros((10, n_clusters))

        for true_digit in range(10):
            digit_mask = self.y == true_digit
            digit_labels = labels[digit_mask]

            if len(digit_labels) > 0:
                cluster_counts = Counter(digit_labels)
                total_digit_samples = len(digit_labels)

                for cluster_id, count in cluster_counts.items():
                    assignment_matrix[true_digit, cluster_id] = (count / total_digit_samples) * 100

        return assignment_matrix

    def plot_assignment_matrix(self, n_clusters):
        assignment_matrix = self.create_assignment_matrix(n_clusters)

        plt.figure(figsize=(12, 8))
        sns.heatmap(
            assignment_matrix,
            annot=True,
            fmt=".1f",
            cmap="Blues",
            xticklabels=[f"Klaster {i}" for i in range(n_clusters)],
            yticklabels=[f"Cyfra {i}" for i in range(10)],
        )

        plt.title(f"Procentowy przydział cyfr do klastrów ({n_clusters} klastrów)")
        plt.xlabel("Klastry")
        plt.ylabel("Prawdziwe cyfry")
        plt.tight_layout()
        plt.savefig(f"{PLOT_DIR}/macierz{n_clusters}.png")

        return assignment_matrix

    def plot_centroids(self, n_clusters):
        if n_clusters not in self.clustering_results:
            raise ValueError(f"Brak wyników dla {n_clusters} klastrów")

        centroids = self.clustering_results[n_clusters]["kmeans"].cluster_centers_

        cols = min(5, n_clusters)
        rows = (n_clusters + cols - 1) // cols

        _, axes = plt.subplots(rows, cols, figsize=(15, 3 * rows))
        if rows == 1:
            axes = axes.reshape(1, -1)

        for i in range(n_clusters):
            row = i // cols
            col = i % cols

            centroid_image = centroids[i].reshape(28, 28)

            axes[row, col].imshow(centroid_image, cmap="gray")
            axes[row, col].set_title(f"Centroid {i}")
            axes[row, col].axis("off")

        for i in range(n_clusters, rows * cols):
            row = i // cols
            col = i % cols
            axes[row, col].axis("off")

        plt.suptitle(f"Centroidy klastrów ({n_clusters} klastrów)")
        plt.tight_layout()
        plt.savefig(f"{PLOT_DIR}/centroidy{n_clusters}.png")

    def analyze_cluster_purity(self, n_clusters):
        assignment_matrix = self.create_assignment_matrix(n_clusters)

        print(f"\nAnaliza czystości dla {n_clusters} klastrów:")
        print("-" * 50)

        for cluster_id in range(n_clusters):
            cluster_column = assignment_matrix[:, cluster_id]
            dominant_digit = np.argmax(cluster_column)
            max_percentage = cluster_column[dominant_digit]

            if max_percentage > 0:
                print(f"Klaster {cluster_id}: dominuje cyfra {dominant_digit} ({max_percentage:.1f}%)")

        return assignment_matrix

    def suggest_cluster_merging(self, n_clusters):
        assignment_matrix = self.create_assignment_matrix(n_clusters)

        print(f"\nSugestie łączenia klastrów dla {n_clusters} klastrów:")
        print("-" * 50)

        digit_to_clusters = {}
        for cluster_id in range(n_clusters):
            cluster_column = assignment_matrix[:, cluster_id]
            dominant_digit = np.argmax(cluster_column)
            max_percentage = cluster_column[dominant_digit]

            if max_percentage > 20:
                if dominant_digit not in digit_to_clusters:
                    digit_to_clusters[dominant_digit] = []
                digit_to_clusters[dominant_digit].append((cluster_id, max_percentage))

        for digit, clusters in digit_to_clusters.items():
            if len(clusters) > 1:
                cluster_info = [f"klaster {cid} ({perc:.1f}%)" for cid, perc in clusters]
                print(f"Cyfra {digit}: można połączyć {', '.join(cluster_info)}")

    def run_complete_analysis(self, cluster_numbers=[10, 15, 20, 30]):
        print("=" * 60)
        print("ANALIZA KLASTROWANIA DANYCH EMNIST/MNIST")
        print("=" * 60)

        self.load_data()

        for n_clusters in cluster_numbers:
            print(f"\n{'='*20} {n_clusters} KLASTRÓW {'='*20}")

            self.perform_clustering(n_clusters)

            self.plot_assignment_matrix(n_clusters)

            self.plot_centroids(n_clusters)

            self.analyze_cluster_purity(n_clusters)
            self.suggest_cluster_merging(n_clusters)

            print("-" * 60)


if __name__ == "__main__":
    analyzer = EMNISTClusteringAnalyzer()
    analyzer.run_complete_analysis()

    cluster_numbers = [10, 15, 20, 30]
    inertias = [analyzer.clustering_results[n]["inertia"] for n in cluster_numbers]

    plt.figure(figsize=(10, 6))
    plt.plot(cluster_numbers, inertias, "bo-", linewidth=2, markersize=8)
    plt.xlabel("Liczba klastrów")
    plt.ylabel("Inercja")
    plt.title("Inercja vs. Liczba klastrów")
    plt.grid(True, alpha=0.3)
    plt.savefig(f"{PLOT_DIR}/inercja_vs_liczba_klastrow.png")

    print("\nPodsumowanie inercji:")
    for n, inertia in zip(cluster_numbers, inertias):
        print(f"{n} klastrów: {inertia:.2f}")
