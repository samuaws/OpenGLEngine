#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <functional> // Required for std::hash
#include <iostream>

class Vector3 {
public:
    float x, y, z;

    Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    // Vector addition
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // Vector subtraction
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // Equality comparison
    bool operator==(const Vector3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    // Normalize the vector
    Vector3 normalize() const {
        float length = std::sqrt(x * x + y * y + z * z);
        return (length > 0) ? Vector3(x / length, y / length, z / length) : Vector3();
    }

    // Dot product
    float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    Vector3 cross(const Vector3& other) const {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
};

// Define a custom hash function for `std::unordered_map`
namespace std {
    template <>
    struct hash<Vector3> {
        size_t operator()(const Vector3& v) const noexcept {
            size_t hx = std::hash<float>{}(v.x);
            size_t hy = std::hash<float>{}(v.y);
            size_t hz = std::hash<float>{}(v.z);
            return hx ^ (hy << 1) ^ (hz << 2); // Combine hashes
        }
    };
}

#endif // VECTOR3_H
