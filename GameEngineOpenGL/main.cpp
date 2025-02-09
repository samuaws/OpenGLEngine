#include "Engine/Application.h"
#include "Engine/EntityManager.h"
#include "GameManager.h"
#include <memory>

int main() {
    // Create Application
    Application& app = Application::getInstance();

    app.registerSetup([&]() {
        auto sceneManager = app.getSceneManager();
        auto entityManager = sceneManager->getEntityManager();

        // Create a Manager entity
        int gameManagerID = entityManager->createEntity();  // Create entity and get ID
        auto gameManagerEntity = entityManager->getEntity(gameManagerID); // Retrieve the entity

        if (gameManagerEntity) { // Ensure entity is valid
            gameManagerEntity->addComponent<GameManager>(10, 5, 3);

            // Add the GameManager entity to the active scene
            sceneManager->addEntityToActiveScene(gameManagerID);
        }
        else {
            std::cerr << "Failed to create GameManager entity.\n";
            return;
        }
        });

    // Start the game loop
    app.start();

    return 0;
}
