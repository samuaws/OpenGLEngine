#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h" // Use the existing Vector3 class

struct Vertex {
    Vector3 position;   // Vertex position
    Vector3 normal;     // Normal vector
    float texCoords[2]; // Texture coordinates (still using a fixed array for simplicity)
};

#endif // VERTEX_H
