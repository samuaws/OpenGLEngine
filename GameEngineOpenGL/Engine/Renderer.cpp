#include "Renderer.h"
#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp> // For matrix operations
#include "MeshRendererComp.h"


Renderer::Renderer() {
    // Constructor logic if needed
}

Renderer::~Renderer() {
    // Destructor logic if needed
}

bool Renderer::initialize() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return false;
    }

    setupOpenGL();
    return true;
}

void Renderer::setupOpenGL() {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // Set the clear color
    glEnable(GL_DEPTH_TEST);              // Enable depth testing
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(SceneManager* sceneManager, Camera* camera) {
    if (!sceneManager || !sceneManager->getActiveScene()) {
        std::cerr << "No active scene to render.\n";
        return;
    }

    const auto& entities = sceneManager->getActiveScene()->getEntities();

    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 projectionMatrix = camera->getProjectionMatrix(800.0f / 600.0f);

    // Iterate over all entities in the scene
    for (int entityID : entities) {
        auto entity = sceneManager->getEntityManager()->getEntity(entityID);

        // Check if the entity has a MeshRendererComp and a TransformComponent
        auto meshRenderer = entity->getComponent<MeshRendererComp>();
        auto transform = entity->getComponent<TransformComponent>();

        if (meshRenderer && transform) {
            // Calculate the model matrix
            glm::mat4 modelMatrix = calculateModelMatrix(transform.get());

         /*   std::cout << "Cheking Transform before Render "
                << transform->position.x << ", "
                << transform->position.y << ", "
                << transform->position.z << std::endl;*/

            // Combine model, view, and projection matrices
            glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

            // Pass the MVP matrix to the mesh renderer (use it in shaders)
            meshRenderer->render(mvpMatrix);
        }
    }
}

glm::mat4 Renderer::calculateModelMatrix(const TransformComponent* transform) const {
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    // Apply translation
    modelMatrix = glm::translate(modelMatrix, glm::vec3(transform->position.x, transform->position.y, transform->position.z));

    // Apply rotation
    modelMatrix = glm::rotate(modelMatrix, glm::radians(transform->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // X-axis
    modelMatrix = glm::rotate(modelMatrix, glm::radians(transform->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Y-axis
    modelMatrix = glm::rotate(modelMatrix, glm::radians(transform->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Z-axis

    // Apply scale
    modelMatrix = glm::scale(modelMatrix, glm::vec3(transform->scale.x, transform->scale.y, transform->scale.z));

    return modelMatrix;
}
