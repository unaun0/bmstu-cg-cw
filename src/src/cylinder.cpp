#include "cylinder.hpp"

#define EPS 0.001f

Cylinder::Cylinder(const vec3& pos, float rd, float ht, const ColorRGB& color, const Material& material)
    : Shape(pos, color, material), rd(rd), ht(ht) {}

std::unique_ptr<vec3> Cylinder::intersect(const Ray& r) const {
    vec3 intp = r.orig - pos;
    bool isBase = false;

    float ts1 = (ht - r.orig.y + pos.y) / (r.dir.y + EPS);
    vec3 point = intp + r.dir.mul(ts1);
    if ((point.x * point.x + point.z * point.z - rd * rd < EPS))
        isBase = true;
    float ts2 = (-ht - r.orig.y + pos.y) / (r.dir.y + EPS);
    point = intp + r.dir.mul(ts2);
    if (point.x * point.x + point.z * point.z - rd * rd < EPS)
        isBase = true;
    
    float a = r.dir.x * r.dir.x + r.dir.z * r.dir.z;
    float b = r.orig.x * r.dir.x - r.dir.x * pos.x + r.orig.z * r.dir.z - r.dir.z * pos.z;
    float c = r.orig.x * r.orig.x + pos.x * pos.x + r.orig.z * r.orig.z + \
              pos.z * pos.z - 2 * (pos.x * r.orig.x + r.orig.z * pos.z) - rd * rd;
    float delta = b * b - (a * c);
    float t = 0.0f;
    if (delta < EPS) {
        if (isBase) {
            t = std::min(ts1, ts2);
            if ((!(abs(r.orig.y + t * r.dir.y - pos.y) > ht)) && (t > 0.0))
                return std::make_unique<vec3>(r.orig + (r.dir.mul(t)));
        }
        return nullptr;
    }
    float t1 = (-b - sqrt(delta)) / a;
    float t2 = (-b + sqrt(delta)) / a;
    t = (t1 < 0.0) ? t2 : t1;
    if ((!(abs(r.orig.y + t * r.dir.y - pos.y) > ht)) && (t > 0.0))
        return std::make_unique<vec3>(r.orig + (r.dir.mul(t)));
    if (!isBase) return nullptr;
    t = std::min(ts1, ts2);
    if ((!(abs(r.orig.y + t * r.dir.y - pos.y) > ht)) && (t > 0.0))
        return std::make_unique<vec3>(r.orig + (r.dir.mul(t)));
    return nullptr;
}

std::unique_ptr<vec3> Cylinder::nrm(const vec3& v) const {
    vec3 nrmintp = v - pos;
    if (nrmintp.y > ht)
        return std::make_unique<vec3>(vec3(0.0f, 1.0f, 0.0f));
    else if (nrmintp.y < -ht)
        return std::make_unique<vec3>(vec3(0.0f, -1.0f, 0.0f));
    return std::make_unique<vec3>(vec3(nrmintp.x, 0.0f, nrmintp.z).nrm());
}
