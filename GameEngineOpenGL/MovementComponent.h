#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "Engine/ScriptComponent.h"
#include "GridSystem.h"
#include "Engine/Vector3.h" 

class MovementComponent : public ScriptComponent {
public:
    MovementComponent(GridSystem* grid, Vector3 direction, bool canTeleport = false);

    void start() override;
    void update(float deltaTime) override;

    Vector3 getNextPosition() const;
    void setDirection(Vector3 newDirection);
    void teleportAway();

private:
    GridSystem* grid;
    Vector3 direction;
    bool canTeleport;
};

#endif // MOVEMENT_COMPONENT_H
