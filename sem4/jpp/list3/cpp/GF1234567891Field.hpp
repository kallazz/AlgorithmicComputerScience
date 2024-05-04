#ifndef GF_1234567891_FIELD_HPP
#define GF_1234567891_FIELD_HPP

#include <compare>
#include <iostream>

class GF1234567891Field {
public:
    GF1234567891Field(const long long value = 0);

    static int getCharacteristic() { return CHARACTERISTIC_; }
    long long getValue() const;

    bool operator==(const GF1234567891Field& other) const;
    std::strong_ordering operator<=>(const GF1234567891Field& other) const;
    bool operator==(const int other) const;
    std::strong_ordering operator<=>(const int other) const;

    GF1234567891Field operator+(const GF1234567891Field& other) const;
    GF1234567891Field operator-(const GF1234567891Field& other) const;
    GF1234567891Field operator*(const GF1234567891Field& other) const;
    GF1234567891Field operator/(const GF1234567891Field& other) const;

    GF1234567891Field& operator=(const GF1234567891Field& other);
    GF1234567891Field& operator+=(const GF1234567891Field& other);
    GF1234567891Field& operator-=(const GF1234567891Field& other);
    GF1234567891Field& operator*=(const GF1234567891Field& other);
    GF1234567891Field& operator/=(const GF1234567891Field& other);

    friend std::ostream& operator<<(std::ostream& outputStream, const GF1234567891Field& field);

    operator int() const;
    operator float() const;
    operator double() const;
private:
    static constexpr int CHARACTERISTIC_ = 1234567891;
    long long value_;

    int getModularInverse(int number) const;
};

#endif // GF_1234567891_FIELD_HPP
