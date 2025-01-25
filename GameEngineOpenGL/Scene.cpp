#include "Scene.h"

Scene::Scene(const std::string& name) : name(name) {}

void Scene::addEntity(int entityID) {
    entities.push_back(entityID);
}

const std::vector<int>& Scene::getEntities() const {
    return entities;
}

const std::string& Scene::getName() const {
    return name;
}
