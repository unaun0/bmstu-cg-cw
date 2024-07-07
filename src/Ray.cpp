#include "Ray.hpp"

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
    : orig(origin), dir(glm::normalize(direction)) {}

Line Ray::asLine(float length) const {
    return Line(orig, orig + dir * length);
}