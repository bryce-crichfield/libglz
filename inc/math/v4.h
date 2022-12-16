#pragma once
#include "v2.h"
#include "v3.h"
#include <string>
namespace gl {
struct v4 {
    float data[4] = {0, 0, 0, 1};
    float& x = data[0];
    float& y = data[1];
    float& z = data[2];
    float& w = data[3];
    float& r = data[0];
    float& g = data[1];
    float& b = data[2];
    float& a = data[3];
    float& s = data[0];
    float& t = data[1];
    float& u = data[2];
    float& v = data[3];

    // New Constructors
    v4() = default;
    v4(float x);
    v4(float x, float y);
    v4(float x, float y, float z);
    v4(float x, float y, float z, float w);
    // V2 Compatibility Constructors
    v4(const v2& that);
    v4(const v2& that, float z);
    v4(const v2& that, float z, float w);
    // V3 Compatibility Constructors
    v4(const v3& that);
    v4(const v3& that, float w);
    // Copy and Move Constructors
    v4(const v4& other);
    v4(const v4&& other);
    v4& operator=(const v4& other);
    v4& operator=(const v4&& other);
    // Destructor
    ~v4() = default;

    // Mutable Arithmetic
    v4& operator+=(const v4& other);
    v4& operator-=(const v4& other);
    v4& operator*=(const v4& other);
    v4& operator/=(const v4& other);
    v4& operator+=(float scalar);
    v4& operator-=(float scalar);
    v4& operator*=(float scalar);
    v4& operator/=(float scalar);

    // Immutable Arithmetic
    v4 operator+(const v4& other) const;
    v4 operator-(const v4& other) const;
    v4 operator*(const v4& other) const;
    v4 operator/(const v4& other) const;
    v4 operator+(float scalar) const;
    v4 operator-(float scalar) const;
    v4 operator*(float scalar) const;
    v4 operator/(float scalar) const;

    // Comparison Operators
    bool operator==(const v4& other) const;
    bool operator!=(const v4& other) const;

    // Linear and Geometric Functions
    float dot(const v4& other) const;
    float angle(const v4& other) const;
    float length() const;
    v4 cross(const v4& other) const;
    v4 normalize() const;
    v4 reflect(const v4& normal) const;
    v4 lerp(const v4& other, float t) const;

    std::string to_string() const;
}; // struct v4
} // namespace gl