#ifndef MODELIMPORTER_H
#define MODELIMPORTER_H

#include "EntityManager.h"
#include "Vertex.h" // Include Vertex definition
#include <string>
#include <vector>

class ModelImporter {
public:
    ModelImporter(EntityManager* entityManager);

    int importModel(const std::string& filePath);

private:
    EntityManager* entityManager;

    void loadMeshFromFile(const std::string& filePath, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
};

#endif // MODELIMPORTER_H
