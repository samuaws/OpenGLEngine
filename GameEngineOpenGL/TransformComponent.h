#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Component.h"
#include "Vector3.h"
#include "Matrix4.h"

class TransformComponent : public Component {
public:
    Vector3 position;
    Vector3 rotation; // Rotation in degrees
    Vector3 scale;

    TransformComponent()
        : position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1) {}

    // Get the transformation matrix
    Matrix4 getTransformMatrix() const;

    // Set position
    void setPosition(const Vector3& pos);

    // Set rotation
    void setRotation(const Vector3& rot);

    // Set scale
    void setScale(const Vector3& scl);
};

#endif // TRANSFORMCOMPONENT_H
