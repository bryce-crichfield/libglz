#pragma once
#include "v2.h"
#include "v3.h"
#include "v4.h"
#include <string>

namespace gl {
struct m4 {
    // A column-major 4x4 matrix
    float data[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    float& m00 = data[0];
    float& m01 = data[1];
    float& m02 = data[2];
    float& m03 = data[3];
    float& m10 = data[4];
    float& m11 = data[5];
    float& m12 = data[6];
    float& m13 = data[7];
    float& m20 = data[8];
    float& m21 = data[9];
    float& m22 = data[10];
    float& m23 = data[11];
    float& m30 = data[12];
    float& m31 = data[13];
    float& m32 = data[14];
    float& m33 = data[15];

    // New Constructors
    m4() = default;
    m4(float uniform);
    // Copy and Move Constructors
    m4(const m4& other);
    m4(const m4&& other);
    m4& operator=(const m4& other);
    m4& operator=(const m4&& other);

    // Destructor
    ~m4() = default;

    // Mutable Arithmetic
    m4& operator+=(const m4& other);
    m4& operator-=(const m4& other);
    m4& operator+=(float scalar);
    m4& operator-=(float scalar);
    m4& operator*=(float scalar);

    // Immutable Arithmetic
    m4 operator+(const m4& other) const;
    m4 operator-(const m4& other) const;
    m4 operator*(const m4& other) const;
    m4 operator+(float scalar) const;
    m4 operator-(float scalar) const;
    m4 operator*(float scalar) const;
    v4 operator*(const v2& vector) const;
    v4 operator*(const v3& vector) const;
    v4 operator*(const v4& vector) const;

    // Comparison Operators
    bool operator==(const m4& other) const;
    bool operator!=(const m4& other) const;

    // Linear Functions
    m4 transpose() const;
    m4 inverse() const;
    float determinant() const;

    // Geometric Functions
    static m4 translate(const v4& vector);
    static m4 rotate(float degrees, float x, float y, float z);
    static m4 lookAt(const v4& eye, const v4& center, const v4& up);
    static m4 perspective(float fov, float aspect, float near, float far);
    static m4 orthographic(float left, float right, float bottom, float top, float near, float far);

    // String Functions
    std::string to_string() const;
};
} // namespace gl