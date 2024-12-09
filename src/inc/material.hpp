#ifndef MATERIAL_HPP
#define MATERIAL_HPP

class Material {
public:
    float ka;
    float kd;
    float ks;
    float n;

    float reflectivity;
    float transparency;
    float emission;

    float refractiveIndex;

    Material(
        float ka, float kd, float ks, 
        float reflectivity, float transparency, float refractiveIndex, 
        float emission, float n
    );
};

#endif // MATERIAL_HPP
