import sys

from shared import G_DEG, mod_poly


def show_unique(table: dict[int, int]) -> dict[int, int]:
    # Defensive: if collision (should not happen here), keep first.
    unique = {}
    for s, pos in table.items():
        if s not in unique:
            unique[s] = pos
    return unique


def build_syndrome_table() -> dict[int, int]:
    """
    Map syndrome (3-bit remainder) -> bit position (0..6) for single-bit errors.
    """
    table = {}
    for pos in range(7):
        e = 1 << pos
        s = mod_poly(e)
        table[s] = pos
    return show_unique(table)


SYNDROME_TO_POS = build_syndrome_table()


def correct_codeword(code8: int) -> tuple[int, bool, bool]:
    """
    Returns (corrected_code8, corrected, detected_double_error)

    SECDED logic:
      - syndrome == 0 and overall parity ok -> no error
      - syndrome == 0 and overall parity bad -> error in parity bit (bit 7)
      - syndrome != 0 and overall parity bad -> single-bit error in bits 0..6, correct it
      - syndrome != 0 and overall parity ok -> detected double-bit error (or any even # of errors), no correction
    """
    code8 &= 0xFF
    code7 = code8 & 0x7F
    parity_bit = (code8 >> 7) & 1

    syndrome = mod_poly(code7)
    overall_ok = ((code7.bit_count() + parity_bit) & 1) == 0

    corrected = False
    double_error = False

    if syndrome == 0 and overall_ok:
        return code8, corrected, double_error

    if syndrome == 0 and not overall_ok:
        # Only the overall parity bit is wrong
        corrected = True
        return code8 ^ 0x80, corrected, double_error

    if syndrome != 0 and not overall_ok:
        # Single-bit error in 7-bit part
        pos = SYNDROME_TO_POS.get(syndrome)
        if pos is None:
            # Should not happen for this code; treat as uncorrectable
            double_error = True
            return code8, corrected, double_error
        corrected = True
        return code8 ^ (1 << pos), corrected, double_error

    # syndrome != 0 and overall_ok
    double_error = True
    return code8, corrected, double_error


def decode_nibble(code8: int) -> tuple[int, bool]:
    """
    Decode one (8,4) codeword into a 4-bit nibble.
    Returns (nibble, double_error_detected).
    """
    corrected_code8, _, double_err = correct_codeword(code8)
    code7 = corrected_code8 & 0x7F
    nibble = (code7 >> G_DEG) & 0xF
    return nibble, double_err


def main() -> int:
    if len(sys.argv) != 3:
        print("Usage: decoder in out", file=sys.stderr)
        return 2

    in_path, out_path = sys.argv[1], sys.argv[2]

    with open(in_path, "rb") as f_in:
        data = f_in.read()

    if len(data) < 2:
        # Not enough for even a single original byte (needs 2 codewords)
        with open(out_path, "wb") as f_out:
            f_out.write(b"")
        print("Double-error blocks: 0")
        return 0

    # Decode each byte -> one nibble; pair nibbles -> one output byte
    nibbles = []
    double_error_count = 0

    for b in data:
        n, is_double = decode_nibble(b)
        nibbles.append(n)
        if is_double:
            double_error_count += 1

    out = bytearray()
    # Pair nibbles: (hi, lo) -> byte
    for i in range(0, len(nibbles) - 1, 2):
        out.append(((nibbles[i] & 0xF) << 4) | (nibbles[i + 1] & 0xF))

    with open(out_path, "wb") as f_out:
        f_out.write(out)

    print(f"Double-error blocks: {double_error_count}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
