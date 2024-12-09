#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "scene.hpp"
#include "vec3.hpp"
#include "colorRGB.hpp"
#include <vector>

class Renderer {
public:
    static bool SKYBOX;
    static int MAX_BOUNCES;

    static constexpr float GLOBAL_ILLUMINATION = 0.5f;
    static constexpr float SKY_EMISSION = 0.4f;

    static std::array<float, 2> getNormCoords(int x, int y, int width, int height);
    static float calcDiffBright(Scene& scene, RayHit& hit);
    static float calcSpecBright(Scene& scene, RayHit& hit);
    static vec3 refractRay(vec3 I, vec3 n, float cos, float thetaT, float thetaI);
    static ColorRGB calcPixelAtHit(Scene& scene, RayHit& hit, int recursionLimit);
    static ColorRGB calcPixel(Scene& scene, float u, float v);
    static std::vector<ColorRGB> renderScene(Scene* scene, int width, int height);
};

#endif // RENDERER_HPP
