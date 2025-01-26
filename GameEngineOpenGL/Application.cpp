#include "Application.h"
#include <GLFW/glfw3.h>
#include <iostream>

Application::Application() {
    // Initialize managers and the camera
    windowManager = new WindowManager();
    renderer = new Renderer();
    entityManager = new EntityManager();
    sceneManager = new SceneManager(entityManager);
    camera = new Camera();
}

Application::~Application() {
    // Cleanup
    delete camera;
    delete sceneManager;
    delete entityManager;
    delete renderer;
    delete windowManager;
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

    // Step 3: Create the default scene
    std::cout << "Creating default scene..." << std::endl;
    sceneManager->createScene("MainScene");
    sceneManager->loadScene("MainScene");
    std::cout << "Default scene 'MainScene' created and loaded." << std::endl;

    // Step 4: Run any additional OpenGL-dependent setup (if a setup callback is registered)
    if (setupCallback) {
        std::cout << "Running setup callback..." << std::endl;
        setupCallback();
    }

    // Step 5: Enter the main game loop
    run();
}


void Application::registerSetup(const std::function<void()>& setupFunction) {
    setupCallback = setupFunction;
}


void Application::run() {
    GLFWwindow* window = windowManager->getWindow();

    // Set the cursor mode for free-fly camera
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Variables for delta time
    float lastFrameTime = glfwGetTime();
    float currentFrameTime;

    std::cout << "Is it even entering the loop.\n";
    while (!windowManager->shouldCloseWindow()) {

        currentFrameTime = glfwGetTime();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // Handle input
        Vector3 movement(0.0f);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) movement.z -= 1.0f;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) movement.z += 1.0f;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) movement.x -= 1.0f;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) movement.x += 1.0f;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) movement.y += 1.0f;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) movement.y -= 1.0f;

        camera->move(movement, deltaTime);

        // Handle mouse movement
        static double lastMouseX = 400, lastMouseY = 300;
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float xOffset = static_cast<float>(mouseX - lastMouseX);
        float yOffset = static_cast<float>(lastMouseY - mouseY); // Reversed y-coordinates
        lastMouseX = mouseX;
        lastMouseY = mouseY;

        camera->rotate(Vector3(yOffset, xOffset, 0.0f));

        // Render the scene
        renderer->clear();
        renderer->render(sceneManager, camera); // Pass the camera to the renderer

        // Update the window
        windowManager->update();
    }

    // Shutdown the window manager
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
