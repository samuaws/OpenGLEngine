#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <unordered_map>
#include <memory>
#include "Entity.h"

class EntityManager {
public:
    EntityManager();
    ~EntityManager();

    // Create a new entity and return its ID
    int createEntity();

    // Delete an entity by ID
    void deleteEntity(int entityID);

    // Get an entity by ID
    std::shared_ptr<Entity> getEntity(int entityID) const;

private:
    int nextEntityID;
    std::unordered_map<int, std::shared_ptr<Entity>> entities;
};

#endif // ENTITYMANAGER_H
