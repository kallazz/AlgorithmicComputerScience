package com.github.kallazz.diffiehellmankeyexchange;

public class Main {
    public static void main(String[] args) {
        DHSetup<GF1234567891Field> dhSetup = new DHSetup<>(GF1234567891Field::new);
        System.out.println("Generator: " + dhSetup.getGenerator());

        User<GF1234567891Field> alice = new User<>(dhSetup);
        User<GF1234567891Field> bob = new User<>(dhSetup);
        GF1234567891Field alicePublicKey = alice.getPublicKey();
        GF1234567891Field bobPublicKey = bob.getPublicKey();
        System.out.println("Alice's public key: " + alicePublicKey);
        System.out.println("Bob's public key: " + bobPublicKey);

        alice.setKey(bobPublicKey);
        bob.setKey(alicePublicKey);

        GF1234567891Field message = new GF1234567891Field(123); 
        GF1234567891Field encryptedMessage = alice.encrypt(message); 
        GF1234567891Field decryptedMessage = bob.decrypt(encryptedMessage); 

        System.out.println("Original Message: " + message);
        System.out.println("Encrypted Message: " + encryptedMessage);
        System.out.println("Decrypted Message: " + decryptedMessage);
    }
}
