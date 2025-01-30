#include "Application.h"
#include <iostream>

Application::Application() {
    // Initialize managers and camera
    windowManager = new WindowManager();
    renderer = new Renderer();
    entityManager = new EntityManager();
    sceneManager = new SceneManager(entityManager);
    camera = new Camera();
}

Application::~Application() {
    // Cleanup memory
    delete camera;
    delete sceneManager;
    delete entityManager;
    delete renderer;
    delete windowManager;
}

void Application::registerSetup(const std::function<void()>& setupFunction) {
    setupCallback = setupFunction;
}

void Application::start() {
    // Step 1: Initialize the window and OpenGL context
    if (!windowManager->initializeWindow(800, 600, "Game Engine Window")) {
        std::cerr << "Failed to initialize the window!" << std::endl;
        return;
    }

    // Step 2: Initialize the renderer
    if (!renderer->initialize()) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return;
    }

    // Step 3: Create and load the default scene
    std::cout << "Creating default scene..." << std::endl;
    sceneManager->createScene("MainScene");
    sceneManager->loadScene("MainScene");
    std::cout << "Default scene 'MainScene' created and loaded." << std::endl;

    // Step 4: Initialize scene input controller
    sceneManager->initializeSceneInput(camera, windowManager->getWindow());

    // Step 5: Run additional OpenGL-dependent setup (if a setup callback is registered)
    if (setupCallback) {
        std::cout << "Running setup callback..." << std::endl;
        setupCallback();
    }

    // Step 6: Enter the main game loop
    run();
}

void Application::run() {
    GLFWwindow* window = windowManager->getWindow();

    float lastFrameTime = glfwGetTime();
    float currentFrameTime;

    std::cout << "Entering main loop.\n";
    while (!windowManager->shouldCloseWindow()) {
        currentFrameTime = glfwGetTime();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // Process input via SceneManager
        sceneManager->processInput(deltaTime);

        // Render the scene
        renderer->clear();
        renderer->render(sceneManager, camera);

        // Update the window
        windowManager->update();
    }

    windowManager->shutdown();
}

WindowManager* Application::getWindowManager() const {
    return windowManager;
}

SceneManager* Application::getSceneManager() const {
    return sceneManager;
}

Camera* Application::getCamera() {
    return camera;
}
