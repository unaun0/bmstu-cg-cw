#include "plane.hpp"

Plane::Plane(float ht, const ColorRGB& color, const Material& material) 
    : Shape(vec3(0.0f, ht, 0.0f), color, material),
    ht(ht) {}


std::unique_ptr<vec3> Plane::intersect(const Ray& r) const {
    float t = -(r.orig.y - pos.y) / r.dir.y;
    if (t > 0 && std::isfinite(t))
        return std::make_unique<vec3>(r.orig + r.dir.mul(t));
    return nullptr;
}

std::unique_ptr<vec3> Plane::nrm(const vec3& v) const {
    return std::make_unique<vec3>(vec3(0.0f, 1.0f, 0.0f));
}