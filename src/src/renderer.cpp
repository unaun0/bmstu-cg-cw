#include "renderer.hpp"
#include <cmath>
#include <iostream>
#include <ctime>
#include <limits>
#include <algorithm>
#include <chrono>
#include <thread>
#include <mutex>
#include <cylinder.hpp>
#include <plane.hpp>

#define EPS 0.001f

bool Renderer::SKYBOX = true;
int Renderer::MAX_BOUNCES = 5;


std::array<float, 2> Renderer::getNormCoords(int x, int y, int wt, int ht) {
    std::array<float, 2> uv;
    float u, v;
    if (wt > ht) {
        u = (x - wt / 2 + ht / 2) / static_cast<float>(ht) * 2 - 1;
        v = -(y / static_cast<float>(ht) * 2 - 1);
    } else {
        u = x / static_cast<float>(wt) * 2 - 1;
        v = -((y - ht / 2 + wt / 2) / static_cast<float>(wt) * 2 - 1);
    }
    uv[0] = u; uv[1] = v;
    return uv;
}

vec3 Renderer::refractRay(vec3 I, vec3 n, float cos, float n1, float n2) {
    if (cos < 0.0f) return refractRay(I, n, -cos, n2, n1);
    float eta = n1 / n2;
    float sin = eta * sqrtf(std::max(0.0f, 1.0f - cos * cos));
    if (sin >= 1.0f)
        return vec3(-1.0f, 0.0f, 0.0f);
    float cos2 = sqrtf(std::max(0.0f, 1.0f - sin * sin));
    return I * eta + n * (eta * cos - cos2);
}

/*float Renderer::calcDiffBright(Scene& scene, RayHit& hit) {
    vec3 lightDir = (scene.light.pos - hit.pos).nrm();
    Ray shadowRay(hit.pos + lightDir * 0.01f, lightDir);
    float lightDistance = vec3::dst(scene.light.pos, hit.pos);
    auto lightBlocker = scene.raycast(shadowRay);
    if (lightBlocker && (&(lightBlocker->shape) != &(hit.shape))) {
        float blockerDistance = vec3::dst(hit.pos, lightBlocker->pos);
        if (blockerDistance < lightDistance)
            return GLOBAL_ILLUMINATION;
    }
    return std::max(
        GLOBAL_ILLUMINATION,
        GLOBAL_ILLUMINATION + std::min(1.0f, vec3::dot(hit.nrm, lightDir))
    );
}*/

float Renderer::calcDiffBright(Scene& scene, RayHit& hit) {
    vec3 lightDir = (scene.light.pos - hit.pos).nrm();
    Ray shadowRay(hit.pos + lightDir * 0.001f, lightDir);
    auto hs = &(hit.shape);
    float accumulatedLight = 1.0f;
    int bounceCount = 0;
    float n = 1.0;
    while (bounceCount < MAX_BOUNCES) {
        ++bounceCount;
        auto lightBlocker = scene.raycast(shadowRay);
        if (lightBlocker && (lightBlocker->pos - scene.light.pos).lng2() < EPS) {
            return std::max(
                GLOBAL_ILLUMINATION,
                std::min(1.0f, vec3::dot(hit.nrm, lightDir)) * accumulatedLight
            );
        }
        if (!lightBlocker) {
            return std::max(
                GLOBAL_ILLUMINATION,
                std::min(1.0f, vec3::dot(hit.nrm, lightDir)) * accumulatedLight
            );
        }
        if (&(lightBlocker->shape) == hs) {
            if (vec3::dot(lightBlocker->nrm, lightDir) > 0.0f) {
                shadowRay.orig = lightBlocker->pos + lightDir * 0.001f;
                continue;
            } else {
                return GLOBAL_ILLUMINATION;
            }
        }
        float transparency = (lightBlocker->shape).material.transparency * 0.9;
        if (transparency > 0.0f) {
            accumulatedLight *= transparency;
            if (accumulatedLight < 0.01f) {
                return GLOBAL_ILLUMINATION;
            }
            vec3 refrRay = refractRay(lightDir, lightBlocker->nrm, vec3::dot(lightDir, lightBlocker->nrm), lightBlocker->shape.material.refractiveIndex,  n);
            //if (lightBlocker->shape.material.refractiveIndex < n)
            //    n = lightBlocker->shape.material.refractiveIndex;
            shadowRay.orig = lightBlocker->pos + lightDir * 0.001f;
            shadowRay.dir = refrRay.nrm();
        } else {
            return GLOBAL_ILLUMINATION;
        }
        hs = &(lightBlocker->shape);
    }
    return std::max(
        GLOBAL_ILLUMINATION,
        std::min(1.0f, vec3::dot(hit.nrm, lightDir)) * accumulatedLight
    );
}

float Renderer::calcSpecBright(Scene& scene, RayHit& hit) {
    vec3 lightDir = (hit.pos - (scene.light.pos).nrm()).nrm();
    float specularFactor = std::max(
        0.0f, 
        vec3::dot(
            lightDir - hit.nrm * (vec3::dot(lightDir, hit.nrm) * 2), //cos, refl vec
            (scene.camera.pos - hit.pos).nrm()
        )
    );
    return std::pow(specularFactor, 2.0f) * hit.shape.material.reflectivity;
}

ColorRGB Renderer::calcPixelAtHit(Scene& scene, RayHit& hit, int limit) {
    const ColorRGB hitColorRGB = hit.shape.color;
    const float dBright = calcDiffBright(scene, hit);
    const float sBright = calcSpecBright(scene, hit);

    const float reflectivity = hit.shape.material.reflectivity;
    const float emission = hit.shape.material.emission;
    const float transparency = hit.shape.material.transparency;
    const float n1 = hit.n;
    const float n2 = hit.shape.material.refractiveIndex;

    ColorRGB reflectionColor;
    ColorRGB refractionColor;

    float dirCos = vec3::dot(hit.ray.dir, hit.nrm);
    vec3 reflectRayDir = hit.ray.dir - (hit.nrm * (2.0f * dirCos));
    vec3 reflectRayOrig = hit.pos + (reflectRayDir * 0.001f);

    vec3 refractRayDir = refractRay(hit.ray.dir, hit.nrm, dirCos, n2, n1);
    vec3 refractRayOrig = hit.pos + (refractRayDir * 0.001f);

    std::unique_ptr<RayHit> reflectHit = (limit > 0) 
        ? scene.raycast(Ray(reflectRayOrig, reflectRayDir)) 
        : nullptr;
    if (reflectHit)
        reflectionColor = calcPixelAtHit(scene, *reflectHit, limit - 1);
    else if (SKYBOX)
        reflectionColor = scene.skybox.getColorRGB(reflectRayDir).mul(SKY_EMISSION);
    else
        reflectionColor = ColorRGB::SKYBLUE;

    std::unique_ptr<RayHit> refractHit = (limit > 0) 
        ? scene.raycast(Ray(refractRayOrig, refractRayDir)) 
        : nullptr;
    if (refractHit)
        refractionColor = calcPixelAtHit(scene, *refractHit, limit - 1);
    else if (SKYBOX)
        refractionColor = scene.skybox.getColorRGB(refractRayDir).mul(SKY_EMISSION);
    else
        refractionColor = ColorRGB::SKYBLUE;
    
    ColorRGB pixelColorRGB = ColorRGB::lrp(hitColorRGB, reflectionColor, reflectivity)
        .mul(dBright)
        .add(sBright)
        .add(reflectionColor.mul(reflectivity * emission))
        .add(refractionColor.mul(transparency));
    return pixelColorRGB;
}

ColorRGB Renderer::calcPixel(Scene& scene, float u, float v) {
    vec3 eyePos(0.0f, 0.0f, (-1.0f / std::tan(scene.camera.fOV * M_PI / 360.0f))); 
    Camera& cam = scene.camera;
    vec3 rayDir = (vec3(u, v, 0.0f) - eyePos).nrm().rot(cam.yaw, cam.pitch);
    auto hitPtr = scene.raycast(Ray(eyePos + cam.pos, rayDir));
    if (hitPtr)
        return calcPixelAtHit(scene, *hitPtr, MAX_BOUNCES);
    else if (SKYBOX)
        return scene.skybox.getColorRGB(rayDir).mul(SKY_EMISSION);
    else
        return ColorRGB::SKYBLUE;
}

std::vector<ColorRGB> Renderer::renderScene(Scene* scene, int wt, int ht) {
    std::vector<ColorRGB> pixels(wt * ht);

    auto start = std::chrono::high_resolution_clock::now();
    auto start_cpu = std::clock();

    int numThreads = 64; //std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 8;

    auto renderBlock = [&scene, &pixels, wt, ht](int startX, int startY, int blockWidth, int blockHeight) {
        for (int x = startX; x < std::min(startX + blockWidth, wt); ++x) {
            for (int y = startY; y < std::min(startY + blockHeight, ht); ++y) {
                std::array<float, 2> uv = getNormCoords(x, y, wt, ht);
                ColorRGB pixel = calcPixel(*scene, uv[0], uv[1]);
                pixels[(y * wt + x)] = pixel;
            }
        }
    };
    std::vector<std::thread> threads;
    int blockWidth = (wt + numThreads - 1) / numThreads;
    for (int t = 0; t < numThreads; ++t) {
        int startX = (t % numThreads) * blockWidth;
        int startY = 0;
        threads.emplace_back(renderBlock, startX, startY, blockWidth, ht);
    }
    for (auto& t : threads) {
        t.join();
    }

    std::clock_t end_cpu = std::clock();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_real = end - start;
    double elapsed_cpu = double(end_cpu - start_cpu) / CLOCKS_PER_SEC;

    std::cout << "Время рендеринга: \n";
    std::cout << "\tРеальное время - " << elapsed_real.count() << " секунд\n";
    std::cout << "\tПроцессорное время - " << elapsed_cpu << " секунд\n";

    return pixels;
}