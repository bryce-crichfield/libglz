#pragma once
#include "v2.h"
#include <string>
namespace gl {
struct v3 {
    float data[4] = {0, 0, 0, 1};
    float& x = data[0];
    float& y = data[1];
    float& z = data[2];
    float& r = data[0];
    float& g = data[1];
    float& b = data[2];
    float& s = data[0];
    float& t = data[1];
    float& u = data[2];

    // New Constructors
    v3() = default;
    v3(float x);
    v3(float x, float y);
    v3(float x, float y, float z);
    // V2 Compatibility Constructors
    v3(const v2& that);
    v3(const v2& that, float z);
    // Copy and Move Constructors
    v3(const v3& other);
    v3(const v3&& other);
    v3& operator=(const v3& other);
    v3& operator=(const v3&& other);
    // Destructor
    ~v3() = default;

    // Mutable Arithmetic
    v3& operator+=(const v3& other);
    v3& operator-=(const v3& other);
    v3& operator*=(const v3& other);
    v3& operator/=(const v3& other);
    v3& operator+=(float scalar);
    v3& operator-=(float scalar);
    v3& operator*=(float scalar);
    v3& operator/=(float scalar);

    // Immutable Arithmetic
    v3 operator+(const v3& other) const;
    v3 operator-(const v3& other) const;
    v3 operator*(const v3& other) const;
    v3 operator/(const v3& other) const;
    v3 operator+(float scalar) const;
    v3 operator-(float scalar) const;
    v3 operator*(float scalar) const;
    v3 operator/(float scalar) const;

    // Comparison Operators
    bool operator==(const v3& other) const;
    bool operator!=(const v3& other) const;

    // Linear and Geometric Functions
    float dot(const v3& other) const;
    float angle(const v3& other) const;
    float length() const;
    v3 cross(const v3& other) const;
    v3 normalize() const;
    v3 reflect(const v3& normal) const;
    v3 lerp(const v3& other, float t) const;

    std::string to_string() const;
}; // struct v3
} // namespace gl