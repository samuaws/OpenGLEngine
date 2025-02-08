#include "GridSystem.h"
#include <iostream>

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

void GridSystem::printGrid() {
    for (float y = 0; y < height; y++) {
        for (float x = 0; x < width; x++) {
            if (isOccupied({ x, y })) std::cout << "[X]";
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

