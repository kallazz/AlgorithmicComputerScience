from typing import List, Tuple

from igraph import Graph, plot

from constants import CITIES, CONNECTIONS, TERABIT


def create_network(cities: List[str], connections: List[Tuple[str, str, int, float]]) -> Graph:
    graph = Graph(directed=False)
    graph.add_vertices(cities)
    for city1, city2, capacity, reliablity in connections:
        graph.add_edge(city1, city2, capacity=capacity * TERABIT, reliablity=reliablity)
    return graph


def main() -> None:
    graph = create_network(CITIES, CONNECTIONS)
    cities = graph.vs["name"]
    network_plot = plot(graph, vertex_label=cities)
    network_plot.save("../img/network.png")
    print("Network image saved")


if __name__ == "__main__":
    main()
