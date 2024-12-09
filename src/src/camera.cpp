#include "camera.hpp"

Camera::Camera() : pos(0.0f, 0.0f, 0.0f), yaw(0.0f), pitch(0.0f), fOV(60.0f) {}

void Camera::trl(const vec3& v) {
    pos.trl(v);
}
