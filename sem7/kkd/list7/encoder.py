import sys

from shared import G_DEG, mod_poly


def encode_nibble(n: int) -> int:
    """
    Encode 4-bit nibble into extended cyclic Hamming (8,4).
    Layout:
      - bits 0..6: cyclic (7,4) codeword where bits 3..6 carry the message
      - bit 7: overall even parity
    """
    n &= 0xF
    shifted = n << G_DEG  # message in bits 3..6
    rem = mod_poly(shifted)
    code7 = shifted | rem  # 7-bit codeword
    overall_parity = code7.bit_count() & 1  # 1 if odd -> makes total even
    code8 = code7 | (overall_parity << 7)
    return code8


def main() -> int:
    if len(sys.argv) != 3:
        print("Usage: encoder in out", file=sys.stderr)
        return 2

    in_path, out_path = sys.argv[1], sys.argv[2]

    with open(in_path, "rb") as f_in, open(out_path, "wb") as f_out:
        data = f_in.read()
        out = bytearray()

        for b in data:
            hi = (b >> 4) & 0xF
            lo = b & 0xF
            out.append(encode_nibble(hi))
            out.append(encode_nibble(lo))

        f_out.write(out)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
