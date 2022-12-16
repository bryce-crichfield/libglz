#include "math/m4.h"
#include "math/v2.h"
#include "math/v3.h"
#include "math/v4.h"

#include <iomanip>
#include <math.h>
#include <sstream>

gl::m4::m4(float uniform) {
    for (int i = 0; i < 16; i++) {
        data[i] = uniform;
    }
}

// Copy and Move Constructors
gl::m4::m4(const gl::m4& other) {
    for (int i = 0; i < 16; i++) {
        data[i] = other.data[i];
    }
}

gl::m4::m4(const gl::m4&& other) {
    for (int i = 0; i < 16; i++) {
        data[i] = other.data[i];
    }
}

gl::m4& gl::m4::operator=(const gl::m4& other) {
    for (int i = 0; i < 16; i++) {
        data[i] = other.data[i];
    }
    return *this;
}

gl::m4& gl::m4::operator=(const gl::m4&& other) {
    for (int i = 0; i < 16; i++) {
        data[i] = other.data[i];
    }
    return *this;
}

// Mutable Arithmetic
gl::m4& gl::m4::operator+=(const m4& other) {
    for (int i = 0; i < 16; i++) {
        data[i] += other.data[i];
    }
    return *this;
}
gl::m4& gl::m4::operator-=(const m4& other) {
    for (int i = 0; i < 16; i++) {
        data[i] -= other.data[i];
    }
    return *this;
}
gl::m4& gl::m4::operator+=(float scalar) {
    for (int i = 0; i < 16; i++) {
        data[i] += scalar;
    }
    return *this;
}
gl::m4& gl::m4::operator-=(float scalar) {
    for (int i = 0; i < 16; i++) {
        data[i] -= scalar;
    }
    return *this;
}
gl::m4& gl::m4::operator*=(float scalar) {
    for (int i = 0; i < 16; i++) {
        data[i] *= scalar;
    }
    return *this;
}

// Immutable Arithmetic
gl::m4 gl::m4::operator+(const gl::m4& other) const {
    return ((gl::m4(*this)) += other);
}
gl::m4 gl::m4::operator-(const gl::m4& other) const {
    return ((gl::m4(*this)) -= other);
}
gl::m4 gl::m4::operator*(const gl::m4& other) const {
    // inlined 4x4 column-major matrix multiplication
    gl::m4 result;
    result.data[0] = data[0] * other.data[0] + data[4] * other.data[1] + data[8] * other.data[2] +
                     data[12] * other.data[3];
    result.data[1] = data[1] * other.data[0] + data[5] * other.data[1] + data[9] * other.data[2] +
                     data[13] * other.data[3];
    result.data[2] = data[2] * other.data[0] + data[6] * other.data[1] + data[10] * other.data[2] +
                     data[14] * other.data[3];
    result.data[3] = data[3] * other.data[0] + data[7] * other.data[1] + data[11] * other.data[2] +
                     data[15] * other.data[3];
    result.data[4] = data[0] * other.data[4] + data[4] * other.data[5] + data[8] * other.data[6] +
                     data[12] * other.data[7];
    result.data[5] = data[1] * other.data[4] + data[5] * other.data[5] + data[9] * other.data[6] +
                     data[13] * other.data[7];
    result.data[6] = data[2] * other.data[4] + data[6] * other.data[5] + data[10] * other.data[6] +
                     data[14] * other.data[7];
    result.data[7] = data[3] * other.data[4] + data[7] * other.data[5] + data[11] * other.data[6] +
                     data[15] * other.data[7];
    result.data[8] = data[0] * other.data[8] + data[4] * other.data[9] + data[8] * other.data[10] +
                     data[12] * other.data[11];
    result.data[9] = data[1] * other.data[8] + data[5] * other.data[9] + data[9] * other.data[10] +
                     data[13] * other.data[11];
    result.data[10] = data[2] * other.data[8] + data[6] * other.data[9] +
                      data[10] * other.data[10] + data[14] * other.data[11];
    result.data[11] = data[3] * other.data[8] + data[7] * other.data[9] +
                      data[11] * other.data[10] + data[15] * other.data[11];
    result.data[12] = data[0] * other.data[12] + data[4] * other.data[13] +
                      data[8] * other.data[14] + data[12] * other.data[15];
    result.data[13] = data[1] * other.data[12] + data[5] * other.data[13] +
                      data[9] * other.data[14] + data[13] * other.data[15];
    result.data[14] = data[2] * other.data[12] + data[6] * other.data[13] +
                      data[10] * other.data[14] + data[14] * other.data[15];
    result.data[15] = data[3] * other.data[12] + data[7] * other.data[13] +
                      data[11] * other.data[14] + data[15] * other.data[15];
    return result;
}
gl::m4 gl::m4::operator+(float scalar) const {
    return ((gl::m4(*this)) += scalar);
}
gl::m4 gl::m4::operator-(float scalar) const {
    return ((gl::m4(*this)) -= scalar);
}
gl::m4 gl::m4::operator*(float scalar) const {
    return ((gl::m4(*this)) *= scalar);
}
gl::v4 gl::m4::operator*(const gl::v2& vector) const {
    return (*this * gl::v4(vector.x, vector.y, 0.0f, 1.0f));
}
gl::v4 gl::m4::operator*(const gl::v3& vector) const {
    return (*this * gl::v4(vector.x, vector.y, vector.z, 1.0f));
}
gl::v4 gl::m4::operator*(const gl::v4& vector) const {
    // generated inlined 4x4 column-major matrix-vector multiplication
    gl::v4 result;
    result.data[0] =
        data[0] * vector.x + data[4] * vector.y + data[8] * vector.z + data[12] * vector.w;
    result.data[1] =
        data[1] * vector.x + data[5] * vector.y + data[9] * vector.z + data[13] * vector.w;
    result.data[2] =
        data[2] * vector.x + data[6] * vector.y + data[10] * vector.z + data[14] * vector.w;
    result.data[3] =
        data[3] * vector.x + data[7] * vector.y + data[11] * vector.z + data[15] * vector.w;
    return result;
}

// Comparison Operators
bool gl::m4::operator==(const gl::m4& other) const {
    for (int i = 0; i < 16; i++) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}
bool gl::m4::operator!=(const gl::m4& other) const {
    return !(*this == other);
}

// Linear Functions
gl::m4 gl::m4::transpose() const {
    gl::m4 result;
    result.data[0] = data[0];
    result.data[1] = data[4];
    result.data[2] = data[8];
    result.data[3] = data[12];
    result.data[4] = data[1];
    result.data[5] = data[5];
    result.data[6] = data[9];
    result.data[7] = data[13];
    result.data[8] = data[2];
    result.data[9] = data[6];
    result.data[10] = data[10];
    result.data[11] = data[14];
    result.data[12] = data[3];
    result.data[13] = data[7];
    result.data[14] = data[11];
    result.data[15] = data[15];
    return result;
}
gl::m4 gl::m4::inverse() const {
    // generated inlined column-major 4x4 matrix inversion
    float det = determinant();
    if (det == 0.0f) {
        return gl::m4();
    }
    gl::m4 result;
    result.data[0] = data[5] * data[10] * data[15] + data[6] * data[11] * data[13] +
                     data[7] * data[9] * data[14] - data[5] * data[11] * data[14] -
                     data[6] * data[9] * data[15] - data[7] * data[10] * data[13];
    result.data[0] /= det;
    result.data[1] = data[1] * data[11] * data[14] + data[2] * data[9] * data[15];
    result.data[1] += data[3] * data[10] * data[13] - data[1] * data[10] * data[15] -
                      data[2] * data[11] * data[13] - data[3] * data[9] * data[14];
    result.data[1] /= det;
    result.data[2] = data[1] * data[6] * data[15] + data[2] * data[7] * data[13];
    result.data[2] += data[3] * data[5] * data[14] - data[1] * data[7] * data[14] -
                      data[2] * data[5] * data[15] - data[3] * data[6] * data[13];
    result.data[2] /= det;
    result.data[3] = data[1] * data[7] * data[10] + data[2] * data[5] * data[11];
    result.data[3] += data[3] * data[6] * data[9] - data[1] * data[6] * data[11] -
                      data[2] * data[7] * data[9] - data[3] * data[5] * data[10];
    result.data[3] /= det;
    result.data[4] = data[4] * data[11] * data[14] + data[6] * data[8] * data[15];
    result.data[4] += data[7] * data[10] * data[12] - data[4] * data[10] * data[15] -
                      data[6] * data[11] * data[12] - data[7] * data[8] * data[14];
    result.data[4] /= det;
    result.data[5] = data[0] * data[10] * data[15] + data[2] * data[11] * data[12];
    result.data[5] += data[3] * data[8] * data[14] - data[0] * data[11] * data[14] -
                      data[2] * data[8] * data[15] - data[3] * data[10] * data[12];
    result.data[5] /= det;
    result.data[6] = data[0] * data[7] * data[14] + data[2] * data[4] * data[15];
    result.data[6] += data[3] * data[6] * data[12] - data[0] * data[6] * data[15] -
                      data[2] * data[7] * data[12] - data[3] * data[4] * data[14];
    result.data[6] /= det;
    result.data[7] = data[0] * data[6] * data[11] + data[2] * data[7] * data[8];
    result.data[7] += data[3] * data[4] * data[10] - data[0] * data[7] * data[10] -
                      data[2] * data[4] * data[11] - data[3] * data[6] * data[8];
    result.data[7] /= det;
    result.data[8] = data[4] * data[9] * data[15] + data[5] * data[11] * data[12];
    result.data[8] += data[7] * data[8] * data[13] - data[4] * data[11] * data[13] -
                      data[5] * data[8] * data[15] - data[7] * data[9] * data[12];
    result.data[8] /= det;
    result.data[9] = data[0] * data[11] * data[13] + data[1] * data[8] * data[15];
    result.data[9] += data[3] * data[9] * data[12] - data[0] * data[9] * data[15] -
                      data[1] * data[11] * data[12] - data[3] * data[8] * data[13];
    result.data[9] /= det;
    result.data[10] = data[0] * data[5] * data[15] + data[1] * data[7] * data[12];
    result.data[10] += data[3] * data[4] * data[13] - data[0] * data[7] * data[13] -
                       data[1] * data[4] * data[15] - data[3] * data[5] * data[12];
    result.data[10] /= det;
    result.data[11] = data[0] * data[7] * data[9] + data[1] * data[4] * data[11];
    result.data[11] += data[3] * data[5] * data[8] - data[0] * data[5] * data[11] -
                       data[1] * data[7] * data[8] - data[3] * data[4] * data[9];
    result.data[11] /= det;
    result.data[12] = data[4] * data[10] * data[13] + data[5] * data[8] * data[14];
    result.data[12] += data[6] * data[9] * data[12] - data[4] * data[9] * data[14] -
                       data[5] * data[10] * data[12] - data[6] * data[8] * data[13];
    result.data[12] /= det;
    result.data[13] = data[0] * data[9] * data[14] + data[1] * data[10] * data[12];
    result.data[13] += data[2] * data[8] * data[13] - data[0] * data[10] * data[13] -
                       data[1] * data[8] * data[14] - data[2] * data[9] * data[12];
    result.data[13] /= det;
    result.data[14] = data[0] * data[6] * data[13] + data[1] * data[4] * data[14];
    result.data[14] += data[2] * data[5] * data[12] - data[0] * data[5] * data[14] -
                       data[1] * data[6] * data[12] - data[2] * data[4] * data[13];
    result.data[14] /= det;
    result.data[15] = data[0] * data[5] * data[10] + data[1] * data[6] * data[8];
    result.data[15] += data[2] * data[4] * data[9] - data[0] * data[6] * data[9] -
                       data[1] * data[4] * data[10] - data[2] * data[5] * data[8];
    result.data[15] /= det;
    return result;
}

float gl::m4::determinant() const {
    // generated inlined column-major 4x4 determinant calculation
    return data[0] * data[5] * data[10] * data[15] + data[0] * data[6] * data[11] * data[13] +
           data[0] * data[7] * data[9] * data[14] + data[1] * data[4] * data[11] * data[14] +
           data[1] * data[6] * data[8] * data[15] + data[1] * data[7] * data[10] * data[12] +
           data[2] * data[4] * data[9] * data[15] + data[2] * data[5] * data[11] * data[12] +
           data[2] * data[7] * data[8] * data[13] + data[3] * data[4] * data[10] * data[13] +
           data[3] * data[5] * data[8] * data[14] + data[3] * data[6] * data[9] * data[12] -
           data[0] * data[5] * data[11] * data[14] - data[0] * data[6] * data[9] * data[15] -
           data[0] * data[7] * data[10] * data[13] - data[1] * data[4] * data[10] * data[15] -
           data[1] * data[6] * data[11] * data[12] - data[1] * data[7] * data[8] * data[14] -
           data[2] * data[4] * data[11] * data[13] - data[2] * data[5] * data[8] * data[15] -
           data[2] * data[7] * data[9] * data[12] - data[3] * data[4] * data[9] * data[14] -
           data[3] * data[5] * data[10] * data[12] - data[3] * data[6] * data[8] * data[13];
}

// Geometric Functions
gl::m4 gl::m4::translate(const gl::v4& vector) {
    gl::m4 result;
    result.data[12] += vector.x;
    result.data[13] += vector.y;
    result.data[14] += vector.z;
    return result;
}
gl::m4 gl::m4::rotate(float degrees, float x, float y, float z) {
    gl::m4 result;
    float angle = degrees * (float)M_PI / 180.0f;
    float c = cos(angle);
    float s = sin(angle);
    float t = 1.0f - c;
    result.data[0] = t * x * x + c;
    result.data[1] = t * x * y + s * z;
    result.data[2] = t * x * z - s * y;
    result.data[4] = t * x * y - s * z;
    result.data[5] = t * y * y + c;
    result.data[6] = t * y * z + s * x;
    result.data[8] = t * x * z + s * y;
    result.data[9] = t * y * z - s * x;
    result.data[10] = t * z * z + c;
    return result;
}
gl::m4 gl::m4::lookAt(const gl::v4& eye, const gl::v4& center, const gl::v4& up) {
    gl::v4 f = (center - eye).normalize();
    gl::v4 s = f.cross(up).normalize();
    gl::v4 u = s.cross(f);
    gl::m4 result;
    result.data[0] = s.x;
    result.data[1] = u.x;
    result.data[2] = -f.x;
    result.data[4] = s.y;
    result.data[5] = u.y;
    result.data[6] = -f.y;
    result.data[8] = s.z;
    result.data[9] = u.z;
    result.data[10] = -f.z;
    result.data[12] = -s.dot(eye);
    result.data[13] = -u.dot(eye);
    result.data[14] = f.dot(eye);
    return result;
}
gl::m4 gl::m4::perspective(float fov, float aspect, float near, float far) {
    gl::m4 result;
    float f = 1.0f / tan(fov / 2.0f);
    result.data[0] = f / aspect;
    result.data[5] = f;
    result.data[10] = (far + near) / (near - far);
    result.data[11] = -1.0f;
    result.data[14] = (2.0f * far * near) / (near - far);
    return result;
}
gl::m4 gl::m4::orthographic(
    float left, float right, float bottom, float top, float near, float far) {
    gl::m4 result;
    result.data[0] = 2.0f / (right - left);
    result.data[5] = 2.0f / (top - bottom);
    result.data[10] = -2.0f / (far - near);
    result.data[12] = -(right + left) / (right - left);
    result.data[13] = -(top + bottom) / (top - bottom);
    result.data[14] = -(far + near) / (far - near);
    return result;
}

// String Functions
std::string gl::m4::to_string() const {
    // column-major 4x4 matrix multi-line string representation
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "[ " << data[0] << ", " << data[4] << ", " << data[8] << ", " << data[12] << " ]"
       << std::endl;
    ss << "[ " << data[1] << ", " << data[5] << ", " << data[9] << ", " << data[13] << " ]"
       << std::endl;
    ss << "[ " << data[2] << ", " << data[6] << ", " << data[10] << ", " << data[14] << " ]"
       << std::endl;
    ss << "[ " << data[3] << ", " << data[7] << ", " << data[11] << ", " << data[15] << " ]"
       << std::endl;
    return ss.str();
}