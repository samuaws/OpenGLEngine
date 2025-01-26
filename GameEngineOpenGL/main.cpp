#include "Application.h"
#include "ModelImporter.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    Application app;

    app.registerSetup([&]() {

        // Access managers
        auto sceneManager = app.getSceneManager();
        auto entityManager = sceneManager->getEntityManager();
        Camera* camera = app.getCamera();

        // Import a model and add it to the scene
        ModelImporter modelImporter(entityManager);
        int modelEntityID = modelImporter.importModel("Objects/dronev1.fbx");

        std::cout << "Model Imported with no error.\n";

        // Add the imported model to the active scene
        sceneManager->addEntityToActiveScene(modelEntityID);

        // Set a transform for the imported model
        auto modelEntity = entityManager->getEntity(modelEntityID);
        auto transform = modelEntity->getComponent<TransformComponent>();
        transform->setPosition({ 0.0f, 0.0f, -5.0f });
        });

    app.start();

    return 0;
}

