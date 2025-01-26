#include "Camera.h"

Camera::Camera()
    : position(0.0f, 0.0f, 3.0f),
    rotation(0.0f, 0.0f, 0.0f),
    movementSpeed(5.0f), // Movement speed
    mouseSensitivity(0.1f) // Mouse sensitivity
{
}

void Camera::setPosition(const Vector3& position) {
    this->position = position;
}

const Vector3& Camera::getPosition() const {
    return position;
}

void Camera::setRotation(const Vector3& rotation) {
    this->rotation = rotation;
}

const Vector3& Camera::getRotation() const {
    return rotation;
}

void Camera::move(const Vector3& direction, float deltaTime) {
    glm::vec3 forward = getForwardVector();
    glm::vec3 right = getRightVector();

    position = position +  Vector3(right.x, right.y, right.z) * (direction.x * movementSpeed * deltaTime);
    position = position +  Vector3(0.0f, 1.0f, 0.0f) * (direction.y * movementSpeed * deltaTime);
    position = position +  Vector3(forward.x, forward.y, forward.z) * (direction.z * movementSpeed * deltaTime);

}

void Camera::rotate(const Vector3& deltaRotation) {
    rotation.x += deltaRotation.x * mouseSensitivity;
    rotation.y += deltaRotation.y * mouseSensitivity;

    // Clamp pitch to avoid gimbal lock
    if (rotation.x > 89.0f) rotation.x = 89.0f;
    if (rotation.x < -89.0f) rotation.x = -89.0f;
}

glm::mat4 Camera::getViewMatrix() const {
    glm::vec3 forward = getForwardVector();
    glm::vec3 up(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraPos(position.x, position.y, position.z);

    return glm::lookAt(cameraPos, cameraPos + forward, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

glm::vec3 Camera::getForwardVector() const {
    glm::vec3 forward;
    forward.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    forward.y = sin(glm::radians(rotation.x));
    forward.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    return glm::normalize(forward);
}

glm::vec3 Camera::getRightVector() const {
    return glm::normalize(glm::cross(getForwardVector(), glm::vec3(0.0f, 1.0f, 0.0f)));
}

glm::vec3 Camera::getUpVector() const {
    return glm::normalize(glm::cross(getRightVector(), getForwardVector()));
}
