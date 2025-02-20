#include "MeshRendererComp.h"
#include <iostream>

MeshRendererComp::MeshRendererComp() : VAO(0), VBO(0), EBO(0) {
    setupShader();
}

MeshRendererComp::~MeshRendererComp() {
    if (shader) {
        delete shader; // Clean up shader
    }
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (EBO) glDeleteBuffers(1, &EBO);
}

void MeshRendererComp::setupShader() {
    try {
        // Load and compile the shaders
        shader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
        std::cout << "Shader initialized successfully." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to initialize shader: " << e.what() << std::endl;
    }
}

void MeshRendererComp::setMeshData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
    this->vertices = vertices;
    this->indices = indices;
    setupMesh();
}

void MeshRendererComp::setupMesh() {
    std::cout << "Mesh Check 1\n";
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    // TexCoords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void MeshRendererComp::setShader(Shader* shader) {
    this->shader = shader;
}


void MeshRendererComp::render(const glm::mat4& mvpMatrix) const {
    // Use the shader program
    shader->use();

    // Send the MVP matrix to the shader
    GLuint mvpLocation = glGetUniformLocation(shader->getID(), "uMVP");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvpMatrix[0][0]);

    // Bind the VAO and draw
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Unbind the shader program
    glUseProgram(0);
}

