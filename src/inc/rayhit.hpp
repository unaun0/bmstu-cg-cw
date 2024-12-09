#ifndef RAY_HIT_HPP
#define RAY_HIT_HPP

#include "ray.hpp"
#include "shape.hpp"
#include "vec3.hpp"


class RayHit {
public:
    Ray ray;
    const Shape& shape;
    vec3 pos;
    float n;
    vec3 nrm;

    RayHit(const Ray& ray, const Shape& shape, const vec3& pos, float n);
};

#endif // RAY_HIT_HPP
