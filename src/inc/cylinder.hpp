#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "shape.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include "colorRGB.hpp"
#include "material.hpp"

class Cylinder : public Shape {
public:
    float rd;
    float ht;
    
    Cylinder(const vec3& pos, float rd, float ht, const ColorRGB& color, const Material& material);
    
    std::unique_ptr<vec3> intersect(const Ray& r) const override;
    std::unique_ptr<vec3> nrm(const vec3& v) const override;
};

#endif // CYLINDERS_HPP
