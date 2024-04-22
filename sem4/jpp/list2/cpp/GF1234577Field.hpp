#ifndef GF_1234577_FIELD_HPP
#define GF_1234577_FIELD_HPP

#include <compare>
#include <iostream>

class GF1234577Field {
public:
    GF1234577Field(const int value = 0);
    int getCharacteristic() const;
    int getValue() const;

    bool operator==(const GF1234577Field& other) const;
    std::strong_ordering operator<=>(const GF1234577Field& other) const;

    GF1234577Field operator+(const GF1234577Field& other) const;
    GF1234577Field operator-(const GF1234577Field& other) const;
    GF1234577Field operator*(const GF1234577Field& other) const;
    GF1234577Field operator/(const GF1234577Field& other) const;

    GF1234577Field& operator=(const GF1234577Field& other);
    GF1234577Field& operator+=(const GF1234577Field& other);
    GF1234577Field& operator-=(const GF1234577Field& other);
    GF1234577Field& operator*=(const GF1234577Field& other);
    GF1234577Field& operator/=(const GF1234577Field& other);

    friend std::ostream& operator<<(std::ostream& os, const GF1234577Field& field);

private:
    const int characteristic_ = 1234577;
    int value_;

    int getMultiplicativeInverse(int number) const;
};

#endif // GF_1234577_FIELD_HPP
