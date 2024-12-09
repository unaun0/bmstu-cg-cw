#include "vec3.hpp"

vec3::vec3(float x, float y, float z) {
    if (std::isnan(x) || std::isnan(y) || std::isnan(z)) {
        std::cout << x << '|' << y << '|' << z << std::endl;
        throw std::invalid_argument("Vec3: One or more parameters are NaN");
    }
    this->x = x;
    this->y = y;
    this->z = z;
}

float vec3::lng2() const noexcept {
    return x * x + y * y + z * z;
}

vec3 vec3::add(const vec3& v) const noexcept {
    return vec3(x + v.x, y + v.y, z + v.z);
}

vec3 vec3::sub(const vec3& v) const noexcept {
    return vec3(x - v.x, y - v.y, z - v.z);
}

vec3 vec3::mul(float s) const noexcept {
    return vec3(x * s, y * s, z * s);
}

vec3 vec3::mul(const vec3& v) const noexcept {
    return vec3(x * v.x, y * v.y, z * v.z);
}

vec3 vec3::div(const vec3& v) const {
    if (v.x == 0.0f || v.y == 0.0f || v.z == 0.0f)
        throw std::runtime_error("Division by zero in one of the vector components");
    return vec3(x / v.x, y / v.y, z / v.z);
}

float vec3::lng() const noexcept {
    return std::sqrt(x * x + y * y + z * z);
}

vec3 vec3::nrm() const {
    float len = lng();
    if (len == 0.0f)
        throw std::runtime_error("Cannot normalize a zero-length vector");
    return vec3(x / len, y / len, z / len);
}

vec3 vec3::rot(float y, float p) const {
    float yr = y * DEG_TO_RAD;
    float pr = p * DEG_TO_RAD;

    float _y = this->y * std::cos(pr) - this->z * std::sin(pr);
    float _z = this->y * std::sin(pr) + this->z * std::cos(pr);
    float _x = this->x * std::cos(yr) + _z * std::sin(yr);
    _z = -this->x * std::sin(yr) + _z * std::cos(yr);

    return vec3(_x, _y, _z);
}

void vec3::trl(const vec3& v) noexcept {
    x += v.x;
    y += v.y;
    z += v.z;
}

vec3 vec3::cln() const noexcept {
    return vec3(x, y, z);
}

std::string vec3::tStr() const {
    return "vec3{" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + '}';
}

std::array<float, 3> vec3::tArr() const noexcept {
    return { x, y, z };
}

vec3 vec3::operator+(const vec3& v) const noexcept {
    return add(v);
}

vec3 vec3::operator-(const vec3& v) const noexcept {
    return sub(v);
}

vec3 vec3::operator*(const vec3& v) const noexcept {
    return mul(v);
}

vec3 vec3::operator*(float s) const noexcept {
    return mul(s);
}

vec3& vec3::operator+=(const vec3& v) noexcept {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

vec3& vec3::operator-=(const vec3& v) noexcept {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

vec3& vec3::operator*=(float s) noexcept {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

vec3 vec3::operator-() const noexcept {
    return vec3(-x, -y, -z);
}

bool vec3::operator==(const vec3& v) const noexcept {
    return x == v.x && y == v.y && z == v.z;
}

bool vec3::operator!=(const vec3& v) const noexcept {
    return !(*this == v);
}

float vec3::dst(const vec3& va, const vec3& vb) {
    return std::sqrt(std::pow(va.x - vb.x, 2.0f) +
                     std::pow(va.y - vb.y, 2.0f) +
                     std::pow(va.z - vb.z, 2.0f));
}

float vec3::dot(const vec3& va, const vec3& vb) {
    return va.x * vb.x + va.y * vb.y + va.z * vb.z;
}

vec3 vec3::lrp(const vec3& va, const vec3& vb, float t) {
    return va.add(vb.sub(va).mul(t));
}
