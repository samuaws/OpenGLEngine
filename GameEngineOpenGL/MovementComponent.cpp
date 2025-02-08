#include "MovementComponent.h"
#include "CombatComponent.h"
#include <iostream>

MovementComponent::MovementComponent(GridSystem* grid, Vector3 direction, bool canTeleport)
    : grid(grid), direction(direction), canTeleport(canTeleport) {}

void MovementComponent::start() {
    std::cout << "MovementComponent initialized with direction ("
        << direction.x << ", " << direction.y << ", " << direction.z << ")\n";
}

void MovementComponent::update(float deltaTime) {
    auto combat = entity->getComponent<CombatComponent>();

    if (combat && combat->isAlive()) {
        if (grid->isOccupied(getNextPosition())) return; // Can't move if a friendly unit is ahead

        grid->moveEntity(entity, getNextPosition());
        std::cout << "Entity " << entity->getID() << " moved to ("
            << getNextPosition().x << ", "
            << getNextPosition().y << ", "
            << getNextPosition().z << ")\n";
    }
}

Vector3 MovementComponent::getNextPosition() const {
    auto transform = entity->getComponent<TransformComponent>();
    return transform->position + direction; // Now using Vector3 addition
}

void MovementComponent::setDirection(Vector3 newDirection) {
    direction = newDirection;
}

void MovementComponent::teleportAway() {
    if (!canTeleport) return;

    auto transform = entity->getComponent<TransformComponent>();
    Vector3 newPosition = transform->position + (direction * 2.0f); // Teleports 2 steps away

    if (!grid->isOccupied(newPosition)) {
        grid->moveEntity(entity, newPosition);
        std::cout << "Mage teleported to ("
            << newPosition.x << ", "
            << newPosition.y << ", "
            << newPosition.z << ")\n";
    }
}
