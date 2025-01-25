#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

Renderer::Renderer() {
    // Constructor logic if needed
}

Renderer::~Renderer() {
    // Destructor logic if needed
}

bool Renderer::initialize() {
    // Initialize GLAD after making the OpenGL context current
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return false;
    }

    setupOpenGL();
    return true;
}

void Renderer::setupOpenGL() {
    // Set OpenGL settings
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // Set the clear color
    glEnable(GL_DEPTH_TEST);              // Enable depth testing
}

void Renderer::clear() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(SceneManager* sceneManager) {
    if (!sceneManager || !sceneManager->getActiveScene()) {
        std::cerr << "No active scene to render.\n";
        return;
    }
    
    const auto& entities = sceneManager->getActiveScene()->getEntities();

    // Iterate through all entities in the active scene
    for (int entityID : entities) {
        auto entity = sceneManager->getEntityManager()->getEntity(entityID);

        // Check if the entity has a MeshRendererComp
        auto meshRenderer = entity->getComponent<MeshRendererComp>();
        if (meshRenderer) {
            renderEntity(entity); // Render the entity
        }
    }
}

void Renderer::renderEntity(const std::shared_ptr<Entity>& entity) {
    // Get the MeshRendererComp and TransformComponent
    auto meshRenderer = entity->getComponent<MeshRendererComp>();
    auto transform = entity->getComponent<TransformComponent>();

    if (!meshRenderer || !transform) {
        return; // Skip rendering if required components are missing
    }

    // Use the transform data (position, rotation, scale) for rendering
    glPushMatrix();

    // Apply transformations
    glTranslatef(transform->position.x, transform->position.y, transform->position.z);
    glRotatef(transform->rotation.x, 1.0f, 0.0f, 0.0f); // Rotate around X-axis
    glRotatef(transform->rotation.y, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis
    glRotatef(transform->rotation.z, 0.0f, 0.0f, 1.0f); // Rotate around Z-axis
    glScalef(transform->scale.x, transform->scale.y, transform->scale.z);

    // Render the mesh using OpenGL
    meshRenderer->render();

    glPopMatrix();
}
