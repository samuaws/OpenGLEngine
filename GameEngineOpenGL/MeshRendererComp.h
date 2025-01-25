#ifndef MESHRENDERERCOMP_H
#define MESHRENDERERCOMP_H

#include "Component.h"
#include "Vertex.h" // Use the globally defined Vertex structure
#include <vector>
#include <glad/glad.h>

class MeshRendererComp : public Component {
public:
    MeshRendererComp();
    ~MeshRendererComp();

    // Set the mesh data and prepare OpenGL buffers
    void setMeshData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    // Render the mesh
    void render() const;

private:
    unsigned int VAO, VBO, EBO; // OpenGL buffers
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Helper function to setup OpenGL buffers
    void setupMesh();
};

#endif // MESHRENDERERCOMP_H
