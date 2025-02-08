#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Engine/ScriptComponent.h"
#include "GridSystem.h"
#include "AISystem.h"
#include "GameSimulation.h"
#include "AdventurerComponent.h"
#include "MonsterComponent.h"
#include "MovementComponent.h"
#include "CombatComponent.h"

class GameManager : public ScriptComponent {
public:
    GameManager(int gridWidth, int gridHeight, int winCondition);

    void start() override;

private:
    std::shared_ptr<GridSystem> grid;
    std::shared_ptr<AISystem> aiSystem;
    std::shared_ptr<GameSimulation> gameSimulation;

    void spawnAdventurers();
    void spawnMonsters();
};

#endif // GAME_MANAGER_H
