#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "colorRGB.hpp"
#include "material.hpp"
#include <memory>

class Box : public Shape {
public:
    vec3 min;
    vec3 max;
    
    Box(const vec3& pos, const vec3& scale, const ColorRGB& color, const Material& material);

    std::unique_ptr<vec3> intersect(const Ray& r) const override;
    std::unique_ptr<vec3> nrm(const vec3& v) const override;
};


#endif // BOX_HPP
