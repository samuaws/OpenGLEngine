#include "Application.h"
#include "EntityManager.h"
#include "TransformComponent.h"
#include <iostream>

int main() {
    // Initialize Application (no entities here)
    Application app;

    // Initialize EntityManager
    EntityManager entityManager;

    // Create and manipulate entities
    int entity1ID = entityManager.createEntity();
    auto entity1 = entityManager.getEntity(entity1ID);
    auto transform1 = entity1->getComponent<TransformComponent>();
    transform1->setPosition({ 0.0f, 1.0f, 2.0f });

    int entity2ID = entityManager.createEntity();
    auto entity2 = entityManager.getEntity(entity2ID);
    auto transform2 = entity2->getComponent<TransformComponent>();
    transform2->setPosition({ 3.0f, 4.0f, 5.0f });

    // Log entity transformations
    std::cout << "Entity 1 Position: (" << transform1->position.x << ", "
        << transform1->position.y << ", " << transform1->position.z << ")\n";
    std::cout << "Entity 2 Position: (" << transform2->position.x << ", "
        << transform2->position.y << ", " << transform2->position.z << ")\n";

    // Start the application
    app.start();

    return 0;
}
