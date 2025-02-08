#include "GameSimulation.h"
#include <iostream>
#include "MovementComponent.h"
#include "CombatComponent.h"
#include "AdventurerComponent.h"
#include "MonsterComponent.h"

GameSimulation::GameSimulation(GridSystem* grid, int winCondition)
    : grid(grid), adventurerScore(0), monsterScore(0), winCondition(winCondition) {}

void GameSimulation::start() {
    std::cout << "Game Simulation Started.\n";
}

void GameSimulation::update(float deltaTime) {
    processTurn(); // Process one turn per update
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
            Vector3 pos(x, y, 0); // Now using Vector3
            Entity* entity = grid->getEntityAt(pos);
            if (entity) entitiesToMove.push_back(entity);
        }
    }

    for (Entity* entity : entitiesToMove) {
        auto movement = entity->getComponent<MovementComponent>();
        if (movement) {
            Vector3 newPos = movement->getNextPosition();
            if (!grid->isOccupied(newPos)) {
                grid->moveEntity(entity, newPos);
            }
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
            if (combat) {
                Entity* opponent = grid->getEntityAt(pos);
                if (opponent && opponent != entity) {
                    auto opponentCombat = opponent->getComponent<CombatComponent>();
                    if (opponentCombat) {
                        combat->fight(opponentCombat.get());
                    }
                }
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
