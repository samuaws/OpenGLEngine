#ifndef RENDERER_H
#define RENDERER_H

#include "SceneManager.h" // Include SceneManager to access entities in the active scene
#include "TransformComponent.h"
#include "MeshRendererComp.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool initialize();
    void clear();
    void render(SceneManager* sceneManager); // Render all entities in the scene

private:
    void setupOpenGL(); // Setup OpenGL settings

    // Helper to render a single entity
    void renderEntity(const std::shared_ptr<Entity>& entity);
};

#endif // RENDERER_H
