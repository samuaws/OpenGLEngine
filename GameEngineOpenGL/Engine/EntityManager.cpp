#include "EntityManager.h"

EntityManager::EntityManager() : nextEntityID(0) {}

EntityManager::~EntityManager() {}

int EntityManager::createEntity() {
    int id = nextEntityID++;
    entities[id] = std::make_shared<Entity>(id);
    return id;
}

void EntityManager::deleteEntity(int entityID) {
    entities.erase(entityID);
}

std::shared_ptr<Entity> EntityManager::getEntity(int entityID) const {
    auto it = entities.find(entityID);
    return (it != entities.end()) ? it->second : nullptr;
}
