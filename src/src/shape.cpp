#include "shape.hpp"

Shape::Shape(const vec3& pos, const ColorRGB& color, const Material& material)
    : pos(pos), color(color), material(material) {
}
