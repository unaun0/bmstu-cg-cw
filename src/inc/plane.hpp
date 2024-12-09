#ifndef PLANE_HPP
#define PLANE_HPP

#include "shape.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "colorRGB.hpp"
#include "material.hpp"
#include <memory>
class Plane : public Shape {
public:
    float ht;

    Plane(float ht, const ColorRGB& color, const Material& material);

    std::unique_ptr<vec3> intersect(const Ray& r) const override;
    std::unique_ptr<vec3> nrm(const vec3& v) const override;
};


#endif // PLANE_HPP
