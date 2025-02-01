#include "Application.h"
#include "ModelImporter.h"
#include "CustomScript.h"
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    Application app;

    app.registerSetup([&]() {
        // Access managers
        auto sceneManager = app.getSceneManager();
        auto entityManager = sceneManager->getEntityManager();

        // Import a model and add it to the scene
        ModelImporter modelImporter(entityManager);
        int modelEntityID = modelImporter.importModel("Objects/dronev1.fbx");
        auto entity = entityManager->getEntity(modelEntityID);
        entity->addComponent<CustomScript>(); // Add a script to test behavior

        std::cout << "Model Imported Successfully, Entity ID: " << modelEntityID << std::endl;

        // Add the model to the active scene
        sceneManager->addEntityToActiveScene(modelEntityID);


        std::cout << "Scene setup completed. Starting Application...\n";
        });

    app.start();

    return 0;
}
