#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <array>

constexpr float DEG_TO_RAD = M_PI / 180.0f;

class vec3 {
public:
    float x, y, z;

    vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    vec3(float x, float y, float z);

    vec3 add(const vec3& v) const noexcept;
    vec3 sub(const vec3& v) const noexcept;
    vec3 mul(float s) const noexcept;
    vec3 mul(const vec3& v) const noexcept;
    vec3 div(const vec3& v) const;
    float lng() const noexcept;
    float lng2() const noexcept;
    vec3 nrm() const;
    vec3 rot(float y, float p) const;
    void trl(const vec3& v) noexcept;
    vec3 cln() const noexcept;
    std::string tStr() const;
    std::array<float, 3> tArr() const noexcept;
    vec3 operator+(const vec3& v) const noexcept;
    vec3 operator-(const vec3& v) const noexcept;   
    vec3 operator*(const vec3& v) const noexcept;
    vec3 operator*(float s) const noexcept;
    vec3& operator+=(const vec3& v) noexcept;
    vec3& operator-=(const vec3& v) noexcept;
    vec3& operator*=(float s) noexcept;
    vec3 operator-() const noexcept;
    bool operator==(const vec3& v) const noexcept;
    bool operator!=(const vec3& v) const noexcept;

    static float dst(const vec3& va, const vec3& vb);
    static float dot(const vec3& va, const vec3& vb);
    static vec3 lrp(const vec3& va, const vec3& vb, float t);
};

#endif // VEC3_HPP
