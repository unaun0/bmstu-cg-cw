#include "Camera.hpp"

Camera::Camera()
    : position(glm::vec3(0.0f, 0.0f, 0.0f)), yaw(0.0f), pitch(0.0f), fov(60.0f) {}

void Camera::translate(const glm::vec3& vec) {
    position += vec;
}

const glm::vec3& Camera::getPosition() const {
    return position;
}

void Camera::setPosition(const glm::vec3& pos) {
    position = pos;
}

float Camera::getYaw() const {
    return yaw;
}

void Camera::setYaw(float angle) {
    yaw = angle;
}

float Camera::getPitch() const {
    return pitch;
}

void Camera::setPitch(float angle) {
    pitch = angle;
}

float Camera::getFOV() const {
    return fov;
}

void Camera::setFOV(float fieldOfView) {
    fov = fieldOfView;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + getFront(), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 Camera::getFront() const {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    return glm::normalize(front);
}
