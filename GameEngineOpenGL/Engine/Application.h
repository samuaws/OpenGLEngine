#ifndef APPLICATION_H
#define APPLICATION_H

#include "WindowManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Camera.h"
#include <functional>

class Application {
public:
    static Application& getInstance(); // Global access to Application instance

    void start(); // Start the application
    void registerSetup(const std::function<void()>& setupFunction);

    // Getters for managers
    WindowManager* getWindowManager() const;
    SceneManager* getSceneManager() const;
    Camera* getCamera();

private:
    static Application instance; // Static instance for Singleton pattern

    void run(); // Main game loop
    Application(); // Private constructor (Singleton)
    ~Application(); // Destructor

    WindowManager* windowManager;
    Renderer* renderer;
    EntityManager* entityManager;
    SceneManager* sceneManager;
    Camera* camera;

    std::function<void()> setupCallback; // Callback for OpenGL-dependent setup

    // Delete copy constructor and assignment operator to prevent duplicates
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
};

#endif // APPLICATION_H
