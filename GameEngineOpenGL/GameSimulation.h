#ifndef GAME_SIMULATION_H
#define GAME_SIMULATION_H

#include "Engine/ScriptComponent.h"
#include "GridSystem.h"
#include "Engine/Vector3.h" // Now using Vector3
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
    int winCondition; // Number of units needed to win

    void processTurn();
    void moveEntities();
    void handleCombat();
    void checkWinCondition();
};

#endif // GAME_SIMULATION_H
