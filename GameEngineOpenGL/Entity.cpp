#include "Entity.h"

Entity::Entity(int id) : id(id) {
    initializeDefaultComponents();
}

Entity::~Entity() {}

int Entity::getID() const {
    return id;
}

void Entity::initializeDefaultComponents() {
    // Add a TransformComponent by default
    addComponent<TransformComponent>();
}
