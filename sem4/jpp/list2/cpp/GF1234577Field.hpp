#ifndef GF_1234577_FIELD_HPP
#define GF_1234577_FIELD_HPP

#include <compare>
#include <iostream>

class GF1234577Field {
public:
    GF1234577Field(const long long value = 0);

    static int getCharacteristic() { return CHARACTERISTIC_; }
    long long getValue() const;

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
    static constexpr int CHARACTERISTIC_ = 1234577;
    long long value_;

    long long getModularInverse(long long number) const;
};

#endif // GF_1234577_FIELD_HPP
