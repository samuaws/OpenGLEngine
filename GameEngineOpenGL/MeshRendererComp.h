#ifndef MESHRENDERERCOMP_H
#define MESHRENDERERCOMP_H

#include "Component.h"
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp> // For MVP matrices
#include "Vertex.h"

class MeshRendererComp : public Component {
public:
    MeshRendererComp();
    ~MeshRendererComp();

    void setMeshData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    void render(const glm::mat4& mvpMatrix) const; // Accept MVP matrix for rendering

private:
    unsigned int VAO, VBO, EBO;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    void setupMesh();
};

#endif // MESHRENDERERCOMP_H
