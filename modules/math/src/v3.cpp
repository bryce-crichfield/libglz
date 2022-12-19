#include "v3.h"

#include <iomanip>
#include <math.h>
#include <sstream>
// New Constructors
gl::v3::v3(float x) {
    data[0] = x;
    data[1] = 0;
    data[2] = 0;
}
gl::v3::v3(float x, float y) {
    data[0] = x;
    data[1] = y;
    data[2] = 0;
}
gl::v3::v3(float x, float y, float z) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
}
// V2 Compatibility Constructors
gl::v3::v3(const gl::v2& that) {
    data[0] = that.data[0];
    data[1] = that.data[1];
    data[2] = 0;
}
gl::v3::v3(const gl::v2& that, float z) {
    data[0] = that.data[0];
    data[1] = that.data[1];
    data[2] = z;
}

// Copy and Move Constructors
gl::v3::v3(const gl::v3& other) {
    data[0] = other.data[0];
    data[1] = other.data[1];
    data[2] = other.data[2];
}
gl::v3::v3(const gl::v3&& other) {
    data[0] = other.data[0];
    data[1] = other.data[1];
    data[2] = other.data[2];
}
gl::v3& gl::v3::operator=(const gl::v3& other) {
    data[0] = other.data[0];
    data[1] = other.data[1];
    data[2] = other.data[2];
    return *this;
}
gl::v3& gl::v3::operator=(const gl::v3&& other) {
    data[0] = other.data[0];
    data[1] = other.data[1];
    data[2] = other.data[2];
    return *this;
}
// Mutable Arithmetic
gl::v3& gl::v3::operator+=(const gl::v3& other) {
    data[0] += other.data[0];
    data[1] += other.data[1];
    data[2] += other.data[2];
    return *this;
}
gl::v3& gl::v3::operator-=(const gl::v3& other) {
    data[0] -= other.data[0];
    data[1] -= other.data[1];
    data[2] -= other.data[2];
    return *this;
}
gl::v3& gl::v3::operator*=(const gl::v3& other) {
    data[0] *= other.data[0];
    data[1] *= other.data[1];
    data[2] *= other.data[2];
    return *this;
}
gl::v3& gl::v3::operator/=(const gl::v3& other) {
    data[0] /= other.data[0];
    data[1] /= other.data[1];
    data[2] /= other.data[2];
    return *this;
}
gl::v3& gl::v3::operator+=(float scalar) {
    data[0] += scalar;
    data[1] += scalar;
    data[2] += scalar;
    return *this;
}
gl::v3& gl::v3::operator-=(float scalar) {
    data[0] -= scalar;
    data[1] -= scalar;
    data[2] -= scalar;
    return *this;
}
gl::v3& gl::v3::operator*=(float scalar) {
    data[0] *= scalar;
    data[1] *= scalar;
    data[2] *= scalar;
    return *this;
}
gl::v3& gl::v3::operator/=(float scalar) {
    data[0] /= scalar;
    data[1] /= scalar;
    data[2] /= scalar;
    return *this;
}

// Immutable Arithmetic
gl::v3 gl::v3::operator+(const gl::v3& other) const {
    return (gl::v3(*this) += other);
}
gl::v3 gl::v3::operator-(const gl::v3& other) const {
    return (gl::v3(*this) -= other);
}
gl::v3 gl::v3::operator*(const gl::v3& other) const {
    return (gl::v3(*this) *= other);
}
gl::v3 gl::v3::operator/(const gl::v3& other) const {
    return (gl::v3(*this) /= other);
}
gl::v3 gl::v3::operator+(float scalar) const {
    return (gl::v3(*this) += scalar);
}
gl::v3 gl::v3::operator-(float scalar) const {
    return (gl::v3(*this) -= scalar);
}
gl::v3 gl::v3::operator*(float scalar) const {
    return (gl::v3(*this) -= scalar);
}
gl::v3 gl::v3::operator/(float scalar) const {
    return (gl::v3(*this) /= scalar);
}
// Comparison Operators
bool gl::v3::operator==(const gl::v3& other) const {
    return (data[0] == other.data[0] && data[1] == other.data[1] && data[2] == other.data[2]);
}
bool gl::v3::operator!=(const gl::v3& other) const {
    return !(*this == other);
}
// Linear and Geometric Functions
float gl::v3::dot(const gl::v3& other) const {
    return data[0] * other.data[0] + data[1] * other.data[1] + data[2] * other.data[2];
}
float gl::v3::angle(const gl::v3& other) const {
    return acos(dot(other) / (length() * other.length()));
}
float gl::v3::length() const {
    return sqrt(dot(*this));
}
gl::v3 gl::v3::cross(const gl::v3& other) const {
    return v3(data[1] * other.data[2] - data[2] * other.data[1],
        data[2] * other.data[0] - data[0] * other.data[2],
        data[0] * other.data[1] - data[1] * other.data[0]);
}
gl::v3 gl::v3::normalize() const {
    return *this / length();
}
gl::v3 gl::v3::reflect(const gl::v3& normal) const {
    return *this - normal * 2 * dot(normal);
}
gl::v3 gl::v3::lerp(const gl::v3& other, float t) const {
    return (*this + t) * (other - *this);
}

std::string gl::v3::to_string() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "v2(" << data[0] << ", " << data[1] << ", " << data[2] << ")";
    return ss.str();
}
