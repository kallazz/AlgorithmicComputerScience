from typing import Dict, List

from constants import AVERAGE_PACKETS_PER_SECOND, CITY_POPULATIONS, POPULATION_RATIOS


def get_intensity_matrix_values(intensity_matrix: Dict[str, Dict[str, int]]) -> List[int]:
    values = []
    for city1 in intensity_matrix:
        for city2 in intensity_matrix[city1]:
            values.append(intensity_matrix[city1][city2])
    return values


def sum_intensity_matrix_fields(intensity_matrix: Dict[str, Dict[str, int]]) -> float:
    result = 0
    for city1 in intensity_matrix:
        for city2 in intensity_matrix[city1]:
            result += intensity_matrix[city1][city2]
    return result


def calculate_intensity(source_city: str, destination_city: str) -> int:
    if source_city == destination_city:
        return 0
    return round(CITY_POPULATIONS[source_city] * POPULATION_RATIOS[destination_city] * AVERAGE_PACKETS_PER_SECOND)


def create_intensity_matrix(cities: List[str]) -> Dict[str, Dict[str, int]]:
    intensity_matrix = {}
    for city1 in cities:
        intensity_matrix[city1] = {}
        for city2 in cities:
            intensity_matrix[city1][city2] = calculate_intensity(city1, city2)
    return intensity_matrix
