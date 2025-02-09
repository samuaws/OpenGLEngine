#include "GameManager.h"
#include "Engine/EntityManager.h"
#include "Engine/Application.h"
#include "Engine/ModelImporter.h"
#include <iostream>

GameManager::GameManager(int gridWidth, int gridHeight, int winCondition) {
    // GridSystem, AISystem, and GameSimulation will be added as components in `start()`
}

void GameManager::start() {
    std::cout << "Game Manager Initialized.\n";

    // Add core game systems as components
    grid = entity->addComponent<GridSystem>(10, 5);  // Grid size: 10x5
    aiSystem = entity->addComponent<AISystem>(grid.get());
    gameSimulation = entity->addComponent<GameSimulation>(grid.get(), 3);  // Win condition: 3 units infiltrating

    // Spawn adventurers and monsters
    spawnAdventurers();
    spawnMonsters();
    std::cout << "GameManager Inisialized";
}

void GameManager::spawnAdventurers() {
    auto sceneManager = Application::getInstance().getSceneManager();
    auto entityManager = sceneManager->getEntityManager();
    ModelImporter modelImporter(entityManager);

    for (int i = 0; i < 3; i++) {
        int entityID = entityManager->createEntity();
        auto adventurer = entityManager->getEntity(entityID);

        AdventurerType type = (i == 0) ? AdventurerType::Warrior : (i == 1) ? AdventurerType::Archer : AdventurerType::Mage;

        adventurer->addComponent<AdventurerComponent>(type);
        auto transform = adventurer->addComponent<TransformComponent>(Vector3(0, i, 0));
        transform->setScale(Vector3(0.01f, 0.01f, 0.01f));
        adventurer->addComponent<CombatComponent>(100, (type == AdventurerType::Warrior) ? 20 : (type == AdventurerType::Archer) ? 15 : 12);
        adventurer->addComponent<MovementComponent>(grid.get(), Vector3(1, 0, 0), (type == AdventurerType::Mage));

        grid->placeEntity(adventurer.get(), Vector3(0, i, 0));

        //Import correct model for each class
        std::string modelPath = (type == AdventurerType::Warrior) ? "Objects/warrior.fbx"
            : (type == AdventurerType::Archer) ? "Objects/warrior.fbx"
            : "Objects/warrior.fbx";

        int modelID = modelImporter.importModel(modelPath);
        if (modelID != -1) {
            sceneManager->addEntityToActiveScene(modelID);
        }
    }
}

void GameManager::spawnMonsters() {
    auto sceneManager = Application::getInstance().getSceneManager();
    auto entityManager = sceneManager->getEntityManager();
    ModelImporter modelImporter(entityManager);

    for (int i = 0; i < 3; i++) {
        int entityID = entityManager->createEntity();
        auto monster = entityManager->getEntity(entityID);

        MonsterType type = (i % 2 == 0) ? MonsterType::Goblin : MonsterType::Skeleton;

        monster->addComponent<MonsterComponent>(type);
        auto transform = monster->addComponent<TransformComponent>(Vector3(grid->getWidth() - 1, i, 0));
        transform->setScale(Vector3(0.01f, 0.01f, 0.01f));
        monster->addComponent<CombatComponent>(100, 18); // Fixed attack power for monsters
        monster->addComponent<MovementComponent>(grid.get(), Vector3(-1, 0, 0), false); // Moving left

        grid->placeEntity(monster.get(), Vector3(grid->getWidth() - 1, i, 0));

        //  Import correct model for each monster
        std::string modelPath = (type == MonsterType::Goblin) ? "Objects/skeleton.fbx"
            : "Objects/skeleton.fbx";

        int modelID = modelImporter.importModel(modelPath);
        if (modelID != -1) {
            sceneManager->addEntityToActiveScene(modelID);
        }
    }
}
