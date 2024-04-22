#ifndef GF_1234577_FIELD_HPP
#define GF_1234577_FIELD_HPP

#include <compare>
#include <iostream>

class GF1234577Field {
public:
    static const int CHARACTERISTIC = 1234577;
    int getCharacteristic() const;
    int getValue() const;

    GF1234577Field(const int value = 0);

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

    friend std::ostream& operator<<(std::ostream& outputStream, const GF1234577Field& field);

    operator int() const;
    operator float() const;
    operator double() const;
private:
    int value_;

    int getModularInverse(int number) const;
};

#endif // GF_1234577_FIELD_HPP
