package com.github.kallazz.gf1234577field;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class GF1234577FieldTest 
{
    final int CHARACTERISTIC = 1234577;

    // Initialization
    @Test
    public void testInitialization() {
        GF1234577Field field = new GF1234577Field(10);
        assertEquals(field.getValue(), 10);
    }

    @Test
    public void testInitializationWithNegativeNumber() {
        GF1234577Field field = new GF1234577Field(-10);
        assertEquals(field.getValue(), CHARACTERISTIC - 10);
    }

    // Comparison
    @Test
    public void testEqualsTrue() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(10);

        boolean result = (field1.equals(field2));
        assertTrue(result == true);
    }

    @Test
    public void testEqualsFalse() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(5);
        boolean result = (field1.equals(field2));
        assertTrue(result == false);
    }

    @Test
    public void testNotEqualsTrue() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(5);
        boolean result = (field1.notEquals(field2));
        assertTrue(result == true);
    }

    @Test
    public void testNotEqualsFalse() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(10);
        boolean result = (field1.notEquals(field2));
        assertTrue(result == false);
    }

    @Test
    public void testLessThanTrue() {
        GF1234577Field field1 = new GF1234577Field(5);
        GF1234577Field field2 = new GF1234577Field(10);
        boolean result = (field1.lessThan(field2));
        assertTrue(result == true);
    }

    @Test
    public void testLessThanFalse() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(5);
        boolean result = (field1.lessThan(field2));
        assertTrue(result == false);
    }

    @Test
    public void testLessThanOrEqualTrue() {
        GF1234577Field field1 = new GF1234577Field(5);
        GF1234577Field field2 = new GF1234577Field(10);
        boolean result = (field1.lessThanOrEqual(field2));
        assertTrue(result == true);
    }

    @Test
    public void testLessThanOrEqualTrueEqual() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(10);
        boolean result = (field1.lessThanOrEqual(field2));
        assertTrue(result == true);
    }

    @Test
    public void testLessThanOrEqualFalse() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(5);
        boolean result = (field1.lessThanOrEqual(field2));
        assertTrue(result == false);
    }

    @Test
    public void testGreaterThanTrue() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(5);
        boolean result = (field1.greaterThan(field2));
        assertTrue(result == true);
    }

    @Test
    public void testGreaterThanFalse() {
        GF1234577Field field1 = new GF1234577Field(5);
        GF1234577Field field2 = new GF1234577Field(10);
        boolean result = (field1.greaterThan(field2));
        assertTrue(result == false);
    }

    @Test
    public void testGreaterThanOrEqualTrue() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(5);
        boolean result = (field1.greaterThanOrEqual(field2));
        assertTrue(result == true);
    }

    @Test
    public void testGreaterThanOrEqualTrueEqual() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(10);
        boolean result = (field1.greaterThanOrEqual(field2));
        assertTrue(result == true);
    }

    @Test
    public void testGreaterThanOrEqualFalse() {
        GF1234577Field field1 = new GF1234577Field(5);
        GF1234577Field field2 = new GF1234577Field(10);
        boolean result = (field1.greaterThanOrEqual(field2));
        assertTrue(result == false);
    }

    // Arithmetic
    @Test
    public void testAddition() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(5);
        GF1234577Field result = field1.add(field2);
        assertEquals(result.getValue(), 15);
    }

    @Test
    public void testSubtraction() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(5);
        GF1234577Field result = field1.subtract(field2);
        assertEquals(result.getValue(), 5);
    }

    @Test
    public void testMultiplication() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(5);
        GF1234577Field result = field1.multiply(field2);
        assertEquals(result.getValue(), 50);
    }

    @Test
    public void testDivision() {
        GF1234577Field field1 = new GF1234577Field(1);
        GF1234577Field field2 = new GF1234577Field(2);
        GF1234577Field result = field1.divide(field2);
        assertEquals(result.getValue(), 617289);
    }

    // Assignment
    @Test
    public void testAssignment() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(5);
        field1.assign(field2);
        assertEquals(field1.getValue(), 5);
    }

    @Test
    public void testAssignmentAddition() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(5);
        field1.assignAdd(field2);
        assertEquals(field1.getValue(), 15);
    }

    @Test
    public void testAssignmentSubtraction() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(5);
        field1.assignSubtract(field2);
        assertEquals(field1.getValue(), 5);
    }

    @Test
    public void testAssignmentSubtractionWithNegativeNumber() {
        GF1234577Field field1 = new GF1234577Field(5);
        GF1234577Field field2 = new GF1234577Field(10);
        field1.assignSubtract(field2);
        assertEquals(field1.getValue(), CHARACTERISTIC - 5);
    }

    @Test
    public void testAssignmentMultiplication() {
        GF1234577Field field1 = new GF1234577Field(10);
        GF1234577Field field2 = new GF1234577Field(5);
        field1.assignMultiply(field2);
        assertEquals(field1.getValue(), 50);
    }

    @Test
    public void testAssignmentDivision() {
        GF1234577Field field1 = new GF1234577Field(1);
        GF1234577Field field2 = new GF1234577Field(2);
        field1.assignDivide(field2);
        assertEquals(field1.getValue(), 617289);
    }

    // toString
    @Test
    public void testToString() {
        GF1234577Field field = new GF1234577Field(10);
        assertEquals(field.toString(), "10");
    }

    // Conversion
    @Test
    public void testIntConversion() {
        GF1234577Field field = new GF1234577Field(10);
        assertEquals(field.intValue(), 10);
    }

    @Test
    public void testFloatConversion() {
        GF1234577Field field = new GF1234577Field(10);
        assertEquals(field.floatValue(), 10.0f, 0.0001);
    }

    @Test
    public void testDoubleConversion() {
        GF1234577Field field = new GF1234577Field(10);
        assertEquals(field.doubleValue(), 10.0, 0.0001);
    }
}
