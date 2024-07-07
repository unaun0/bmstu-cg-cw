#include "Shape.hpp"

Shape::Shape(const glm::vec3& pos, const Color& col, float refl, float refr, float emit)
    : position(pos), color(col), reflectivity(refl), refractivity(refr), emission(emit) {}
