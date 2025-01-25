#include "ModelImporter.h"
#include "MeshRendererComp.h"
#include "TransformComponent.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

void ModelImporter::loadMeshFromFile(const std::string& filePath, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
    std::cout << "Loading model with Assimp: " << filePath << "\n";

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
        std::cerr << "Error loading model: " << importer.GetErrorString() << "\n";
        return;
    }

    aiMesh* mesh = scene->mMeshes[0]; // Load the first mesh as an example

    // Extract vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex = {};
        vertex.position[0] = mesh->mVertices[i].x;
        vertex.position[1] = mesh->mVertices[i].y;
        vertex.position[2] = mesh->mVertices[i].z;

        vertex.normal[0] = mesh->mNormals[i].x;
        vertex.normal[1] = mesh->mNormals[i].y;
        vertex.normal[2] = mesh->mNormals[i].z;

        if (mesh->mTextureCoords[0]) { // Check if the mesh has texture coordinates
            vertex.texCoords[0] = mesh->mTextureCoords[0][i].x;
            vertex.texCoords[1] = mesh->mTextureCoords[0][i].y;
        }
        else {
            vertex.texCoords[0] = 0.0f;
            vertex.texCoords[1] = 0.0f;
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

    std::cout << "Model loaded: " << vertices.size() << " vertices, " << indices.size() << " indices\n";
}
