#include "box.hpp"

Box::Box(const vec3& pos, const vec3& scale, const ColorRGB& color, const Material& material) 
    : Shape(pos, color, material),
      min(pos - scale.mul(0.5f)),  
      max(pos + scale.mul(0.5f)) {}

std::unique_ptr<vec3> Box::intersect(const Ray& r) const {
    float t1, t2;
    float tn = -INFINITY;
    float tf = INFINITY;
    bool intersection = true;

    std::array<float, 3> rDirArr = r.dir.tArr();
    const float* rDir = rDirArr.data();
    std::array<float, 3> rayOriginArr = r.orig.tArr();
    const float* rayOrigin = rayOriginArr.data();
    std::array<float, 3> b1Arr = min.tArr();
    const float* b1 = b1Arr.data();
    std::array<float, 3> b2Arr = max.tArr();
    const float* b2 = b2Arr.data();

    for (int i = 0; i < 3; ++i) {
        if (rDir[i] == 0.0f) {
            if (rayOrigin[i] < b1[i] || rayOrigin[i] > b2[i])
                intersection = false;
        } else {
            t1 = (b1[i] - rayOrigin[i]) / rDir[i];
            t2 = (b2[i] - rayOrigin[i]) / rDir[i];
            if (t1 > t2) std::swap(t1, t2);
            if (t1 > tn) tn = t1;
            if (t2 < tf) tf = t2;
            if (tn > tf) intersection = false;
            if (tf < 0) intersection = false;
        }
    }
    return intersection ? std::make_unique<vec3>(r.orig + r.dir.mul(tn)) : nullptr;
}

std::unique_ptr<vec3> Box::nrm(const vec3& v) const {
    vec3 dir = v - pos;
    if (fabs(v.x - min.x) < 1e-6)
        return std::make_unique<vec3>(vec3(-1.0f, 0.0f, 0.0f));
    if (fabs(v.x - max.x) < 1e-6)
        return std::make_unique<vec3>(vec3(1.0f, 0.0f, 0.0f));
    if (fabs(v.y - min.y) < 1e-6)
        return std::make_unique<vec3>(vec3(0.0f, -1.0f, 0.0f));
    if (fabs(v.y - max.y) < 1e-6)
        return std::make_unique<vec3>(vec3(0.0f, 1.0f, 0.0f));
    if (fabs(v.z - min.z) < 1e-6)
        return std::make_unique<vec3>(vec3(0.0f, 0.0f, -1.0f));
    if (fabs(v.z - max.z) < 1e-6)
        return std::make_unique<vec3>(vec3(0.0f, 0.0f, 1.0f));

    if (fabs(dir.x) > fabs(dir.y) && fabs(dir.x) > fabs(dir.z))
        return std::make_unique<vec3>(vec3((dir.x > 0) ? 1.0f : -1.0f, 0.0f, 0.0f));
    else if (fabs(dir.y) > fabs(dir.z))
        return std::make_unique<vec3>(vec3(0.0f, (dir.y > 0) ? 1.0f : -1.0f, 0.0f));
    return std::make_unique<vec3>(vec3(0.0f, 0.0f, (dir.z > 0) ? 1.0f : -1.0f));
}
