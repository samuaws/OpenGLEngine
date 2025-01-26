#include "ModelImporter.h"
#include "MeshRendererComp.h"
#include "TransformComponent.h"
#include "Vertex.h" // Ensure the new Vertex format is included
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

ModelImporter::ModelImporter(EntityManager* entityManager) : entityManager(entityManager) {}

int ModelImporter::importModel(const std::string& filePath) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Load the mesh data from the file
    loadMeshFromFile(filePath, vertices, indices);

    // If no data was loaded, return an error
    if (vertices.empty() || indices.empty()) {
        std::cerr << "Failed to load model: " << filePath << "\n";
        return -1;
    }

    // Create a new entity for the model
    int entityID = entityManager->createEntity();
    auto entity = entityManager->getEntity(entityID);

    // Add a MeshRendererComp to the entity and set the mesh data
    auto meshRenderer = entity->addComponent<MeshRendererComp>();
    meshRenderer->setMeshData(vertices, indices);

    // Transform is added by default as per earlier implementation
    std::cout << "Model imported and entity created with ID: " << entityID << "\n";

    return entityID;
}

void ModelImporter::loadMeshFromFile(const std::string& filePath, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
    std::cout << "Loading model: " << filePath << "\n";

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

    // Check for errors
    if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
        std::cerr << "Error loading model: " << importer.GetErrorString() << "\n";
        return;
    }

    // For simplicity, load the first mesh in the scene
    aiMesh* mesh = scene->mMeshes[0];

    // Extract vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;

        // Position
        vertex.position = glm::vec3(
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        );

        // Normal
        if (mesh->mNormals) {
            vertex.normal = glm::vec3(
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z
            );
        }
        else {
            vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        // Texture coordinates
        if (mesh->mTextureCoords[0]) {
            vertex.texCoords = glm::vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            );
        }
        else {
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    // Extract indices
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    std::cout << "Loaded " << vertices.size() << " vertices and " << indices.size() << " indices from the model.\n";
}
