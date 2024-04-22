#include "GF1234577Field.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

const int CHARACTERISTIC = 1234577;

// Initialization
void testInitialization() {
    GF1234577Field field = GF1234577Field(10);
    assert(field.getValue() == 10);
}

void testInitializationWithNegativeNumber() {
    GF1234577Field field = GF1234577Field(-10);
    assert(field.getValue() == CHARACTERISTIC - 10);
}

// Comparison operators
void testEqualOperatorTrue() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(10);

    bool result = (field1 == field2);
    assert(result == true);
}

void testEqualOperatorFalse() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(5);
    bool result = (field1 == field2);
    assert(result == false);
}

void testNotEqualOperatorTrue() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(5);
    bool result = (field1 != field2);
    assert(result == true);
}

void testNotEqualOperatorFalse() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(10);
    bool result = (field1 != field2);
    assert(result == false);
}

void testLessThanOperatorTrue() {
    GF1234577Field field1 = GF1234577Field(5);
    GF1234577Field field2 = GF1234577Field(10);
    bool result = (field1 < field2);
    assert(result == true);
}

void testLessThanOperatorFalse() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(5);
    bool result = (field1 < field2);
    assert(result == false);
}

void testLessThanOrEqualOperatorTrue() {
    GF1234577Field field1 = GF1234577Field(5);
    GF1234577Field field2 = GF1234577Field(10);
    bool result = (field1 <= field2);
    assert(result == true);
}

void testLessThanOrEqualOperatorTrueEqual() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(10);
    bool result = (field1 <= field2);
    assert(result == true);
}

void testLessThanOrEqualOperatorFalse() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(5);
    bool result = (field1 <= field2);
    assert(result == false);
}

void testGreaterThanOperatorTrue() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(5);
    bool result = (field1 > field2);
    assert(result == true);
}

void testGreaterThanOperatorFalse() {
    GF1234577Field field1 = GF1234577Field(5);
    GF1234577Field field2 = GF1234577Field(10);
    bool result = (field1 > field2);
    assert(result == false);
}

void testGreaterThanOrEqualOperatorTrue() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(5);
    bool result = (field1 >= field2);
    assert(result == true);
}

void testGreaterThanOrEqualOperatorTrueEqual() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(10);
    bool result = (field1 >= field2);
    assert(result == true);
}

void testGreaterThanOrEqualOperatorFalse() {
    GF1234577Field field1 = GF1234577Field(5);
    GF1234577Field field2 = GF1234577Field(10);
    bool result = (field1 >= field2);
    assert(result == false);
}

// Arithmetic operators
void testAdditionOperator() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(5);
    GF1234577Field result = field1 + field2;
    assert(result.getValue() == 15);
}

void testSubtractionOperator() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(5);
    GF1234577Field result = field1 - field2;
    assert(result.getValue() == 5);
}

void testMultiplicationOperator() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(5);
    GF1234577Field result = field1 * field2;
    assert(result.getValue() == 50);
}

void testDivisionOperator() {
    GF1234577Field field1 = GF1234577Field(1);
    GF1234577Field field2 = GF1234577Field(2);
    GF1234577Field result = field1 / field2;
    assert(result.getValue() == 617289);
}

// Assignment operators
void testAssignmentOperator() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(5);
    field1 = field2;
    assert(field1.getValue() == 5);
}

void testAssignmentAdditionOperator() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(5);
    field1 += field2;
    assert(field1.getValue() == 15);
}

void testAssignmentSubtractionOperator() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(5);
    field1 -= field2;
    assert(field1.getValue() == 5);
}

void testAssignmentSubtractionOperatorWithNegativeNumber() {
    GF1234577Field field1 = GF1234577Field(5);
    GF1234577Field field2 = GF1234577Field(10);
    field1 -= field2;
    assert(field1.getValue() == CHARACTERISTIC - 5);
}

void testAssignmentMultiplicationOperator() {
    GF1234577Field field1 = GF1234577Field(10);
    GF1234577Field field2 = GF1234577Field(5);
    field1 *= field2;
    assert(field1.getValue() == 50);
}

void testAssignmentDivisionOperator() {
    GF1234577Field field1 = GF1234577Field(1);
    GF1234577Field field2 = GF1234577Field(2);
    field1 /= field2;
    assert(field1.getValue() == 617289);
}

// Output stream operator
void testOutputStreamOperator() {
    GF1234577Field field = GF1234577Field(10);
    std::stringstream out;
    out << field;
    assert(out.str() == "10");
}

// Conversion operators
void testIntOperator() {
    GF1234577Field field = GF1234577Field(10);
    assert(int(field) == 10);
}

void testFloatOperator() {
    GF1234577Field field = GF1234577Field(10);
    assert(float(field) == 10.0f);
}

void testDoubleOperator() {
    GF1234577Field field = GF1234577Field(10);
    assert(double(field) == 10.0);
}


int main() {
    testInitialization();
    testInitializationWithNegativeNumber();

    testEqualOperatorTrue();
    testEqualOperatorFalse();
    testNotEqualOperatorTrue();
    testNotEqualOperatorFalse();
    testLessThanOperatorTrue();
    testLessThanOperatorFalse();
    testLessThanOrEqualOperatorTrue();
    testLessThanOrEqualOperatorTrueEqual();
    testLessThanOrEqualOperatorFalse();
    testGreaterThanOperatorTrue();
    testGreaterThanOperatorFalse();
    testGreaterThanOrEqualOperatorTrue();
    testGreaterThanOrEqualOperatorTrueEqual();
    testGreaterThanOrEqualOperatorFalse();

    testAdditionOperator();
    testSubtractionOperator();
    testMultiplicationOperator();
    testDivisionOperator();

    testAssignmentOperator();
    testAssignmentAdditionOperator();
    testAssignmentSubtractionOperator();
    testAssignmentSubtractionOperatorWithNegativeNumber();
    testAssignmentMultiplicationOperator();
    testAssignmentDivisionOperator();

    testOutputStreamOperator();

    testIntOperator();
    testFloatOperator();
    testDoubleOperator();

    std::cout << "All tests passed!\n"; 
}
