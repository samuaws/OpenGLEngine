#include "GridSystem.h"
#include <iostream>
#include "AdventurerComponent.h"
#include "MonsterComponent.h"

GridSystem::GridSystem(int width, int height) : width(width), height(height) {}

void GridSystem::start() {
    std::cout << "Grid System Initialized.\n";
}

void GridSystem::update(float deltaTime) {
    // No update logic needed for the grid itself yet
}

bool GridSystem::placeEntity(Entity* entity, Vector3 position) {
    if (isOccupied(position)) return false;

    grid[position] = entity;
    return true;
}

bool GridSystem::moveEntity(Entity* entity, Vector3 newPosition) {
    if (!isValidPosition(newPosition) || isOccupied(newPosition)) return false;

    for (auto it = grid.begin(); it != grid.end(); ++it) {
        if (it->second == entity) {
            grid.erase(it);
            grid[newPosition] = entity;
            return true;
        }
    }
    return false;
}

Entity* GridSystem::getEntityAt(Vector3 position) {
    if (isOccupied(position)) return grid[position];
    return nullptr;
}

bool GridSystem::isOccupied(Vector3 position) {
    return grid.find(position) != grid.end();
}

bool GridSystem::hasOpponent(Vector3 position, Entity* entity) {
    auto target = getEntityAt(position);
    if (!target || target == entity) return false;

    auto adventurer = entity->getComponent<AdventurerComponent>();
    auto monster = entity->getComponent<MonsterComponent>();

    auto targetAdventurer = target->getComponent<AdventurerComponent>();
    auto targetMonster = target->getComponent<MonsterComponent>();

    // If one is an adventurer and the other is a monster, return true
    return (adventurer && targetMonster) || (monster && targetAdventurer);
}

bool GridSystem::isValidPosition(Vector3 position) {
    return position.x >= 0 && position.x < width && position.y >= 0 && position.y < height;
}


std::vector<Entity*> GridSystem::getEntitiesAt(Vector3 position) {
    std::vector<Entity*> entities;
    if (isOccupied(position)) {
        entities.push_back(grid[position]);
    }
    return entities;
}

void GridSystem::printGrid() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Vector3 pos(x, y, 0);
            if (isOccupied(pos)) std::cout << "[X]";
            else std::cout << "[ ]";
        }
        std::cout << std::endl;
    }
}

void GridSystem::removeEntity(Entity* entity) {
    for (auto it = grid.begin(); it != grid.end(); ++it) {
        if (it->second == entity) {
            grid.erase(it);
            std::cout << "Entity " << entity->getID() << " removed from grid.\n";
            return;
        }
    }
}

Entity* GridSystem::getOpponentAt(Vector3 position, Entity* entity) {
    auto it = grid.find(position);
    if (it == grid.end()) return nullptr; // No entity at this position

    Entity* potentialOpponent = it->second;

    if (!potentialOpponent || potentialOpponent == entity) return nullptr; // Avoid self

    auto adventurer = entity->getComponent<AdventurerComponent>();
    auto monster = entity->getComponent<MonsterComponent>();

    auto potentialAdventurer = potentialOpponent->getComponent<AdventurerComponent>();
    auto potentialMonster = potentialOpponent->getComponent<MonsterComponent>();

    // Check if the opponent is from the opposing team
    if ((adventurer && potentialMonster) || (monster && potentialAdventurer)) {
        return potentialOpponent;
    }

    return nullptr;
}

