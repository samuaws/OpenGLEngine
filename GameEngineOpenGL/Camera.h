#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include <glm/glm.hpp> // For matrix operations
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera {
public:
    Camera();

    // Setters and getters
    void setPosition(const Vector3& position);
    const Vector3& getPosition() const;

    void setRotation(const Vector3& rotation);
    const Vector3& getRotation() const;

    // Movement and rotation
    void move(const Vector3& direction, float deltaTime);
    void rotate(const Vector3& deltaRotation);

    // Get matrices
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;

private:
    Vector3 position;
    Vector3 rotation; // Euler angles in degrees
    float movementSpeed;
    float mouseSensitivity;

    glm::vec3 getForwardVector() const;
    glm::vec3 getRightVector() const;
    glm::vec3 getUpVector() const;
};

#endif // CAMERA_H
