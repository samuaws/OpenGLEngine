#ifndef RENDERER_H
#define RENDERER_H

#include "SceneManager.h"
#include "Camera.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool initialize();
    void clear();
    void render(SceneManager* sceneManager, Camera* camera); // Render entities using the camera

private:
    void setupOpenGL();

    // Helper function to calculate the model matrix
    glm::mat4 calculateModelMatrix(const TransformComponent* transform) const;
};

#endif // RENDERER_H
