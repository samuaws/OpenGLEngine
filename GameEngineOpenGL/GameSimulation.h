#ifndef GAME_SIMULATION_H
#define GAME_SIMULATION_H

#include "Engine/ScriptComponent.h"
#include "GridSystem.h"
#include "Engine/Vector3.h"
#include <vector>

class GameSimulation : public ScriptComponent {
public:
    GameSimulation(GridSystem* grid, int winCondition);

    void start() override;
    void update(float deltaTime) override;

private:
    GridSystem* grid;
    int adventurerScore;
    int monsterScore;
    int winCondition;
    float timeAccumulator; // NEW: Track time for turns

    void processTurn();
    void moveEntities();
    void handleCombat();
    void checkWinCondition();
    void renderGrid(); // NEW: Render grid to the console
};

#endif // GAME_SIMULATION_H
