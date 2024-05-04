#include "GF1234567891Field.hpp"

#include <stdexcept>
#include <iostream>

GF1234567891Field::GF1234567891Field(const long long value) : value_(value % getCharacteristic()) {
    if (value_ < 0) {
        value_ += getCharacteristic();
    }
}

long long GF1234567891Field::getValue() const {
    return value_;
}

bool GF1234567891Field::operator==(const GF1234567891Field& other) const {
    return value_ == other.value_;
}

std::strong_ordering GF1234567891Field::operator<=>(const GF1234567891Field& other) const {
    return value_ <=> other.value_;
}

bool GF1234567891Field::operator==(const int other) const {
    return value_ == other;
}

std::strong_ordering GF1234567891Field::operator<=>(const int other) const {
    return value_ <=> other;
}

GF1234567891Field GF1234567891Field::operator+(const GF1234567891Field& other) const {
    return GF1234567891Field((value_ + other.value_) % getCharacteristic());
}

GF1234567891Field GF1234567891Field::operator-(const GF1234567891Field& other) const {
    return GF1234567891Field((value_ - other.value_) % getCharacteristic());
}

GF1234567891Field GF1234567891Field::operator*(const GF1234567891Field& other) const {
    return GF1234567891Field((value_ * other.value_) % getCharacteristic());
}

GF1234567891Field GF1234567891Field::operator/(const GF1234567891Field& other) const {
    if (other.value_ == 0) {
        throw std::invalid_argument("Division by 0!");
    }
    const int inverse = getModularInverse(other.value_);
    return GF1234567891Field((value_ * inverse) % getCharacteristic());
}

GF1234567891Field& GF1234567891Field::operator=(const GF1234567891Field& other) {
    value_ = other.value_;
    return *this;
}

GF1234567891Field& GF1234567891Field::operator+=(const GF1234567891Field& other) {
    value_ = (value_ + other.value_) % getCharacteristic();
    return *this;
}

GF1234567891Field& GF1234567891Field::operator-=(const GF1234567891Field& other) {
    value_ = (value_ - other.value_) % getCharacteristic();
    if (value_ < 0) {
        value_ += getCharacteristic();
    }
    return *this;
}

GF1234567891Field& GF1234567891Field::operator*=(const GF1234567891Field& other) {
    value_ = (value_ * other.value_) % getCharacteristic();
    return *this;
}

GF1234567891Field& GF1234567891Field::operator/=(const GF1234567891Field& other) {
    if (other.value_ == 0) {
        throw std::invalid_argument("Division by 0!");
    }
    const int inverse = getModularInverse(other.value_);
    value_ = (value_ * inverse) % getCharacteristic();
    return *this;
}

std::ostream& operator<<(std::ostream& outputStream, const GF1234567891Field& field) {
    return outputStream << field.value_;
}

GF1234567891Field::operator int() const {
    return static_cast<int>(value_);
}

GF1234567891Field::operator float() const {
    return static_cast<float>(value_);
}

GF1234567891Field::operator double() const {
    return static_cast<double>(value_);
}

int GF1234567891Field::getModularInverse(int number) const {
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
