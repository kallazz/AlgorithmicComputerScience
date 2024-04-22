from typing import Dict, List, Tuple

# Units
TERABIT = 1_000_000_000_000

# Packets
AVERAGE_PACKETS_PER_SECOND = 10
AVERAGE_PACKET_SIZE_IN_BITS = 1500 * 8

# Network Design
CITIES: List[str] = [
    "Warszawa",
    "Berlin",
    "Paryż",
    "Londyn",
    "Madryt",
    "Rzym",
    "Moskwa",
    "Kijów",
    "Praga",
    "Budapeszt",
    "Wiedeń",
    "Amsterdam",
    "Bruksela",
    "Sztokholm",
    "Oslo",
    "Helsinki",
    "Kopenhaga",
    "Lizbona",
    "Ateny",
    "Dublin",
]
CONNECTIONS: List[Tuple[str, str, int, float]] = [
    ("Warszawa", "Berlin", 7, 0.997),
    ("Warszawa", "Kijów", 3, 0.986),
    ("Warszawa", "Londyn", 6, 0.996),
    ("Berlin", "Paryż", 8, 0.997),
    ("Berlin", "Amsterdam", 4, 0.995),
    ("Berlin", "Rzym", 6, 0.995),
    ("Rzym", "Madryt", 5, 0.999),
    ("Rzym", "Amsterdam", 4, 0.996),
    ("Amsterdam", "Kopenhaga", 4, 0.995),
    ("Amsterdam", "Bruksela", 4, 0.996),
    ("Praga", "Lizbona", 3, 0.991),
    ("Kopenhaga", "Oslo", 3, 0.994),
    ("Kopenhaga", "Sztokholm", 3, 0.994),
    ("Wiedeń", "Praga", 3, 0.996),
    ("Sztokholm", "Helsinki", 2, 0.996),
    ("Helsinki", "Oslo", 3, 0.996),
    ("Helsinki", "Moskwa", 5, 0.992),
    ("Oslo", "Bruksela", 3, 0.995),
    ("Londyn", "Dublin", 5, 0.997),
    ("Londyn", "Bruksela", 4, 0.995),
    ("Dublin", "Paryż", 4, 0.996),
    ("Paryż", "Madryt", 6, 0.997),
    ("Paryż", "Bruksela", 3, 0.997),
    ("Madryt", "Lizbona", 5, 0.996),
    ("Budapeszt", "Kijów", 2, 0.984),
    ("Ateny", "Rzym", 4, 0.995),
    ("Wiedeń", "Berlin", 3, 0.996),
    ("Praga", "Berlin", 3, 0.996),
    ("Budapeszt", "Wiedeń", 2, 0.995),
]

# Populations
CITY_POPULATIONS: Dict[str, int] = {
    "Warszawa": 1790000,
    "Berlin": 3769000,
    "Paryż": 2148000,
    "Londyn": 8982000,
    "Madryt": 3345000,
    "Rzym": 2872000,
    "Moskwa": 12615000,
    "Kijów": 2944000,
    "Praga": 1326000,
    "Budapeszt": 1752000,
    "Wiedeń": 1897000,
    "Amsterdam": 872000,
    "Bruksela": 1211000,
    "Sztokholm": 975000,
    "Oslo": 681000,
    "Helsinki": 656000,
    "Kopenhaga": 616000,
    "Lizbona": 506000,
    "Ateny": 664000,
    "Dublin": 553000,
}
TOTAL_POPULATION = sum(CITY_POPULATIONS.values())
POPULATION_RATIOS: Dict[str, float] = {
    city: population / TOTAL_POPULATION for city, population in CITY_POPULATIONS.items()
}
