#include "DHSetup.hpp"
#include "GF1234567891Field.hpp"
#include "User.hpp"

#include <iostream>

int main() {
    DHSetup<GF1234567891Field> dhSetup;
    std::cout << "Generator: " << dhSetup.getGenerator() << '\n';

    User<GF1234567891Field> alice(dhSetup);
    User<GF1234567891Field> bob(dhSetup);
    GF1234567891Field alicePublicKey = alice.getPublicKey();
    GF1234567891Field bobPublicKey = bob.getPublicKey();
    std::cout << "Alice's public key: " << alicePublicKey << '\n';
    std::cout << "Bob's public key: " << bobPublicKey << '\n';

    alice.setKey(bobPublicKey);
    bob.setKey(alicePublicKey);

    GF1234567891Field message = 123;
    GF1234567891Field encryptedMessage = alice.encrypt(message);
    GF1234567891Field decryptedMessage = bob.decrypt(encryptedMessage);

    std::cout << "Original Message: " << message << '\n';
    std::cout << "Encrypted Message: " << encryptedMessage << '\n';
    std::cout << "Decrypted Message: " << decryptedMessage << '\n';

    return 0;
}
