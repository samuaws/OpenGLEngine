#ifndef APPLICATION_H
#define APPLICATION_H

#include "WindowManager.h"
#include "Renderer.h"
#include "EntityManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include <functional>

class Application {
public:
    Application();
    ~Application();

    void start(); // Start the application
    void registerSetup(const std::function<void()>& setupFunction);

    // Getters for managers
    WindowManager* getWindowManager() const;
    SceneManager* getSceneManager() const;
    Camera* getCamera();

private:
    void run(); // Main game loop

    // Managers and Camera
    WindowManager* windowManager;
    Renderer* renderer;
    EntityManager* entityManager;
    SceneManager* sceneManager;
    Camera* camera;

    std::function<void()> setupCallback; // Callback for OpenGL-dependent setup
};

#endif // APPLICATION_H
