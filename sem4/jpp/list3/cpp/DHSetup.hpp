#ifndef DHS_SETUP_HPP
#define DHS_SETUP_HPP

#include <cmath>
#include <random>
#include <vector>


template<typename T>
class DHSetup {
public:
    DHSetup();
    T getGenerator() const;
    T power(T a, unsigned long b) const;
private:
    const int fieldCharacteristic_;
    const T generator_;

    T generateGenerator();
    bool isGenerator(const T &generator) const;
    bool isPrime(const int number) const;
    std::vector<int> getPrimeFactors(const int number) const;
};


template<typename T>
DHSetup<T>::DHSetup() : fieldCharacteristic_(T::getCharacteristic()), generator_(generateGenerator()) {}

template<typename T>
T DHSetup<T>::getGenerator() const {
    return generator_;
}

template<typename T>
T DHSetup<T>::power(T a, unsigned long b) const {
    T result = 1;

    while (b > 0) {
        if (b & 1) {
            result = result * a;
        }

        b = b >> 1;
        a = a * a;
    }

    return result;
}

template<typename T>
T DHSetup<T>::generateGenerator() {
    std::mt19937 randomNumberGenerator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(1, fieldCharacteristic_ - 1);

    T generator = distribution(randomNumberGenerator);
    while (!isGenerator(generator)) {
        generator = distribution(randomNumberGenerator);
    }
    return generator;
}

template<typename T>
bool DHSetup<T>::isGenerator(const T &generator) const {
    const int p = fieldCharacteristic_;
    const std::vector<int> primeFactors = getPrimeFactors(p - 1);

    for (const int &q : primeFactors) {
        if (power(generator, (p - 1) / q) == 1) {
            return false;
        }
    }

    return true;
}

template<typename T>
bool DHSetup<T>::isPrime(const int number) const {
    if (number <= 1) {
        return false;
    }

    for (int i = 2; i <= sqrt(number); i++) {
        if (number % i == 0) {
            return false;
        }
    }

    return true;
}

template<typename T>
std::vector<int> DHSetup<T>::getPrimeFactors(const int number) const {
    std::vector<int> primeFactors;
    for (int i = 2; i <= sqrt(number); i++) {
        if ((number % i == 0) && isPrime(i)) {
            primeFactors.push_back(i);
        }
    }
    return primeFactors;
}


#endif // DHS_SETUP_HPP
