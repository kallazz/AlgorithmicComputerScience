import sys
import math
import struct
from collections import defaultdict
from typing import Dict
from constants import MAX_RANGE, HALF_RANGE, QUARTER_RANGE, MAX_TOTAL_SYMBOL_FREQUENCY


class AdaptiveArithmeticEncoder:
    def __init__(self):
        self.symbol_frequency: Dict[int, int] = defaultdict(lambda: 1)
        self.total_symbol_frequency: int = 256
        self.interval_low: int = 0
        self.interval_high: int = MAX_RANGE - 1
        self.num_of_pending_bits: int = 0
        self.output_bits: list[int] = []

    def _write_bit(self, bit_value: int) -> None:
        self.output_bits.append(bit_value)
        while self.num_of_pending_bits > 0:
            self.output_bits.append(1 - bit_value)
            self.num_of_pending_bits -= 1

    def _convert_bits_to_bytes(self, bits: list[int]) -> bytes:
        encoded_bytes = bytearray()
        current_byte_value = 0
        num_of_bits_in_current_byte = 0

        for bit_value in bits:
            current_byte_value = (current_byte_value << 1) | bit_value
            num_of_bits_in_current_byte += 1
            if num_of_bits_in_current_byte == 8:
                encoded_bytes.append(current_byte_value)
                current_byte_value = 0
                num_of_bits_in_current_byte = 0

        if num_of_bits_in_current_byte > 0:
            encoded_bytes.append(current_byte_value << (8 - num_of_bits_in_current_byte))

        return bytes(encoded_bytes)

    def encode(self, input_data: bytes) -> bytes:
        for byte_value in input_data:
            cumulative_frequency = sum(self.symbol_frequency[symbol_index] for symbol_index in range(byte_value))
            symbol_freq = self.symbol_frequency[byte_value]

            interval_range = self.interval_high - self.interval_low + 1
            self.interval_high = (
                self.interval_low
                + (interval_range * (cumulative_frequency + symbol_freq)) // self.total_symbol_frequency
                - 1
            )
            self.interval_low = (
                self.interval_low + (interval_range * cumulative_frequency) // self.total_symbol_frequency
            )

            while True:
                if self.interval_high < HALF_RANGE:
                    self._write_bit(0)
                    self.interval_low = self.interval_low * 2
                    self.interval_high = self.interval_high * 2 + 1
                elif self.interval_low >= HALF_RANGE:
                    self._write_bit(1)
                    self.interval_low = (self.interval_low - HALF_RANGE) * 2
                    self.interval_high = (self.interval_high - HALF_RANGE) * 2 + 1
                elif self.interval_low >= QUARTER_RANGE and self.interval_high < 3 * QUARTER_RANGE:
                    self.num_of_pending_bits += 1
                    self.interval_low = (self.interval_low - QUARTER_RANGE) * 2
                    self.interval_high = (self.interval_high - QUARTER_RANGE) * 2 + 1
                else:
                    break

            self.symbol_frequency[byte_value] += 1
            self.total_symbol_frequency += 1

            if self.total_symbol_frequency > MAX_TOTAL_SYMBOL_FREQUENCY:
                for symbol_key in list(self.symbol_frequency.keys()):
                    self.symbol_frequency[symbol_key] = (self.symbol_frequency[symbol_key] + 1) // 2
                self.total_symbol_frequency = sum(self.symbol_frequency.values())

        self.num_of_pending_bits += 1
        if self.interval_low < QUARTER_RANGE:
            self._write_bit(0)
        else:
            self._write_bit(1)

        return self._convert_bits_to_bytes(self.output_bits)


def calculate_entropy(symbol_probabilities: Dict[int, float]) -> float:
    return sum(
        -(probability * math.log2(probability)) for probability in symbol_probabilities.values() if probability > 0
    )


def main() -> None:
    if len(sys.argv) != 3:
        print("Usage: python3 encode.py input.bin output.bin")
        sys.exit(1)

    with open(sys.argv[1], "rb") as input_file:
        input_data = input_file.read()

    encoder = AdaptiveArithmeticEncoder()
    encoded_data = encoder.encode(input_data)

    with open(sys.argv[2], "wb") as output_file:
        output_file.write(struct.pack(">I", len(input_data)))
        output_file.write(encoded_data)

    byte_frequency = [0] * 256
    for byte_value in input_data:
        byte_frequency[byte_value] += 1

    total_num_of_bytes = len(input_data)
    symbol_probabilities = {
        symbol_index: byte_frequency[symbol_index] / total_num_of_bytes
        for symbol_index in range(256)
        if byte_frequency[symbol_index] > 0
    }

    entropy = calculate_entropy(symbol_probabilities)
    average_code_length = len(encoded_data) * 8 / len(input_data) if len(input_data) > 0 else 0
    compression_ratio = len(input_data) / len(encoded_data) if len(encoded_data) > 0 else 0

    print(f"Entropy: {entropy:.4f} bits/symbol")
    print(f"Average code length: {average_code_length:.4f} bits/symbol")
    print(f"Compression ratio: {compression_ratio:.4f}")


if __name__ == "__main__":
    main()
