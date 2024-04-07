import argparse
from random import randint
from typing import Callable, Dict, List


def generate_random_list(list_size: int) -> List[int]:
    return [randint(0, 2 * list_size - 1) for _ in range(list_size)]


def generate_random_ascending_list(list_size: int) -> List[int]:
    return sorted(generate_random_list(list_size))


def generate_random_descending_list(list_size: int) -> List[int]:
    return sorted(generate_random_list(list_size), reverse=True)


CHOICES_TO_GENERATORS: Dict[str, Callable[[int], List[int]]] = {
    "random": generate_random_list,
    "ascending": generate_random_ascending_list,
    "descending": generate_random_descending_list,
}


def main() -> None:
    parser = argparse.ArgumentParser("Random lists generators")
    parser.add_argument("generator_type", choices=["random", "ascending", "descending"])
    parser.add_argument("list_size", type=int)
    args = parser.parse_args()

    generated_list = CHOICES_TO_GENERATORS[args.generator_type](args.list_size)
    print(" ".join([str(number) for number in generated_list]))


if __name__ == "__main__":
    main()
