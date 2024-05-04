#ifndef USER_HPP
#define USER_HPP

#include "DHSetup.hpp"

#include <random>
#include <stdexcept>


template<typename T>
class User {
public:
    User(const DHSetup<T> &dhSetup);
    T getPublicKey() const;
    void setKey(T a);
    T encrypt(T m) const;
    T decrypt(T c) const;
private:
    const DHSetup<T> &dhSetup_;
    const unsigned long secret_;
    const T publicKey_;
    T encryptionKey_ {0};

    unsigned long generateSecret() const;
    T generatePublicKey() const;
};


template<typename T>
User<T>::User(const DHSetup<T> &dhSetup) : dhSetup_(dhSetup), secret_(generateSecret()), publicKey_(generatePublicKey()) {}

template<typename T>
T User<T>::getPublicKey() const {
    return publicKey_;
}

template<typename T>
void User<T>::setKey(T a) {
    encryptionKey_ = dhSetup_.power(a, secret_);
}

template<typename T>
T User<T>::encrypt(T m) const {
    if (encryptionKey_ == 0) {
        throw std::runtime_error("Encryption key was not initialized!");
    }
    return m * encryptionKey_;
};

template<typename T>
T User<T>::decrypt(T c) const {
    if (encryptionKey_ == 0) {
        throw std::runtime_error("Encryption key was not initialized!");
    }
    return c / encryptionKey_;
};

template<typename T>
unsigned long User<T>::generateSecret() const {
    std::mt19937 randomNumberGenerator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(1, T::getCharacteristic() - 1);
    return distribution(randomNumberGenerator);
}

template<typename T>
T User<T>::generatePublicKey() const {
    return dhSetup_.power(dhSetup_.getGenerator(), secret_);
};

#endif // USER_HPP
