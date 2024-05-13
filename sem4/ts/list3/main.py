from bit_framing import encode, decode


def main() -> None:
    with open("input.txt", "r") as input_file:
        input_bits = input_file.read()

    with open("encoded.txt", "w") as encoded_file:
        encoded_bits = encode(input_bits)
        encoded_file.write(encoded_bits)

    with open("decoded.txt", "w") as decoded_file:
        decoded_file.write(decode(encoded_bits))


if __name__ == "__main__":
    main()
