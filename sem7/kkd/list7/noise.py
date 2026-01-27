import sys
import random


def main() -> int:
    if len(sys.argv) != 4:
        print("Usage: noise p in out", file=sys.stderr)
        return 2

    try:
        p = float(sys.argv[1])
    except ValueError:
        print("Error: p must be a float in [0, 1].", file=sys.stderr)
        return 2

    if not (0.0 <= p <= 1.0):
        print("Error: p must be in [0, 1].", file=sys.stderr)
        return 2

    in_path, out_path = sys.argv[2], sys.argv[3]

    with open(in_path, "rb") as f_in:
        data = bytearray(f_in.read())

    for i in range(len(data)):
        x = data[i]
        for bit in range(8):
            if random.random() < p:
                x ^= 1 << bit
        data[i] = x

    with open(out_path, "wb") as f_out:
        f_out.write(data)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
