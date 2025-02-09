#include "GameSimulation.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "MovementComponent.h"
#include "CombatComponent.h"
#include "AdventurerComponent.h"
#include "MonsterComponent.h"

#ifdef _WIN32
#include <windows.h>
void clearConsole() { system("cls"); }
#else
#include <unistd.h>
void clearConsole() { system("clear"); }
#endif

GameSimulation::GameSimulation(GridSystem* grid, int winCondition)
    : grid(grid), adventurerScore(0), monsterScore(0), winCondition(winCondition), timeAccumulator(0.0f) {}

void GameSimulation::start() {
    std::cout << "Game Simulation Started.\n";
}

void GameSimulation::update(float deltaTime) {
    timeAccumulator += deltaTime;

    // Only update every 5 seconds
    if (timeAccumulator >= 5.0f) {
        timeAccumulator = 0.0f;
        processTurn();
        renderGrid(); // NEW: Display updated grid
    }
}

void GameSimulation::processTurn() {
    moveEntities();
    handleCombat();
    checkWinCondition();
}
void GameSimulation::moveEntities() {
    std::vector<Entity*> entitiesToMove;

    for (int y = 0; y < grid->getHeight(); y++) {
        for (int x = 0; x < grid->getWidth(); x++) {
            Vector3 pos(x, y, 0);
            Entity* entity = grid->getEntityAt(pos);
            if (entity) entitiesToMove.push_back(entity);
        }
    }

    for (Entity* entity : entitiesToMove) {
        auto transform = entity->getComponent<TransformComponent>();
        auto movement = entity->getComponent<MovementComponent>();
        auto combat = entity->getComponent<CombatComponent>();

        if (!transform || !movement) continue;  // Ensure valid components

        Vector3 entityPos = transform->position;

        // Skip movement if the entity is in combat
        if (grid->hasOpponent(entityPos, entity)) {
            continue;
        }

        Vector3 newPos = movement->getNextPosition();

        // Ensure new position is valid and not occupied by the same team
        if (grid->isValidPosition(newPos) && !grid->isOccupied(newPos)) {
            grid->moveEntity(entity, newPos);
            transform->position = newPos;
            std::cout << "Entity " << entity->getID() << " moved to "
                << newPos.x << ", " << newPos.y << ", " << newPos.z << "\n";
        }
    }
}
void GameSimulation::handleCombat() {
    for (int y = 0; y < grid->getHeight(); y++) {
        for (int x = 0; x < grid->getWidth(); x++) {
            Vector3 pos(x, y, 0);
            Entity* entity = grid->getEntityAt(pos);
            if (!entity) continue;

            auto combat = entity->getComponent<CombatComponent>();
            auto adventurer = entity->getComponent<AdventurerComponent>();
            auto monster = entity->getComponent<MonsterComponent>();

            if (!combat) continue;

            // Find an opponent at this position
            Entity* opponent = grid->getOpponentAt(pos, entity);
            if (!opponent) continue;

            auto opponentCombat = opponent->getComponent<CombatComponent>();
            if (!opponentCombat) continue;

            // Mage Teleports Instead of Fighting
            if (adventurer && adventurer->getType() == AdventurerType::Mage) {
                Vector3 teleportPos = pos + Vector3(2, 0, 0); // Move 2 cells away
                if (grid->isValidPosition(teleportPos) && !grid->isOccupied(teleportPos)) {
                    grid->moveEntity(entity, teleportPos);
                    entity->getComponent<TransformComponent>()->position = teleportPos;
                    std::cout << "Mage teleported to (" << teleportPos.x << ", " << teleportPos.y << ", " << teleportPos.z << ")\n";
                }
                continue; // Skip combat for Mage
            }

            // Archer Attacks from Distance
            if (adventurer && adventurer->getType() == AdventurerType::Archer) {
                Vector3 archerAttackPos = pos + Vector3(1, 0, 0); // Check one tile ahead
                Entity* rangedTarget = grid->getEntityAt(archerAttackPos);
                if (rangedTarget) {
                    auto targetCombat = rangedTarget->getComponent<CombatComponent>();
                    if (targetCombat) {
                        std::cout << "Archer attacked target at (" << archerAttackPos.x << ", " << archerAttackPos.y << ", " << archerAttackPos.z << ")\n";
                        targetCombat->takeDamage(combat->getDamage());
                    }
                }
                continue; // Archer doesn't enter melee combat
            }

            // Melee Combat
            combat->fight(opponentCombat.get());

            // Remove dead entities
            if (!combat->isAlive()) {
                grid->removeEntity(entity);
            }
            if (!opponentCombat->isAlive()) {
                grid->removeEntity(opponent);
            }
        }
    }
}



void GameSimulation::checkWinCondition() {
    for (int y = 0; y < grid->getHeight(); y++) {
        for (int x = 0; x < grid->getWidth(); x++) {
            Vector3 pos(x, y, 0);
            Entity* entity = grid->getEntityAt(pos);
            if (!entity) continue;

            auto adventurer = entity->getComponent<AdventurerComponent>();
            auto monster = entity->getComponent<MonsterComponent>();

            if (adventurer && x == grid->getWidth() - 1) {
                adventurerScore++;
                std::cout << "Adventurer reached the base!\n";
                grid->removeEntity(entity);
            }

            if (monster && x == 0) {
                monsterScore++;
                std::cout << "Monster reached the base!\n";
                grid->removeEntity(entity);
            }
        }
    }

    if (adventurerScore >= winCondition) {
        std::cout << "Adventurers win!\n";
        exit(0);
    }

    if (monsterScore >= winCondition) {
        std::cout << "Monsters win!\n";
        exit(0);
    }
}
void GameSimulation::renderGrid() {
    std::cout << "\n=== Game Grid ===\n";

    for (int y = 0; y < grid->getHeight(); y++) {
        for (int x = 0; x < grid->getWidth(); x++) {
            Vector3 pos(x, y, 0);
            Entity* entity = grid->getEntityAt(pos);

            if (entity) {
                auto adventurer = entity->getComponent<AdventurerComponent>();
                auto monster = entity->getComponent<MonsterComponent>();
                auto combat = entity->getComponent<CombatComponent>();

                if (adventurer) {
                    std::string classType;
                    switch (adventurer->getType()) {
                    case AdventurerType::Warrior: classType = "W"; break;
                    case AdventurerType::Archer: classType = "A"; break;
                    case AdventurerType::Mage: classType = "M"; break;
                    }

                    std::cout << "[" << classType << combat->getHealth() << "] "; // Example: [W100] or [A80]
                }
                else if (monster) {
                    std::string monsterType = (monster->getType() == MonsterType::Goblin) ? "G" : "S";
                    std::cout << "[" << monsterType << combat->getHealth() << "] "; // Example: [G120] or [S110]
                }
            }
            else {
                std::cout << "[   ] "; // Empty cell
            }
        }
        std::cout << "\n"; // New row
    }
}

