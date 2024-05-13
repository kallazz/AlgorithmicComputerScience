from bit_framing import encode, decode


def main() -> None:
    with open("input.txt", "r") as input_file:
        input_bits = input_file.read()
        print("Input bits:")
        print(f"{input_bits}\n")

    with open("encoded.txt", "w") as encoded_file:
        encoded_bits = encode(input_bits)
        print("Encoded bits:")
        print(f"{encoded_bits}\n")
        encoded_file.write(encoded_bits)

    with open("decoded.txt", "w") as decoded_file:
        decoded_bits = decode(encoded_bits)
        print("Decoded bits:")
        print(f"{decoded_bits}\n")
        decoded_file.write(decoded_bits)

    if input_bits == decoded_bits:
        print("The bits were successfully decoded!")


if __name__ == "__main__":
    main()
