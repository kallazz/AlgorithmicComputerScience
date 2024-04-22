#include "GF1234577Field.hpp"

#include <stdexcept>
#include <iostream>

int GF1234577Field::getCharacteristic() const {
    return CHARACTERISTIC;
}

GF1234577Field::GF1234577Field(const int value) : value_(value % getCharacteristic()) {
    if (value_ < 0) {
        value_ += getCharacteristic();
    }
}

int GF1234577Field::getValue() const {
    return value_;
}

bool GF1234577Field::operator==(const GF1234577Field& other) const {
    return value_ == other.value_;
}

std::strong_ordering GF1234577Field::operator<=>(const GF1234577Field& other) const {
    return value_ <=> other.value_;
}

GF1234577Field GF1234577Field::operator+(const GF1234577Field& other) const {
    return GF1234577Field((value_ + other.value_) % getCharacteristic());
}

GF1234577Field GF1234577Field::operator-(const GF1234577Field& other) const {
    return GF1234577Field((value_ - other.value_) % getCharacteristic());
}

GF1234577Field GF1234577Field::operator*(const GF1234577Field& other) const {
    return GF1234577Field((value_ * other.value_) % getCharacteristic());
}

GF1234577Field GF1234577Field::operator/(const GF1234577Field& other) const {
    if (other.value_ == 0) {
        throw std::invalid_argument("Division by 0!");
    }
    const int inverse = getMultiplicativeInverse(other.value_);
    return GF1234577Field((value_ * inverse) % getCharacteristic());
}

GF1234577Field& GF1234577Field::operator=(const GF1234577Field& other) {
    value_ = other.value_;
    return *this;
}

GF1234577Field& GF1234577Field::operator+=(const GF1234577Field& other) {
    value_ = (value_ + other.value_) % getCharacteristic();
    return *this;
}

GF1234577Field& GF1234577Field::operator-=(const GF1234577Field& other) {
    value_ = (value_ - other.value_) % getCharacteristic();
    if (value_ < 0) {
        value_ += getCharacteristic();
    }
    return *this;
}

GF1234577Field& GF1234577Field::operator*=(const GF1234577Field& other) {
    value_ = (value_ * other.value_) % getCharacteristic();
    return *this;
}

GF1234577Field& GF1234577Field::operator/=(const GF1234577Field& other) {
    if (other.value_ == 0) {
        throw std::invalid_argument("Division by 0!");
    }
    const int inverse = getMultiplicativeInverse(other.value_);
    value_ = (value_ * inverse) % getCharacteristic();
    return *this;
}

std::ostream& operator<<(std::ostream& outputStream, const GF1234577Field& field) {
    return outputStream << field.value_;
}

GF1234577Field::operator int() const {
    return value_;
}

GF1234577Field::operator float() const {
    return static_cast<float>(value_);
}

GF1234577Field::operator double() const {
    return static_cast<double>(value_);
}

int GF1234577Field::getMultiplicativeInverse(int number) const {
    int modulo = getCharacteristic();
    const int originalModulo = modulo;
    int inverse = 0;
    int tempResult = 1;

    while (number > 1) {
        int quotient = number / modulo;
        int temp = modulo;
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
