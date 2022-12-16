#include "math/v4.h"

#include <iomanip>
#include <math.h>
#include <sstream>
// New Constructors
gl::v4::v4(float x) {
    data[0] = x;
    data[1] = 0;
    data[2] = 0;
    data[3] = 1;
}
gl::v4::v4(float x, float y) {
    data[0] = x;
    data[1] = y;
    data[2] = 0;
    data[3] = 1;
}
gl::v4::v4(float x, float y, float z) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
    data[3] = 1;
}
gl::v4::v4(float x, float y, float z, float w) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
    data[3] = w;
}
// V2 Compatibility Constructors
gl::v4::v4(const gl::v2& that) {
    data[0] = that.data[0];
    data[1] = that.data[1];
    data[2] = 0;
    data[3] = 1;
}
gl::v4::v4(const gl::v2& that, float z) {
    data[0] = that.data[0];
    data[1] = that.data[1];
    data[2] = z;
    data[3] = 1;
}
gl::v4::v4(const gl::v2& that, float z, float w) {
    data[0] = that.data[0];
    data[1] = that.data[1];
    data[2] = z;
    data[3] = w;
}
// V3 Compatibility Constructors
gl::v4::v4(const gl::v3& that) {
    data[0] = that.data[0];
    data[1] = that.data[1];
    data[2] = that.data[2];
    data[3] = 1;
}
gl::v4::v4(const gl::v3& that, float w) {
    data[0] = that.data[0];
    data[1] = that.data[1];
    data[2] = that.data[2];
    data[3] = w;
}
// Copy and Move Constructors
gl::v4::v4(const gl::v4& other) {
    data[0] = other.data[0];
    data[1] = other.data[1];
    data[2] = other.data[2];
    data[3] = other.data[3];
}
gl::v4::v4(const gl::v4&& other) {
    data[0] = other.data[0];
    data[1] = other.data[1];
    data[2] = other.data[2];
    data[3] = other.data[3];
}
gl::v4& gl::v4::operator=(const gl::v4& other) {
    data[0] = other.data[0];
    data[1] = other.data[1];
    data[2] = other.data[2];
    data[3] = other.data[3];
    return *this;
}
gl::v4& gl::v4::operator=(const gl::v4&& other) {
    data[0] = other.data[0];
    data[1] = other.data[1];
    data[2] = other.data[2];
    data[3] = other.data[3];
    return *this;
}
// Mutable Arithmetic
gl::v4& gl::v4::operator+=(const gl::v4& other) {
    data[0] += other.data[0];
    data[1] += other.data[1];
    data[2] += other.data[2];
    data[3] += other.data[3];
    return *this;
}
gl::v4& gl::v4::operator-=(const gl::v4& other) {
    data[0] -= other.data[0];
    data[1] -= other.data[1];
    data[2] -= other.data[2];
    data[3] -= other.data[3];
    return *this;
}
gl::v4& gl::v4::operator*=(const gl::v4& other) {
    data[0] *= other.data[0];
    data[1] *= other.data[1];
    data[2] *= other.data[2];
    data[3] *= other.data[3];
    return *this;
}
gl::v4& gl::v4::operator/=(const gl::v4& other) {
    data[0] /= other.data[0];
    data[1] /= other.data[1];
    data[2] /= other.data[2];
    data[3] /= other.data[3];
    return *this;
}
gl::v4& gl::v4::operator+=(float scalar) {
    data[0] += scalar;
    data[1] += scalar;
    data[2] += scalar;
    data[3] += scalar;
    return *this;
}
gl::v4& gl::v4::operator-=(float scalar) {
    data[0] -= scalar;
    data[1] -= scalar;
    data[2] -= scalar;
    data[3] -= scalar;
    return *this;
}
gl::v4& gl::v4::operator*=(float scalar) {
    data[0] *= scalar;
    data[1] *= scalar;
    data[2] *= scalar;
    data[3] *= scalar;
    return *this;
}
gl::v4& gl::v4::operator/=(float scalar) {
    data[0] /= scalar;
    data[1] /= scalar;
    data[2] /= scalar;
    data[3] /= scalar;
    return *this;
}

// Immutable Arithmetic
gl::v4 gl::v4::operator+(const gl::v4& other) const {
    return (gl::v4(*this) += other);
}
gl::v4 gl::v4::operator-(const gl::v4& other) const {
    return (gl::v4(*this) -= other);
}
gl::v4 gl::v4::operator*(const gl::v4& other) const {
    return (gl::v4(*this) *= other);
}
gl::v4 gl::v4::operator/(const gl::v4& other) const {
    return (gl::v4(*this) /= other);
}
gl::v4 gl::v4::operator+(float scalar) const {
    return (gl::v4(*this) += scalar);
}
gl::v4 gl::v4::operator-(float scalar) const {
    return (gl::v4(*this) -= scalar);
}
gl::v4 gl::v4::operator*(float scalar) const {
    return (gl::v4(*this) -= scalar);
}
gl::v4 gl::v4::operator/(float scalar) const {
    return (gl::v4(*this) /= scalar);
}
// Comparison Operators
bool gl::v4::operator==(const gl::v4& other) const {
    return (data[0] == other.data[0] && data[1] == other.data[1] && data[2] == other.data[2] &&
            data[3] == other.data[3]);
}
bool gl::v4::operator!=(const gl::v4& other) const {
    return !(*this == other);
}
// Linear and Geometric Functions
float gl::v4::dot(const gl::v4& other) const {
    return (data[0] * other.data[0] + data[1] * other.data[1] + data[2] * other.data[2] +
            data[3] * other.data[3]);
}
float gl::v4::angle(const gl::v4& other) const {
    return acos(dot(other) / (length() * other.length()));
}
float gl::v4::length() const {
    return sqrt(dot(*this));
}
gl::v4 gl::v4::cross(const gl::v4& other) const {
    return v4(data[1] * other.data[2] - data[2] * other.data[1],
        data[2] * other.data[0] - data[0] * other.data[2],
        data[0] * other.data[1] - data[1] * other.data[0], 0.0f);
}
gl::v4 gl::v4::normalize() const {
    return *this / length();
}
gl::v4 gl::v4::reflect(const gl::v4& normal) const {
    return *this - normal * 2 * dot(normal);
}
gl::v4 gl::v4::lerp(const gl::v4& other, float t) const {
    return (*this + t) * (other - *this);
}

std::string gl::v4::to_string() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "v4(" << data[0] << ", " << data[1] << ", " << data[2] << ", " << data[3] << ")";
    return ss.str();
}
