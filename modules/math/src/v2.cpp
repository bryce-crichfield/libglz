#include "v2.h"

#include <iomanip>
#include <math.h>
#include <sstream>
// New Constructors
gl::v2::v2(float x) {
    data[0] = x;
    data[1] = 0;
}
gl::v2::v2(float x, float y) {
    data[0] = x;
    data[1] = y;
}

// Copy and Move Constructors
gl::v2::v2(const gl::v2& other) {
    data[0] = other.data[0];
    data[1] = other.data[1];
}
gl::v2::v2(const gl::v2&& other) {
    data[0] = other.data[0];
    data[1] = other.data[1];
}
gl::v2& gl::v2::operator=(const gl::v2& other) {
    data[0] = other.data[0];
    data[1] = other.data[1];
    return *this;
}
gl::v2& gl::v2::operator=(const gl::v2&& other) {
    data[0] = other.data[0];
    data[1] = other.data[1];
    return *this;
}
// Mutable Arithmetic
gl::v2& gl::v2::operator+=(const gl::v2& other) {
    data[0] += other.data[0];
    data[1] += other.data[1];
    return *this;
}
gl::v2& gl::v2::operator-=(const gl::v2& other) {
    data[0] -= other.data[0];
    data[1] -= other.data[1];
    return *this;
}
gl::v2& gl::v2::operator*=(const gl::v2& other) {
    data[0] *= other.data[0];
    data[1] *= other.data[1];
    return *this;
}
gl::v2& gl::v2::operator/=(const gl::v2& other) {
    data[0] /= other.data[0];
    data[1] /= other.data[1];
    return *this;
}
gl::v2& gl::v2::operator+=(float scalar) {
    data[0] += scalar;
    data[1] += scalar;
    return *this;
}
gl::v2& gl::v2::operator-=(float scalar) {
    data[0] -= scalar;
    data[1] -= scalar;
    return *this;
}
gl::v2& gl::v2::operator*=(float scalar) {
    data[0] *= scalar;
    data[1] *= scalar;
    return *this;
}
gl::v2& gl::v2::operator/=(float scalar) {
    data[0] /= scalar;
    data[1] /= scalar;
    return *this;
}

// Immutable Arithmetic
gl::v2 gl::v2::operator+(const gl::v2& other) const {
    return (gl::v2(*this) += other);
}
gl::v2 gl::v2::operator-(const gl::v2& other) const {
    return (gl::v2(*this) -= other);
}
gl::v2 gl::v2::operator*(const gl::v2& other) const {
    return (gl::v2(*this) *= other);
}
gl::v2 gl::v2::operator/(const gl::v2& other) const {
    return (gl::v2(*this) /= other);
}
gl::v2 gl::v2::operator+(float scalar) const {
    return (gl::v2(*this) += scalar);
}
gl::v2 gl::v2::operator-(float scalar) const {
    return (gl::v2(*this) -= scalar);
}
gl::v2 gl::v2::operator*(float scalar) const {
    return (gl::v2(*this) -= scalar);
}
gl::v2 gl::v2::operator/(float scalar) const {
    return (gl::v2(*this) /= scalar);
}
// Comparison Operators
bool gl::v2::operator==(const gl::v2& other) const {
    return data[0] == other.data[0] && data[1] == other.data[1];
}
bool gl::v2::operator!=(const gl::v2& other) const {
    return !(*this == other);
}
// Linear and Geometric Functions
float gl::v2::dot(const gl::v2& other) const {
    return data[0] * other.data[0] + data[1] * other.data[1];
}
float gl::v2::angle(const gl::v2& other) const {
    return acos(dot(other) / (length() * other.length()));
}
float gl::v2::length() const {
    return sqrt(dot(*this));
}
gl::v2 gl::v2::normalize() const {
    return *this / length();
}
gl::v2 gl::v2::reflect(const gl::v2& normal) const {
    return *this - normal * 2 * dot(normal);
}
gl::v2 gl::v2::lerp(const gl::v2& other, float t) const {
    return (*this + t) * (other - *this);
}

std::string gl::v2::to_string() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "v2(" << data[0] << ", " << data[1] << ")";
    return ss.str();
}
