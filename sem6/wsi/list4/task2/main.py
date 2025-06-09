import time
from collections import Counter

import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
import tensorflow_datasets as tfds
from sklearn.decomposition import PCA
from sklearn.manifold import TSNE

from dbscan import DBSCAN

PLOT_DIR = "../img"


def load_and_preprocess_mnist(n_samples=1000):
    print("Ładowanie danych MNIST z TensorFlow Datasets...")

    ds = tfds.load("mnist", split="train", as_supervised=True, download=True)
    print(f"Dataset załadowany pomyślnie!")

    X_list = []
    y_list = []

    print(f"Przetwarzanie {n_samples} próbek...")

    for i, (image, label) in enumerate(tfds.as_numpy(ds.take(n_samples))):
        if i % 500 == 0:
            print(f"Przetworzono {i} próbek...")

        X_list.append(image.reshape(-1))
        y_list.append(label)

    X = np.array(X_list, dtype=np.float32)
    y = np.array(y_list, dtype=int)

    print(f"Załadowano {len(X)} próbek")
    print(f"Kształt danych: {X.shape}")

    X = X / 255.0

    print("Redukcja wymiarowości PCA...")
    X_pca = PCA(n_components=50).fit_transform(X)

    print("Redukcja wymiarowości t-SNE...")
    tsne = TSNE(n_components=2, random_state=0)
    X_tsne = tsne.fit_transform(X_pca)

    return X_tsne, y


def analyze_clusters(labels, true_labels):
    unique_clusters = set(labels)
    n_clusters = len(unique_clusters) - (1 if -1 in unique_clusters else 0)
    noise_count = sum(1 for label in labels if label == -1)
    noise_percentage = (noise_count / len(labels)) * 100

    print(f"\n=== ANALIZA WYNIKÓW ===")
    print(f"Liczba klastrów: {n_clusters}")
    print(f"Liczba punktów szumu: {noise_count}")
    print(f"Procent szumu: {noise_percentage:.2f}%")

    cluster_purity = {}
    cluster_sizes = {}
    total_correct = 0
    total_in_clusters = 0

    for cluster_id in unique_clusters:
        if cluster_id == -1:
            continue

        cluster_mask = labels == cluster_id
        cluster_true_labels = true_labels[cluster_mask]
        cluster_sizes[cluster_id] = len(cluster_true_labels)

        if len(cluster_true_labels) > 0:
            digit_counts = Counter(cluster_true_labels)
            dominant_digit = digit_counts.most_common(1)[0][0]
            dominant_count = digit_counts.most_common(1)[0][1]

            purity = dominant_count / len(cluster_true_labels)
            cluster_purity[cluster_id] = {
                "dominant_digit": dominant_digit,
                "purity": purity,
                "size": len(cluster_true_labels),
                "correct_count": dominant_count,
            }

            total_correct += dominant_count
            total_in_clusters += len(cluster_true_labels)

    accuracy = (total_correct / total_in_clusters) * 100 if total_in_clusters > 0 else 0

    print(f"Dokładność klasyfikacji (bez szumu): {accuracy:.2f}%")
    print(f"Procent błędnych klasyfikacji: {100 - accuracy:.2f}%")

    print(f"\n=== SZCZEGÓŁY KLASTRÓW (TOP 10) ===")
    sorted_clusters = sorted(cluster_purity.items(), key=lambda x: x[1]["size"], reverse=True)

    for i, (cluster_id, info) in enumerate(sorted_clusters[:10]):
        print(
            f"Klaster {cluster_id}: cyfra {info['dominant_digit']}, "
            f"czystość {info['purity']:.2f}, "
            f"rozmiar {info['size']}"
        )

    if len(sorted_clusters) > 10:
        print(f"... i {len(sorted_clusters) - 10} innych klastrów")

    print(f"\n=== POKRYCIE CYFR ===")
    digit_coverage = {}
    for digit in range(10):
        digit_clusters = []
        for cluster_id, info in cluster_purity.items():
            if info["dominant_digit"] == digit:
                digit_clusters.append(cluster_id)
        digit_coverage[digit] = len(digit_clusters)
        print(f"Cyfra {digit}: {len(digit_clusters)} klastrów")

    return {
        "n_clusters": n_clusters,
        "noise_percentage": noise_percentage,
        "accuracy": accuracy,
        "cluster_purity": cluster_purity,
    }


def plot_results(X, labels, true_labels, n_clusters):
    X_vis = X
    labels_vis = labels
    true_labels_vis = true_labels

    _, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))

    sns.scatterplot(
        x=X_vis[:, 0],
        y=X_vis[:, 1],
        hue=true_labels_vis,
        palette=sns.hls_palette(10),
        legend="full",
        ax=ax1,
        s=30,
        alpha=0.7,
    )
    ax1.set_title("Prawdziwe etykiety (cyfry)")
    ax1.set_xlabel("Wymiar 1 (t-SNE)")
    ax1.set_ylabel("Wymiar 2 (t-SNE)")

    sns.scatterplot(
        x=X_vis[:, 0],
        y=X_vis[:, 1],
        hue=labels_vis,
        palette=sns.color_palette("tab20", n_clusters + 1),
        legend="full",
        ax=ax2,
        s=30,
        alpha=0.7,
    )
    ax2.set_title(f"Klasteryzacja DBSCAN ({n_clusters} klastrów)")
    ax2.set_xlabel("Wymiar 1 (t-SNE)")
    ax2.set_ylabel("Wymiar 2 (t-SNE)")

    plt.tight_layout()
    plt.savefig(f"{PLOT_DIR}/dbscan_porownanie.png")


def main():
    print("=== IMPLEMENTACJA DBSCAN DLA MNIST (TensorFlow Datasets) ===\n")

    print(f"\n" + "=" * 50)
    X, y = load_and_preprocess_mnist(n_samples=5000)

    eps = 2.5
    min_samples = 9

    print(f"\n" + "=" * 50)
    print(f"Parametry DBSCAN:")
    print(f"eps (promień sąsiedztwa): {eps}")
    print(f"min_samples (min. punktów w klastrze): {min_samples}")

    print(f"\nUruchamianie DBSCAN...")
    start_time = time.time()

    print(f"Rozpoczynam klasteryzację DBSCAN (eps={eps}, min_samples={min_samples})")
    dbscan = DBSCAN(eps=eps, min_samples=min_samples)
    cluster_labels = dbscan.fit_predict(X)

    end_time = time.time()
    print(f"Czas wykonania: {end_time - start_time:.2f} sekund")

    results = analyze_clusters(cluster_labels, y)

    print(f"\nGenerowanie wizualizacji...")
    plot_results(X, cluster_labels, y, results["n_clusters"])

    print(f"\n" + "=" * 50)
    print(f"=== PODSUMOWANIE ===")
    print(f"✓ Liczba klastrów: {results['n_clusters']}")
    print(f"✓ Procent szumu: {results['noise_percentage']:.2f}%")
    print(f"✓ Dokładność klasyfikacji: {results['accuracy']:.2f}%")
    print(f"✓ Procent błędów: {100 - results['accuracy']:.2f}%")


if __name__ == "__main__":
    main()
