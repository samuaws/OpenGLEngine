#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

class Vertex {
public : 
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

#endif // VERTEX_H
