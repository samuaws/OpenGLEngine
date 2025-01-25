#ifndef APPLICATION_H
#define APPLICATION_H

#include "WindowManager.h"
#include "Renderer.h"
#include "EntityManager.h"
#include "SceneManager.h"

class Application {
public:
    Application();
    ~Application();

    void start(); // Start the application

private:
    void run(); // Main game loop

    // Managers
    WindowManager* windowManager;
    Renderer* renderer;
    EntityManager* entityManager;
    SceneManager* sceneManager;
};

#endif // APPLICATION_H
