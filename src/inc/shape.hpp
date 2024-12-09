#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "vec3.hpp"
#include "ray.hpp"
#include "colorRGB.hpp"
#include "material.hpp"
#include <memory>

class Shape {
public:
    vec3 pos;
    ColorRGB color;
    Material material;

    Shape(const vec3& pos, const ColorRGB& color, const Material& material);

    virtual std::unique_ptr<vec3> intersect(const Ray& r) const = 0;
    virtual std::unique_ptr<vec3> nrm(const vec3& v) const = 0;

    virtual ~Shape() = default;
};

#endif // SHAPE_HPP
