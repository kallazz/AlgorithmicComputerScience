package com.github.kallazz.diffiehellmankeyexchange;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class DHSetup<T extends AlgebraicField<T>> {
    private final int fieldCharacteristic;
    private final T generator;
    private final AlgebraicFieldConstructor<T> fieldConstructor;
    private final T one;

    @FunctionalInterface
    interface AlgebraicFieldConstructor<T extends AlgebraicField<T>> {
        T createInstance(long value);
    }

    public DHSetup(AlgebraicFieldConstructor<T> fieldConstructor) {
        this.fieldConstructor = fieldConstructor;
        this.one = fieldConstructor.createInstance(1); 
        this.fieldCharacteristic = this.one.getCharacteristic();
        this.generator = generateGenerator();
    }

    public T getGenerator() {
        return this.generator;
    }

    public T power(T a, long b) {
        T result = this.one;

        while (b > 0) {
            if ((b & 1) == 1) {
                result = result.multiply(a);
            }
            b >>= 1;
            a = a.multiply(a);
        }

        return result;
    }

    private T generateGenerator() {
        Random randomNumberGenerator = new Random();
        final int lowerBound = 1;
        final int upperBound = fieldCharacteristic;

        T generator = this.fieldConstructor.createInstance(randomNumberGenerator.nextInt(upperBound) + lowerBound);
        while (!isGenerator(generator)) {
            generator = this.fieldConstructor.createInstance(randomNumberGenerator.nextInt(upperBound) + lowerBound);
        }
        return generator;
    }

    private boolean isGenerator(T generator) {
        final int p = this.fieldCharacteristic;
        final List<Integer> primeFactors = getPrimeFactors(p - 1);

        for (final int q : primeFactors) {
            if (power(generator, (p - 1) / q).fieldEquals(this.one)) {
                return false;
            }
        }

        return true;
    }

    private boolean isPrime(int number) {
        if (number <= 1) {
            return false;
        }

        for (int i = 2; i <= Math.sqrt(number); i++) {
            if (number % i == 0) {
                return false;
            }
        }

        return true;
    }

    private List<Integer> getPrimeFactors(int number) {
        List<Integer> primeFactors = new ArrayList<>();
        for (int i = 2; i <= Math.sqrt(number); i++) {
            if (number % i == 0 && isPrime(i)) {
                primeFactors.add(i);
            }
        }
        return primeFactors;
    }
}
