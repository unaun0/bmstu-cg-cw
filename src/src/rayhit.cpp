#include "rayhit.hpp"


RayHit::RayHit(const Ray& ray, const Shape& shape, const vec3& pos, float n)
    : ray(ray), shape(shape), pos(pos), n(n), nrm(shape.nrm(pos) ? *shape.nrm(pos) : vec3()) {}