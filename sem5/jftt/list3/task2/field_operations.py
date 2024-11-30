def field_add(a: int, b: int, field_characteristic: int) -> int:
    return (a + b) % field_characteristic


def field_sub(a: int, b: int, field_characteristic: int) -> int:
    return (a - b + field_characteristic) % field_characteristic


def field_mul(a: int, b: int, field_characteristic: int) -> int:
    return (a * b) % field_characteristic


def field_div(a: int, b: int, field_characteristic: int) -> int:
    return (a * field_pow(b, field_characteristic - 2, field_characteristic)) % field_characteristic


def field_pow(a: int, b: int, field_characteristic: int) -> int:
    result = 1
    while b > 0:
        if b % 2 == 1:
            result = field_mul(result, a, field_characteristic)
        a = field_mul(a, a, field_characteristic)
        b //= 2
    return result
