package com.github.kallazz.diffiehellmankeyexchange;

import java.util.Random;

public class User<T extends AlgebraicField<T>> {
    private final DHSetup<T> dhSetup;
    private final long secret;
    private final T publicKey;
    private T encryptionKey = null;

    public User(DHSetup<T> dhSetup) {
        this.dhSetup = dhSetup;
        this.secret = generateSecret();
        this.publicKey = generatePublicKey();
    }

    public T getPublicKey() {
        return this.publicKey;
    }

    public void setKey(T a) {
        this.encryptionKey = dhSetup.power(a, secret);
    }

    public T encrypt(T m) {
        if (encryptionKey == null) {
            throw new IllegalStateException("Encryption key was not initialized!");
        }
        return m.multiply(encryptionKey);
    }

    public T decrypt(T c) {
        if (encryptionKey == null) {
            throw new IllegalStateException("Encryption key was not initialized!");
        }
        return c.divide(encryptionKey);
    }

    private long generateSecret() {
        Random randomNumberGenerator = new Random();
        final int lowerBound = 1;
        final int upperBound = dhSetup.getGenerator().getCharacteristic();

        return randomNumberGenerator.nextInt(upperBound) + lowerBound;
    }

    private T generatePublicKey() {
        return dhSetup.power(dhSetup.getGenerator(), this.secret);
    }
}
