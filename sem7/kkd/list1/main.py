import math
import sys
from collections import defaultdict
from typing import Dict, Tuple


def read_file_content(filename: str) -> bytes:
    try:
        with open(filename, "rb") as file:
            return file.read()
    except FileNotFoundError:
        print(f"Error: File '{filename}' not found.")
        sys.exit(1)
    except Exception as e:
        print(f"Error reading file: {e}")
        sys.exit(1)


def calculate_byte_counts(content: bytes) -> Dict[int, int]:
    counts = defaultdict(int)
    for byte in content:
        counts[byte] += 1
    return dict(counts)


def calculate_pair_counts(content: bytes) -> Dict[Tuple[int, int], int]:
    counts = defaultdict(int)
    previous_byte = 0  # Initial byte
    for byte in content:
        counts[(previous_byte, byte)] += 1
        previous_byte = byte
    return dict(counts)


def calculate_entropy(probabilities: Dict[int, float]) -> float:
    return sum(-(p * math.log2(p)) for p in probabilities.values())


def calculate_conditional_entropy(
    pair_counts: Dict[Tuple[int, int], int], byte_counts: Dict[int, int]
) -> float:
    total_pairs = sum(pair_counts.values())
    entropy = 0.0

    for (first_byte, _), count in pair_counts.items():
        joint_probability = count / total_pairs
        conditional_probability = count / byte_counts.get(first_byte, 1)
        entropy -= joint_probability * math.log2(conditional_probability)

    return entropy


def main() -> None:
    if len(sys.argv) != 2:
        print("Usage: python main.py <filename>")
        sys.exit(1)

    filename = sys.argv[1]
    content = read_file_content(filename)

    byte_counts = calculate_byte_counts(content)
    pair_counts = calculate_pair_counts(content)

    total_bytes = sum(byte_counts.values())
    probabilities = {byte: count / total_bytes for byte, count in byte_counts.items()}

    entropy = calculate_entropy(probabilities)
    conditional_entropy = calculate_conditional_entropy(pair_counts, byte_counts)
    difference = entropy - conditional_entropy

    print(f"H(Y) = {entropy:.4f} bits")
    print(f"H(Y|X) = {conditional_entropy:.4f} bits")
    print(f"Difference (H(Y) - H(Y|X)) = {difference:.4f} bits")


if __name__ == "__main__":
    main()
