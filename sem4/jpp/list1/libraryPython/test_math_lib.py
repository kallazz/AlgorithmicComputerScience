import pytest

from math_lib import *


class TestMathLib:
    def validate_diophantine_result(
        self, a: int, b: int, c: int, solution: DiophantineEquationSolution
    ) -> None:
        if solution.x == 0 and solution.y == 0:
            assert (a == 0 and b == 0) or (c % gcd(a, b) != 0)
        else:
            assert a * solution.x + b * solution.y == c

    def test_factorial(self):
        expected_results = [1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800]
        for input, expected_result in enumerate(expected_results):
            assert factorial(input) == expected_result

    def test_factorial_recursive(self):
        expected_results = [1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800]
        for input, expected_result in enumerate(expected_results):
            assert factorial_recursive(input) == expected_result

    def test_gcd(self):
        inputs = [[0, 17], [17, 0], [3, 7], [10, 6], [15, 5], [24, 18], [75, 100]]
        expected_results = [17, 17, 1, 2, 5, 6, 25]
        for i in range(len(inputs)):
            a, b = inputs[i]
            assert gcd(a, b) == expected_results[i]

    def test_gcd_recursive(self):
        inputs = [[0, 17], [17, 0], [3, 7], [10, 6], [15, 5], [24, 18], [75, 100]]
        expected_results = [17, 17, 1, 2, 5, 6, 25]
        for i in range(len(inputs)):
            a, b = inputs[i]
            assert gcd_recursive(a, b) == expected_results[i]

    def test_diophantine(self):
        inputs = [
            [0, 0, 0],
            [0, 0, 5],
            [5, 0, 5],
            [0, 5, 5],
            [2, 4, 5],
            [6, -9, 29],
            [6, -9, 30],
            [-9, 6, 30],
            [2, -3, 10],
            [3, 2, 10],
            [4, 7, 19],
            [-6, -9, 10],
            [87, -64, 3],
            [137, 173, 99],
            [16, 7, 15],
            [195, 42, 12],
            [35, 10, 55],
        ]
        for a, b, c in inputs:
            solution = diophantine(a, b, c)
            self.validate_diophantine_result(a, b, c, solution)

    def test_diophantine_recursive(self):
        inputs = [
            [0, 0, 0],
            [0, 0, 5],
            [5, 0, 5],
            [0, 5, 5],
            [2, 4, 5],
            [6, -9, 29],
            [6, -9, 30],
            [-9, 6, 30],
            [2, -3, 10],
            [3, 2, 10],
            [4, 7, 19],
            [-6, -9, 10],
            [87, -64, 3],
            [137, 173, 99],
            [16, 7, 15],
            [195, 42, 12],
            [35, 10, 55],
        ]
        for a, b, c in inputs:
            solution = diophantine_recursive(a, b, c)
            self.validate_diophantine_result(a, b, c, solution)
