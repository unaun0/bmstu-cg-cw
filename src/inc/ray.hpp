#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

class Ray {
public:
    vec3 orig;
    vec3 dir;

    Ray() noexcept : orig(vec3(0.0f, 0.0f, 0.0f)), dir(vec3(1.0f, 0.0f, 0.0f)) {}
    Ray(const vec3& orig, const vec3& dir);

    bool operator==(const Ray& other) const noexcept {
        return orig == other.orig && dir == other.dir;
    }
    
    bool operator!=(const Ray& other) const noexcept {
        return !(*this == other);
    }
};

#endif // RAY_HPP
