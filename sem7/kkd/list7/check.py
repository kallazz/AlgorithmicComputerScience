import sys


def main() -> int:
    if len(sys.argv) != 3:
        print("Usage: check in1 in2", file=sys.stderr)
        return 2

    p1, p2 = sys.argv[1], sys.argv[2]

    with open(p1, "rb") as f1, open(p2, "rb") as f2:
        a = f1.read()
        b = f2.read()

    min_len = min(len(a), len(b))
    nibble_diff = 0

    for i in range(min_len):
        a_hi = (a[i] >> 4) & 0xF
        a_lo = a[i] & 0xF
        b_hi = (b[i] >> 4) & 0xF
        b_lo = b[i] & 0xF

        if a_hi != b_hi:
            nibble_diff += 1
        if a_lo != b_lo:
            nibble_diff += 1

    # Remaining bytes (if file sizes differ):
    extra_bytes = abs(len(a) - len(b))
    nibble_diff += 2 * extra_bytes

    print(f"Different 4-bit blocks: {nibble_diff}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
