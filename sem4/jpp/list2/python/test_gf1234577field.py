import pytest
from gf1234577field import GF1234577Field

CHARACTERISTIC = 1234577


class TestGF1234577Field:
    # Initialization
    def test_initialization(self):
        field = GF1234577Field(10)
        assert field.value == 10

    def test_initialization_with_negative_number(self):
        field = GF1234577Field(-10)
        assert field.value == CHARACTERISTIC - 10

    # Comparison operators
    def test_equal_operator_true(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(10)
        result = field1 == field2
        assert result == True

    def test_equal_operator_false(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(5)
        result = field1 == field2
        assert result == False

    def test_not_equal_operator_true(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(5)
        result = field1 != field2
        assert result == True

    def test_not_equal_operator_false(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(10)
        result = field1 != field2
        assert result == False

    def test_less_than_operator_true(self):
        field1 = GF1234577Field(5)
        field2 = GF1234577Field(10)
        result = field1 < field2
        assert result == True

    def test_less_than_operator_false(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(5)
        result = field1 < field2
        assert result == False

    def test_less_than_or_equal_operator_true(self):
        field1 = GF1234577Field(5)
        field2 = GF1234577Field(10)
        result = field1 <= field2
        assert result == True

    def test_less_than_or_equal_operator_true_equal(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(10)
        result = field1 <= field2
        assert result == True

    def test_less_than_or_equal_operator_false(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(5)
        result = field1 <= field2
        assert result == False

    def test_greater_than_operator_true(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(5)
        result = field1 > field2
        assert result == True

    def test_greater_than_operator_false(self):
        field1 = GF1234577Field(5)
        field2 = GF1234577Field(10)
        result = field1 > field2
        assert result == False

    def test_greater_than_or_equal_operator_true(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(5)
        result = field1 >= field2
        assert result == True

    def test_greater_than_or_equal_operator_true_equal(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(10)
        result = field1 >= field2
        assert result == True

    def test_greater_than_or_equal_operator_false(self):
        field1 = GF1234577Field(5)
        field2 = GF1234577Field(10)
        result = field1 >= field2
        assert result == False

    # Arithmetic operators
    def test_addition_operator(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(5)
        result = field1 + field2
        assert result.value == 15

    def test_subtraction_operator(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(5)
        result = field1 - field2
        assert result.value == 5

    def test_multiplication_operator(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(5)
        result = field1 * field2
        assert result.value == 50

    def test_division_operator(self):
        field1 = GF1234577Field(1)
        field2 = GF1234577Field(2)
        result = field1 / field2
        assert result.value == 617289

    # Assignment operators
    def test_assignment_operator(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(5)
        field1 = field2
        assert field1.value == 5

    def test_assignment_addition_operator(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(5)
        field1 += field2
        assert field1.value == 15

    def test_assignment_subtraction_operator(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(5)
        field1 -= field2
        assert field1.value == 5

    def test_assignment_subtraction_operator_with_negative_number(self):
        field1 = GF1234577Field(5)
        field2 = GF1234577Field(10)
        field1 -= field2
        assert field1.value == CHARACTERISTIC - 5

    def test_assignment_multiplication_operator(self):
        field1 = GF1234577Field(10)
        field2 = GF1234577Field(5)
        field1 *= field2
        assert field1.value == 50

    def test_assignment_division_operator(self):
        field1 = GF1234577Field(1)
        field2 = GF1234577Field(2)
        field1 /= field2
        assert field1.value == 617289

    # Conversion operators
    def test_str_operator(self):
        field = GF1234577Field(10)
        assert str(field) == "10"

    def test_repr_operator(self):
        field = GF1234577Field(10)
        assert repr(field) == "GF1234577Field(10)"

    def test_int_operator(self):
        field = GF1234577Field(10)
        assert int(field) == 10

    def test_float_operator(self):
        field = GF1234577Field(10)
        assert float(field) == 10.0
