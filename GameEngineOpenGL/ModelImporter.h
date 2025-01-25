#ifndef MODELIMPORTER_H
#define MODELIMPORTER_H

#include "EntityManager.h"
#include <string>
#include <vector>

struct Vertex {
    float position[3];
    float normal[3];
    float texCoords[2];
};

class ModelImporter {
public:
    // Constructor: Requires an EntityManager to create entities
    ModelImporter(EntityManager* entityManager);

    // Import a 3D model file and create an entity with a MeshRenderer
    int importModel(const std::string& filePath);

private:
    EntityManager* entityManager;

    // Load mesh data from a file
    void loadMeshFromFile(const std::string& filePath, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};

#endif // MODELIMPORTER_H
