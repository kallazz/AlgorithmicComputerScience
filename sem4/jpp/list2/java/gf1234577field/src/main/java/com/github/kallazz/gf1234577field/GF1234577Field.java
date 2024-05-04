package com.github.kallazz.gf1234577field;

public class GF1234577Field {
    private static final int CHARACTERISTIC = 1234577;
    private long value;

    public GF1234577Field(final long value) {
        this.value = value % CHARACTERISTIC;
        if (this.value < 0) {
            this.value += CHARACTERISTIC;
        }
    }

    public GF1234577Field(final int value) {
        this.value = value % CHARACTERISTIC;
        if (this.value < 0) {
            this.value += CHARACTERISTIC;
        }
    }

    public static int getCharacteristic() {
        return CHARACTERISTIC;
    }

    public long getValue() {
        return value;
    }

    private long getModularInverse(long number) {
        long modulo = getCharacteristic();
        final long originalModulo = modulo;
        long inverse = 0;
        long tempResult = 1;

        while (number > 1) {
            long quotient = number / modulo;
            long temp = modulo;
            modulo = number % modulo;
            number = temp;
            temp = inverse;
            inverse = tempResult - quotient * inverse;
            tempResult = temp;
        }

        if (tempResult < 0)
            tempResult += originalModulo;

        return tempResult;
    }

    public boolean equals(GF1234577Field other) {
        return value == other.value;
    }

    public boolean notEquals(GF1234577Field other) {
        return value != other.value;
    }

    public boolean lessThan(GF1234577Field other) {
        return value < other.value;
    }

    public boolean lessThanOrEqual(GF1234577Field other) {
        return value <= other.value;
    }

    public boolean greaterThan(GF1234577Field other) {
        return value > other.value;
    }

    public boolean greaterThanOrEqual(GF1234577Field other) {
        return value >= other.value;
    }

    public GF1234577Field add(GF1234577Field other) {
        return new GF1234577Field((value + other.value) % getCharacteristic());
    }

    public GF1234577Field subtract(GF1234577Field other) {
        return new GF1234577Field((value - other.value) % getCharacteristic());
    }

    public GF1234577Field multiply(GF1234577Field other) {
        return new GF1234577Field((value * other.value) % getCharacteristic());
    }

    public GF1234577Field divide(GF1234577Field other) {
        if (other.value == 0) {
            throw new IllegalArgumentException("Division by 0!");
        }
        final long inverse = getModularInverse(other.value);
        return new GF1234577Field((value * inverse) % getCharacteristic());
    }

    public GF1234577Field assign(GF1234577Field other) {
        value = other.value;
        return this;
    }

    public GF1234577Field assignAdd(GF1234577Field other) {
        value = (value + other.value) % getCharacteristic();
        return this;
    }

    public GF1234577Field assignSubtract(GF1234577Field other) {
        value = (value - other.value) % getCharacteristic();
        if (value < 0) {
            value += getCharacteristic();
        } 
        return this;
    }

    public GF1234577Field assignMultiply(GF1234577Field other) {
        value = (value * other.value) % getCharacteristic();
        return this;
    }

    public GF1234577Field assignDivide(GF1234577Field other) {
        if (other.value == 0) {
            throw new IllegalArgumentException("Divison by 0!");
        }
        final long inverse = getModularInverse(other.value);
        value = (value * inverse) % getCharacteristic();
        return this;
    }

    @Override
    public String toString() {
        return String.valueOf(value);
    }

    public int intValue() {
        return (int) value;
    }

    public float floatValue() {
        return (float) value;
    }

    public double doubleValue() {
        return (double) value;
    }
};
