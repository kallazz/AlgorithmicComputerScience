from typing import List, Optional

import numpy as np


class DBSCAN:
    def __init__(self, eps: float = 0.5, min_samples: int = 5):
        self.eps: float = eps
        self.min_samples: int = min_samples
        self.labels_: Optional[np.ndarray] = None

    def _euclidean_distance(self, point1: np.ndarray, point2: np.ndarray) -> float:
        return float(np.linalg.norm(point1 - point2))

    def _get_neighbors(self, X: np.ndarray, point_idx: int) -> List[int]:
        neighbors: List[int] = []
        for i, point in enumerate(X):
            if self._euclidean_distance(X[point_idx], point) <= self.eps:
                neighbors.append(i)
        return neighbors

    def _expand_cluster(
        self, X: np.ndarray, labels: np.ndarray, point_idx: int, neighbors: List[int], cluster_id: int
    ) -> None:
        labels[point_idx] = cluster_id
        i = 0

        while i < len(neighbors):
            neighbor_idx = neighbors[i]

            if labels[neighbor_idx] == 0:
                labels[neighbor_idx] = cluster_id
                new_neighbors = self._get_neighbors(X, neighbor_idx)

                if len(new_neighbors) >= self.min_samples:
                    for new_neighbor in new_neighbors:
                        if new_neighbor not in neighbors:
                            neighbors.append(new_neighbor)
            else:
                labels[neighbor_idx] = cluster_id

            i += 1

    def fit(self, X: np.ndarray) -> "DBSCAN":
        cluster_id = 0
        n_points = len(X)
        labels = np.zeros(n_points, dtype=int)  # 0 = not visited, -1 = noise, >0 = cluster

        for point_idx in range(n_points):
            if labels[point_idx] != 0:
                continue

            neighbors = self._get_neighbors(X, point_idx)

            if len(neighbors) < self.min_samples:
                labels[point_idx] = -1
            else:
                cluster_id += 1
                self._expand_cluster(X, labels, point_idx, neighbors, cluster_id)

        self.labels_ = labels
        return self

    def fit_predict(self, X: np.ndarray) -> np.ndarray:
        self.fit(X)
        assert self.labels_ is not None
        return self.labels_
