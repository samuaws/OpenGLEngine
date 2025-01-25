#include "Application.h"
#include <iostream>

Application::Application() {
    // Initialize managers
    windowManager = new WindowManager();
    renderer = new Renderer();
    entityManager = new EntityManager();
    sceneManager = new SceneManager(entityManager);
}

Application::~Application() {
    // Cleanup all managers
    delete sceneManager;
    delete entityManager;
    delete renderer;
    delete windowManager;
}

void Application::start() {
    // Initialize the window
    if (!windowManager->initializeWindow(800, 600, "Game Engine Window")) {
        std::cerr << "Failed to initialize the window!" << std::endl;
        return;
    }

    // Initialize the renderer
    if (!renderer->initialize()) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return;
    }

    // Initialize the scene
    sceneManager->createScene("MainScene");         // Create a new scene
    sceneManager->loadScene("MainScene");           // Load and set it as active

    // Log success
    std::cout << "Scene 'MainScene' created and loaded.\n";

    // Run the main loop
    run();
}

void Application::run() {
    while (!windowManager->shouldCloseWindow()) {
        // Clear the screen
        renderer->clear();

        // Render all entities in the active scene
        renderer->render(sceneManager);

        // Update the window
        windowManager->update();
    }

    // Shutdown the window manager
    windowManager->shutdown();
}
