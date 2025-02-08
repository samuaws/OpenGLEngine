#include "Entity.h"
#include <iostream>

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


void Entity::startScripts() {
    for (auto& script : scriptComponents) {
        script->start();
    }
}

void Entity::updateScripts(float deltaTime) {
    for (auto& script : scriptComponents) {
        script->update(deltaTime);
    }
}
