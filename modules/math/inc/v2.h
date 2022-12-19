#pragma once
#include <string>
namespace gl {
struct v2 {
    float data[4] = {0, 0, 0, 1};
    float& x = data[0];
    float& y = data[1];
    float& s = data[0];
    float& t = data[1];

    // New Constructors
    v2() = default;
    v2(float x);
    v2(float x, float y);
    // Copy and Move Constructors
    v2(const v2& other);
    v2(const v2&& other);
    v2& operator=(const v2& other);
    v2& operator=(const v2&& other);
    // Destructor
    ~v2() = default;

    // Mutable Arithmetic
    v2& operator+=(const v2& other);
    v2& operator-=(const v2& other);
    v2& operator*=(const v2& other);
    v2& operator/=(const v2& other);
    v2& operator+=(float scalar);
    v2& operator-=(float scalar);
    v2& operator*=(float scalar);
    v2& operator/=(float scalar);

    // Immutable Arithmetic
    v2 operator+(const v2& other) const;
    v2 operator-(const v2& other) const;
    v2 operator*(const v2& other) const;
    v2 operator/(const v2& other) const;
    v2 operator+(float scalar) const;
    v2 operator-(float scalar) const;
    v2 operator*(float scalar) const;
    v2 operator/(float scalar) const;

    // Comparison Operators
    bool operator==(const v2& other) const;
    bool operator!=(const v2& other) const;

    // Linear and Geometric Functions
    float dot(const v2& other) const;
    float angle(const v2& other) const;
    float length() const;
    v2 normalize() const;
    v2 reflect(const v2& normal) const;
    v2 lerp(const v2& other, float t) const;

    std::string to_string() const;
}; // struct v2
} // namespace gl