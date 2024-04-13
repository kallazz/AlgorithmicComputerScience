from dataclasses import dataclass
from typing import Tuple


@dataclass
class DiophantineEquationSolution:
    x: int = 0
    y: int = 0


def factorial(n: int) -> int:
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result


def factorial_recursive(n: int) -> int:
    if n <= 1:
        return 1
    return n * factorial_recursive(n - 1)


def gcd(a: int, b: int) -> int:
    if b == 0:
        return a
    while a % b > 0:
        r = a % b
        a = b
        b = r
    return b


def gcd_recursive(a: int, b: int) -> int:
    if b != 0:
        return gcd_recursive(b, a % b)
    return a


def gcd_extended(a: int, b: int) -> Tuple[int, int, int]:
    x_prev, y_prev, x_curr, y_curr = 1, 0, 0, 1

    while b != 0:
        quotient = a // b

        temp = b
        b = a % b
        a = temp

        temp = x_prev - quotient * x_curr
        x_prev = x_curr
        x_curr = temp
        temp = y_prev - quotient * y_curr
        y_prev = y_curr
        y_curr = temp

    return a, x_prev, y_prev


def gcd_extended_recursive(a: int, b: int) -> Tuple[int, int, int]:
    if a == 0:
        x = 0
        y = 1
        return b, x, y

    gcd_result, x1, y1 = gcd_extended_recursive(b % a, a)
    x = y1 - (b // a) * x1
    y = x1

    return gcd_result, x, y


def diophantine(a: int, b: int, c: int) -> DiophantineEquationSolution:
    if a == 0 and b == 0:
        return DiophantineEquationSolution

    gcd_result, x_solution, y_solution = gcd_extended(abs(a), abs(b))
    if c % gcd_result != 0:
        return DiophantineEquationSolution

    x_solution *= c // gcd_result
    y_solution *= c // gcd_result
    if a < 0:
        x_solution = -x_solution
    if b < 0:
        y_solution = -y_solution

    return DiophantineEquationSolution(x_solution, y_solution)


def diophantine_recursive(a: int, b: int, c: int) -> DiophantineEquationSolution:
    if a == 0 and b == 0:
        return DiophantineEquationSolution

    gcd_result, x_solution, y_solution = gcd_extended_recursive(abs(a), abs(b))
    if c % gcd_result != 0:
        return DiophantineEquationSolution

    x_solution *= c // gcd_result
    y_solution *= c // gcd_result
    if a < 0:
        x_solution = -x_solution
    if b < 0:
        y_solution = -y_solution

    return DiophantineEquationSolution(x_solution, y_solution)
