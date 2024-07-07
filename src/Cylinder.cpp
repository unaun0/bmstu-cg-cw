#include "Cylinder.hpp"
#include "Ray.hpp"
#include <cmath>

Cylinder::Cylinder(const glm::vec3& position, float radius, float height, const Color& color, float reflectivity, float refractivity, float emission)
    : Shape(position, color, reflectivity, refractivity, emission), radius(radius), height(height) {}

glm::vec3* Cylinder::intersect(const Ray& ray) const {
    const float eps = 0.001f;

    glm::vec3 intersectionPoint = ray.orig - position;

    bool isBelongToCylinderBase = false;

    float ts1 = (height - ray.orig.y + position.y) / (ray.dir.y + eps);
    glm::vec3 point = intersectionPoint + ray.dir * ts1;

    if (point.x * point.x + point.z * point.z - radius * radius < eps)
        isBelongToCylinderBase = true;

    float ts2 = (-height - ray.orig.y + position.y) / (ray.dir.y + eps);
    point = intersectionPoint + ray.dir * ts2;

    if (point.x * point.x + point.z * point.z - radius * radius < eps)
        isBelongToCylinderBase = true;

    float a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
    float b = ray.orig.x * ray.dir.x - ray.dir.x * position.x + ray.orig.z * ray.dir.z -
              ray.dir.z * position.z;
    float c = ray.orig.x * ray.orig.x + position.x * position.x + ray.orig.z * ray.orig.z +
              position.z * position.z - 2 * (position.x * ray.orig.x + ray.orig.z * position.z) -
              radius * radius;

    float delta = b * b - (a * c);

    float t = 0.0f;

    if (delta < eps) {
        if (isBelongToCylinderBase) {
            t = std::min(ts1, ts2);
            return new glm::vec3(ray.orig + ray.dir * t);
        }
        return nullptr;
    }

    float t1 = (-b - sqrt(delta)) / a;
    float t2 = (-b + sqrt(delta)) / a;
    t = (t1 < eps) ? t2 : t1;

    if (!(std::abs(ray.orig.y + t * ray.dir.y - position.y) > height)) {
        return (t > eps) ? new glm::vec3(ray.orig + ray.dir * t) : nullptr;
    }

    if (!isBelongToCylinderBase) return nullptr;
    t = std::min(ts1, ts2);
    return new glm::vec3(ray.orig + ray.dir * t);
}

glm::vec3 Cylinder::getNormal(const glm::vec3& point) const {
    glm::vec3 normalIntersectionPoint = point - position;
    if (!(std::abs(normalIntersectionPoint.y) > height))
        return glm::normalize(glm::vec3(normalIntersectionPoint.x, 0.0f, normalIntersectionPoint.z));
    else
        return glm::normalize(point - position);
}

Color Cylinder::getTexture(const glm::vec3& point) const {
    return color;
}
