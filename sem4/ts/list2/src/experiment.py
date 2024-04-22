import random
from typing import Dict, Tuple

from igraph import Graph

from constants import AVERAGE_PACKET_SIZE_IN_BITS, CITIES, CONNECTIONS
from intensity_matrix import create_intensity_matrix, sum_intensity_matrix_fields
from network import create_network

NUMBER_OF_EXPERIMENTS = 100_000


def simulate_breaking(network: Graph) -> None:
    edges_to_remove = []
    for edge in network.es:
        probability_of_unbroken_edge = edge["reliablity"]
        if random.uniform(0, 1) > probability_of_unbroken_edge:
            edges_to_remove.append(edge)
    network.delete_edges(edges_to_remove)


def check_flow(network: Graph, intensity_matrix: Dict[str, Dict[str, int]]) -> Tuple[Dict[int, int], bool]:
    edge_ids_to_flows: Dict[int, int] = {i: 0 for i in range(len(network.es))}
    for source_city in network.vs:
        for target_city in network.vs:
            shortest_path_nodes = network.get_shortest_path(source_city, target_city)
            for i in range(len(shortest_path_nodes) - 1):
                edge_id = network.get_eid(shortest_path_nodes[i], shortest_path_nodes[i + 1])
                edge_ids_to_flows[edge_id] += intensity_matrix[source_city["name"]][target_city["name"]]

    for edge in network.es:
        flow = edge_ids_to_flows[edge.index]
        capacity = edge["capacity"]
        if flow * AVERAGE_PACKET_SIZE_IN_BITS > capacity:
            return edge_ids_to_flows, False

    return edge_ids_to_flows, True


def check_delay(
    network: Graph,
    intensity_matrix: Dict[str, Dict[str, int]],
    edge_ids_to_flows: Dict[int, int],
    max_delay: float,
) -> bool:
    matrix_sum = sum_intensity_matrix_fields(intensity_matrix)
    edge_sums = 0
    for edge in network.es:
        sent_packets = edge_ids_to_flows[edge.index]
        capacity = edge["capacity"]
        edge_sums += sent_packets / (capacity / AVERAGE_PACKET_SIZE_IN_BITS - sent_packets)
    delay = (1 / matrix_sum) * edge_sums

    return delay < max_delay


def run_experiment(
    intensity_matrix: Dict[str, Dict[str, int]],
    max_delay: float,
    number_of_experiments: int,
) -> Tuple[int, int, int, float]:
    breaking_fails = 0
    capacity_fails = 0
    delay_fails = 0
    successes = 0
    for _ in range(number_of_experiments):
        network = create_network(CITIES, CONNECTIONS)

        simulate_breaking(network)
        if not network.is_connected():
            breaking_fails += 1
            continue

        edge_ids_to_flows, was_success = check_flow(network, intensity_matrix)
        if not was_success:
            capacity_fails += 1
            continue

        if not check_delay(network, intensity_matrix, edge_ids_to_flows, max_delay):
            delay_fails += 1
            continue

        successes += 1

    return breaking_fails, capacity_fails, delay_fails, successes / number_of_experiments


def main() -> None:
    intensity_matrix = create_intensity_matrix(CITIES)
    breaking_fails, capacity_fails, delay_fails, reliablity = run_experiment(
        intensity_matrix, 0.000000032, NUMBER_OF_EXPERIMENTS
    )
    print(f"Breaking fails: {breaking_fails} Capacity fails: {capacity_fails} Delay fails: {delay_fails}")
    print(f"The reliablity of this network is {reliablity}")


if __name__ == "__main__":
    main()
