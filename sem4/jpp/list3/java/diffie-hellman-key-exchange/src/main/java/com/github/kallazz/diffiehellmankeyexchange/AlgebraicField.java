package com.github.kallazz.diffiehellmankeyexchange;

public interface AlgebraicField<T> {
    int getCharacteristic();
    long getValue();

    boolean fieldEquals(T other);
    boolean notEquals(T other);
    boolean lessThan(T other);
    boolean lessThanOrEqual(T other);
    boolean greaterThan(T other);
    boolean greaterThanOrEqual(T other);

    T add(T other);
    T subtract(T other);
    T multiply(T other);
    T divide(T other);

    T assign(T other);
    T assignAdd(T other);
    T assignSubtract(T other);
    T assignMultiply(T other);
    T assignDivide(T other);

    int intValue();
    float floatValue();
    double doubleValue();

    String toString();
}
