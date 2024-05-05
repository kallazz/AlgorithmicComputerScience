from gf1234567891field import GF1234567891Field
from dh_setup import DHSetup
from user import User


def main() -> None:
    dh_setup = DHSetup(GF1234567891Field)
    print(f"Generator: {dh_setup.generator}")

    alice = User(dh_setup)
    bob = User(dh_setup)
    alice_public_key = alice.public_key
    bob_public_key = bob.public_key
    print(f"Alice's public key: {alice_public_key}")
    print(f"Bob's public key: {bob_public_key}")

    alice.set_key(bob_public_key)
    bob.set_key(alice_public_key)

    message = GF1234567891Field(123)
    encryptedMessage = alice.encrypt(message)
    decryptedMessage = bob.decrypt(encryptedMessage)

    print(f"Original Message: {message}")
    print(f"Encrypted Message: {encryptedMessage}")
    print(f"Decrypted Message: {decryptedMessage}")


if __name__ == "__main__":
    main()
