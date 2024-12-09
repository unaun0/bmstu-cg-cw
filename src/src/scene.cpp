#include "scene.hpp"
#include <limits>
#include <cmath>

Scene::Scene()
    : camera(), light(vec3(-1.0f, 2.0f, -1.0f)),
      skybox("img/bluecloud_rt.jpg", "img/bluecloud_lf.jpg", "img/bluecloud_up.jpg",
             "img/bluecloud_dn.jpg", "img/bluecloud_ft.jpg", "img/bluecloud_bk.jpg") {}

void Scene::addShape(std::shared_ptr<Shape> Shape) {
    Shapes.push_back(Shape);
}

std::unique_ptr<RayHit> Scene::raycast(const Ray& ray) const {
    std::unique_ptr<RayHit> closestHit = nullptr;
    for (const auto& Shape : Shapes) {
        if (!Shape) continue;
        auto hitPos = Shape->intersect(ray);
        if (hitPos != nullptr) {
            float currentdst = vec3::dst(*hitPos, ray.orig);
            if (!closestHit || vec3::dst(closestHit->pos, ray.orig) > currentdst)
                closestHit = std::make_unique<RayHit>(ray, *Shape, *hitPos, 1.0f);
        }
    }
    return closestHit;
}