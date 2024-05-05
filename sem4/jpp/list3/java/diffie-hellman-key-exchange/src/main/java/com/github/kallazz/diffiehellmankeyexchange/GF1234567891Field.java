package com.github.kallazz.diffiehellmankeyexchange;

public class GF1234567891Field implements AlgebraicField<GF1234567891Field> {
    private static final int CHARACTERISTIC = 1234567891;
    private long value;

    public GF1234567891Field(final long value) {
        this.value = value % CHARACTERISTIC;
        if (this.value < 0) {
            this.value += CHARACTERISTIC;
        }
    }

    public GF1234567891Field(final int value) {
        this.value = value % CHARACTERISTIC;
        if (this.value < 0) {
            this.value += CHARACTERISTIC;
        }
    }

    @Override
    public int getCharacteristic() {
        return CHARACTERISTIC;
    }

    @Override
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

    @Override
    public boolean fieldEquals(GF1234567891Field other) {
        return value == other.value;
    }

    @Override
    public boolean notEquals(GF1234567891Field other) {
        return value != other.value;
    }

    @Override
    public boolean lessThan(GF1234567891Field other) {
        return value < other.value;
    }

    @Override
    public boolean lessThanOrEqual(GF1234567891Field other) {
        return value <= other.value;
    }

    @Override
    public boolean greaterThan(GF1234567891Field other) {
        return value > other.value;
    }

    @Override
    public boolean greaterThanOrEqual(GF1234567891Field other) {
        return value >= other.value;
    }

    @Override
    public GF1234567891Field add(GF1234567891Field other) {
        return new GF1234567891Field((value + other.value) % getCharacteristic());
    }

    @Override
    public GF1234567891Field subtract(GF1234567891Field other) {
        return new GF1234567891Field((value - other.value) % getCharacteristic());
    }

    @Override
    public GF1234567891Field multiply(GF1234567891Field other) {
        return new GF1234567891Field((value * other.value) % getCharacteristic());
    }

    @Override
    public GF1234567891Field divide(GF1234567891Field other) {
        if (other.value == 0) {
            throw new IllegalArgumentException("Division by 0!");
        }
        final long inverse = getModularInverse(other.value);
        return new GF1234567891Field((value * inverse) % getCharacteristic());
    }

    @Override
    public GF1234567891Field assign(GF1234567891Field other) {
        value = other.value;
        return this;
    }

    @Override
    public GF1234567891Field assignAdd(GF1234567891Field other) {
        value = (value + other.value) % getCharacteristic();
        return this;
    }

    @Override
    public GF1234567891Field assignSubtract(GF1234567891Field other) {
        value = (value - other.value) % getCharacteristic();
        if (value < 0) {
            value += getCharacteristic();
        } 
        return this;
    }

    @Override
    public GF1234567891Field assignMultiply(GF1234567891Field other) {
        value = (value * other.value) % getCharacteristic();
        return this;
    }

    @Override
    public GF1234567891Field assignDivide(GF1234567891Field other) {
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

    @Override
    public int intValue() {
        return (int) value;
    }

    @Override
    public float floatValue() {
        return (float) value;
    }

    @Override
    public double doubleValue() {
        return (double) value;
    }
};
