#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include "camera.hpp"
#include "light.hpp"
#include "shape.hpp"
#include "ray.hpp"
#include "rayhit.hpp"
#include "skybox.hpp"

class Scene {
public:
    Camera camera;
    Light light;
    std::vector<std::shared_ptr<Shape>> Shapes;
    Skybox skybox;
    
    Scene();

    void addShape(std::shared_ptr<Shape> Shape);
    std::unique_ptr<RayHit> raycast(const Ray& ray) const;
};

#endif // SCENE_HPP
