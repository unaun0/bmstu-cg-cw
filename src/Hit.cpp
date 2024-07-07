#include "Hit.hpp"

Hit::Hit(const Ray& ray, const Shape& shape, const glm::vec3& position)
    : ray(ray), shape(shape), position(position), normal(shape.getNormal(position)) {}
