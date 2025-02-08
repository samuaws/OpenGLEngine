#ifndef GRID_SYSTEM_H
#define GRID_SYSTEM_H

#include <unordered_map>
#include "Engine/ScriptComponent.h"
#include "Engine/Entity.h"
#include "Engine/Vector3.h" // Replacing Vector2 with Vector3

class GridSystem : public ScriptComponent {
public:
    GridSystem(int width, int height);

    void start() override;
    void update(float deltaTime) override;

    bool placeEntity(Entity* entity, Vector3 position);
    bool moveEntity(Entity* entity, Vector3 newPosition);
    Entity* getEntityAt(Vector3 position);
    bool isOccupied(Vector3 position);
    void removeEntity(Entity* entity);

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void printGrid();

private:
    int width, height;
    std::unordered_map<Vector3, Entity*> grid; // Using Vector3 now
};

#endif // GRID_SYSTEM_H
