import random

SIZE = 1000


def generate_random_bit_sequence(length: int) -> str:
    return "".join([str(random.randint(0, 1)) for _ in range(length)])


def main() -> None:
    with open("input.txt", "w") as input_file:
        input_file.write(generate_random_bit_sequence(SIZE))


if __name__ == "__main__":
    main()
