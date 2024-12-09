#include "material.hpp"

Material::Material(
    float ka, float kd, float ks, 
    float reflectivity, float transparency, float refractiveIndex, float emission, 
    float n
) : ka(ka), kd(kd), ks(ks), n(n), 
    reflectivity(reflectivity), transparency(transparency), emission(emission), 
    refractiveIndex(refractiveIndex) {}

