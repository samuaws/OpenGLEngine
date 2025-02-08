#ifndef VECTOR2_H
#define VECTOR2_H

#include <functional>

struct Vector2 {
    float x, y;

    Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
};

// Hash function for Vector2 (needed for unordered_map)
namespace std {
    template <>
    struct hash<Vector2> {
        size_t operator()(const Vector2& v) const {
            return hash<float>()(v.x) ^ (hash<float>()(v.y) << 1);
        }
    };
}

#endif // VECTOR2_H
