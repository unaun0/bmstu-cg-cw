#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "vec3.hpp"
class Camera {
public:
    vec3 pos;
    float yaw;
    float pitch;
    float fOV;

    Camera();

    void trl(const vec3& v);
};


#endif // CAMERA_HPP
