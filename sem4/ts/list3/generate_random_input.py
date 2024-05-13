import random

SIZE = 1000


def generate_random_bit_sequence(length: int) -> str:
    bit_sequence = ""
    for _ in range(length):
        bit_sequence += str(random.randint(0, 1))
    return bit_sequence


def main() -> None:
    with open("input.txt", "w") as input_file:
        input_file.write(generate_random_bit_sequence(SIZE))


if __name__ == "__main__":
    main()
