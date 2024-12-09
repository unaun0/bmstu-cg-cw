#include "ray.hpp"

Ray::Ray(const vec3& orig, const vec3& dir) : orig(orig) {
    float length = dir.lng();
    if (length != 0.0f && length != 1.0f) {
        this->dir = dir.nrm();
    } else {
        this->dir = dir;
    }
}
