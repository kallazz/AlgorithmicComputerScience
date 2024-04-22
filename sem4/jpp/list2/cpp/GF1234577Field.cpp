#include "GF1234577Field.hpp"

#include <stdexcept>
#include <iostream>

GF1234577Field::GF1234577Field(const int value) : value_(value % characteristic_) {
    if (value_ < 0) {
        value_ += characteristic_;
    }
}

int GF1234577Field::getCharacteristic() const {
    return characteristic_;
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
    return GF1234577Field((value_ + other.value_) % characteristic_);
}

GF1234577Field GF1234577Field::operator-(const GF1234577Field& other) const {
    return GF1234577Field((value_ - other.value_) % characteristic_);
}

GF1234577Field GF1234577Field::operator*(const GF1234577Field& other) const {
    return GF1234577Field((value_ * other.value_) % characteristic_);
}

GF1234577Field GF1234577Field::operator/(const GF1234577Field& other) const {
    if (other.value_ == 0) {
        throw std::invalid_argument("Division by 0!");
    }
    const int inverse = getMultiplicativeInverse(other.value_);
    return GF1234577Field((value_ * inverse) % characteristic_);
}

GF1234577Field& GF1234577Field::operator=(const GF1234577Field& other) {
    value_ = other.value_;
    return *this;
}

GF1234577Field& GF1234577Field::operator+=(const GF1234577Field& other) {
    value_ = (value_ + other.value_) % characteristic_;
    return *this;
}

GF1234577Field& GF1234577Field::operator-=(const GF1234577Field& other) {
    value_ = (value_ - other.value_) % characteristic_;
    if (value_ < 0) {
        value_ += characteristic_;
    }
    return *this;
}

GF1234577Field& GF1234577Field::operator*=(const GF1234577Field& other) {
    value_ = (value_ * other.value_) % characteristic_;
    return *this;
}

GF1234577Field& GF1234577Field::operator/=(const GF1234577Field& other) {
    if (other.value_ == 0) {
        throw std::invalid_argument("Division by 0!");
    }
    const int inverse = getMultiplicativeInverse(other.value_);
    value_ = (value_ * inverse) % characteristic_;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const GF1234577Field& field) {
    return os << field.value_;
}

int GF1234577Field::getMultiplicativeInverse(int number) const {
    int modulo = characteristic_;
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
