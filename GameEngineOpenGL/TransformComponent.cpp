#include "TransformComponent.h"
#include <cmath>

#define DEG2RAD(angle) ((angle) * 0.0174532925f)

Matrix4 TransformComponent::getTransformMatrix() const {
    // Translation matrix
    Matrix4 translation = Matrix4::translate(position);

    // Scaling matrix
    Matrix4 scaling = Matrix4::scale(scale);

    // Rotation matrices (simplified, no full quaternion rotations yet)
    Matrix4 rotationX, rotationY, rotationZ;

    // Rotation around X-axis
    rotationX.data[1][1] = std::cos(DEG2RAD(rotation.x));
    rotationX.data[1][2] = -std::sin(DEG2RAD(rotation.x));
    rotationX.data[2][1] = std::sin(DEG2RAD(rotation.x));
    rotationX.data[2][2] = std::cos(DEG2RAD(rotation.x));

    // Rotation around Y-axis
    rotationY.data[0][0] = std::cos(DEG2RAD(rotation.y));
    rotationY.data[0][2] = std::sin(DEG2RAD(rotation.y));
    rotationY.data[2][0] = -std::sin(DEG2RAD(rotation.y));
    rotationY.data[2][2] = std::cos(DEG2RAD(rotation.y));

    // Rotation around Z-axis
    rotationZ.data[0][0] = std::cos(DEG2RAD(rotation.z));
    rotationZ.data[0][1] = -std::sin(DEG2RAD(rotation.z));
    rotationZ.data[1][0] = std::sin(DEG2RAD(rotation.z));
    rotationZ.data[1][1] = std::cos(DEG2RAD(rotation.z));

    // Combined transformation: Translation * Rotation * Scaling
    return translation * rotationX * rotationY * rotationZ * scaling;
}

void TransformComponent::setPosition(const Vector3& pos) {
    position = pos;
}

void TransformComponent::setRotation(const Vector3& rot) {
    rotation = rot;
}

void TransformComponent::setScale(const Vector3& scl) {
    scale = scl;
}
