#ifndef AI_SYSTEM_H
#define AI_SYSTEM_H

#include "Engine/ScriptComponent.h"
#include "GridSystem.h"
#include "Engine/Vector3.h" // Now using Vector3
#include <vector>

class AISystem : public ScriptComponent {
public:
    AISystem(GridSystem* grid);

    void start() override;
    void update(float deltaTime) override;

private:
    GridSystem* grid;

    void decideMove(Entity* entity);
    void decideCombat(Entity* entity);
};

#endif // AI_SYSTEM_H
