G_DEG = 3
_G_POLY = 0b1011  # 1 + x + x^3 (LSB-first)


def mod_poly(dividend: int) -> int:
    """
    Return remainder of dividend(x) divided by g(x) over GF(2).
    dividend is treated as a 7-bit polynomial (bits for x^0..x^6).
    """
    v = dividend
    for i in range(6, G_DEG - 1, -1):
        if (v >> i) & 1:
            v ^= _G_POLY << (i - G_DEG)
    return v & ((1 << G_DEG) - 1)  # 3-bit remainder
