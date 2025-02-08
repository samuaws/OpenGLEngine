#include "AISystem.h"
#include "CombatComponent.h"
#include "MovementComponent.h"
#include "Engine/Entity.h"
#include <iostream>
#include "AdventurerComponent.h"

AISystem::AISystem(GridSystem* grid) : grid(grid) {}

void AISystem::start() {
    std::cout << "AI System Initialized.\n";
}

void AISystem::update(float deltaTime) {
    std::vector<Entity*> entitiesToProcess;

    // Get all entities on the grid
    for (int y = 0; y < grid->getHeight(); y++) {
        for (int x = 0; x < grid->getWidth(); x++) {
            Vector3 pos(x, y, 0); // Now using Vector3
            Entity* entity = grid->getEntityAt(pos);
            if (entity) entitiesToProcess.push_back(entity);
        }
    }

    // Process movement and combat for each entity
    for (Entity* entity : entitiesToProcess) {
        decideCombat(entity);
        decideMove(entity);
    }
}

void AISystem::decideMove(Entity* entity) {
    auto movement = entity->getComponent<MovementComponent>();
    if (!movement) return;

    auto combat = entity->getComponent<CombatComponent>();
    if (combat && !combat->isAlive()) return; // Don't move dead entities

    Vector3 nextPos = movement->getNextPosition(); // Now using Vector3

    // Mages teleport if engaged in combat
    if (entity->hasComponent<AdventurerComponent>() && entity->getComponent<AdventurerComponent>()->getType() == AdventurerType::Mage && grid->isOccupied(nextPos)) {
        movement->teleportAway();
        return;
    }

    // Move if no friendly unit is blocking
    if (!grid->isOccupied(nextPos)) {
        grid->moveEntity(entity, nextPos);
        std::cout << "Entity " << entity->getID() << " moved to ("
            << nextPos.x << ", "
            << nextPos.y << ", "
            << nextPos.z << ")\n";
    }
}

void AISystem::decideCombat(Entity* entity) {
    auto combat = entity->getComponent<CombatComponent>();
    if (!combat || !combat->isAlive()) return;

    Vector3 position = entity->getComponent<TransformComponent>()->position;

    // Check if an opponent is in the same cell
    Entity* opponent = grid->getEntityAt(position);
    if (opponent && opponent != entity) {
        auto opponentCombat = opponent->getComponent<CombatComponent>();
        if (opponentCombat) {
            combat->fight(opponentCombat.get());
        }
    }

    // Archers attack from range
    if (entity->hasComponent<AdventurerComponent>() && entity->getComponent<AdventurerComponent>()->getType() == AdventurerType::Archer) {
        for (int range = 1; range <= 2; range++) {
            Vector3 attackPos = { position.x + range, position.y, position.z };
            Entity* target = grid->getEntityAt(attackPos);
            if (target && target->hasComponent<CombatComponent>()) {
                target->getComponent<CombatComponent>()->takeDamage(combat->getDamage());
                std::cout << "Archer attacked target at ("
                    << attackPos.x << ", "
                    << attackPos.y << ", "
                    << attackPos.z << ")\n";
                return;
            }
        }
    }
}
