#include "Application.h"
#include "WindowManager.h"
#include "Renderer.h"
#include <iostream>

Application::Application() {
    // Initialize the WindowManager and Renderer instances
    windowManager = new WindowManager();
    renderer = new Renderer();
}

Application::~Application() {
    // Cleanup WindowManager and Renderer
    delete windowManager;
    delete renderer;
}

void Application::start() {
    if (!windowManager->initializeWindow(800, 600, "Game Engine Window")) {
        std::cerr << "Failed to initialize the window!" << std::endl;
        return;
    }

    // Initialize GLAD and renderer (OpenGL settings)
    if (!renderer->initialize()) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return;
    }

    // Run the main loop
    run();
}

void Application::run() {
    while (!windowManager->shouldCloseWindow()) {
        // Clear the screen using Renderer
        renderer->clear();

        // Render the objects
        renderer->render();

        // Update the window
        windowManager->update();
    }
    windowManager->shutdown();
}
