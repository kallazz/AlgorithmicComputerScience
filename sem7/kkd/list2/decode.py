import sys
import struct
from collections import defaultdict
from constants import PRECISION, MAX_RANGE, HALF_RANGE, QUARTER_RANGE, MAX_TOTAL_SYMBOL_FREQUENCY
from typing import Iterator, DefaultDict


def bitstream(data: bytes) -> Iterator[int]:
    for byte_value in data:
        for bit_index in range(7, -1, -1):
            yield (byte_value >> bit_index) & 1


def adaptive_arithmetic_decode(encoded_data: bytes, output_size: int) -> bytes:
    symbol_frequency: DefaultDict[int, int] = defaultdict(lambda: 1)
    total_symbol_frequency = 256
    interval_low, interval_high = 0, MAX_RANGE - 1
    current_value = 0
    input_bits = bitstream(encoded_data)

    for _ in range(PRECISION):
        current_value = (current_value << 1) | next(input_bits, 0)

    decoded_bytes = bytearray()

    for _ in range(output_size):
        interval_range = interval_high - interval_low + 1
        target_value = ((current_value - interval_low + 1) * total_symbol_frequency - 1) // interval_range

        decoded_symbol = 0
        cumulative_frequency = 0
        while cumulative_frequency + symbol_frequency[decoded_symbol] <= target_value:
            cumulative_frequency += symbol_frequency[decoded_symbol]
            decoded_symbol += 1

        decoded_bytes.append(decoded_symbol)

        interval_high = (
            interval_low
            + (interval_range * (cumulative_frequency + symbol_frequency[decoded_symbol])) // total_symbol_frequency
            - 1
        )
        interval_low = interval_low + (interval_range * cumulative_frequency) // total_symbol_frequency

        while True:
            if interval_high < HALF_RANGE:
                pass
            elif interval_low >= HALF_RANGE:
                interval_low -= HALF_RANGE
                interval_high -= HALF_RANGE
                current_value -= HALF_RANGE
            elif interval_low >= QUARTER_RANGE and interval_high < 3 * QUARTER_RANGE:
                interval_low -= QUARTER_RANGE
                interval_high -= QUARTER_RANGE
                current_value -= QUARTER_RANGE
            else:
                break

            interval_low = interval_low * 2
            interval_high = interval_high * 2 + 1
            current_value = (current_value * 2) + next(input_bits, 0)

        symbol_frequency[decoded_symbol] += 1
        total_symbol_frequency += 1

        if total_symbol_frequency > MAX_TOTAL_SYMBOL_FREQUENCY:
            for symbol_key in symbol_frequency:
                symbol_frequency[symbol_key] = (symbol_frequency[symbol_key] + 1) // 2
            total_symbol_frequency = sum(symbol_frequency.values())

    return bytes(decoded_bytes)


def main() -> None:
    if len(sys.argv) != 3:
        print("Usage: python3 decode.py input.bin output.bin")
        sys.exit(1)

    with open(sys.argv[1], "rb") as input_file:
        header_bytes = input_file.read(4)
        if len(header_bytes) < 4:
            print("Error: input file too short, missing header.")
            sys.exit(1)

        original_size = struct.unpack(">I", header_bytes)[0]
        encoded_data = input_file.read()

    decoded_data = adaptive_arithmetic_decode(encoded_data, original_size)

    with open(sys.argv[2], "wb") as output_file:
        output_file.write(decoded_data)


if __name__ == "__main__":
    main()
