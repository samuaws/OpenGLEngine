#include "SceneControllerInput.h"
#include <iostream>

SceneControllerInput::SceneControllerInput(Camera* camera, GLFWwindow* window)
    : camera(camera), window(window), lastMouseX(400), lastMouseY(300), firstMouseMove(true) {}

void SceneControllerInput::processInput(float deltaTime) {
    static bool wasRightMouseHeld = false;  // Track previous right-click state

    // Check if the right mouse button is currently held
    bool rightMouseHeld = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

    // Reset mouse position when right mouse button is first pressed
    if (rightMouseHeld && !wasRightMouseHeld) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        lastMouseX = mouseX;
        lastMouseY = mouseY;
    }

    // Handle movement input (only when right-click is held)
    Vector3 movement(0.0f);
    if (rightMouseHeld) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) movement.z += 1.0f; // Forward
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) movement.z -= 1.0f; // Backward
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) movement.x -= 1.0f; // Left
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) movement.x += 1.0f; // Right
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) movement.y += 1.0f; // Up
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) movement.y -= 1.0f; // Down

        camera->move(movement, deltaTime);
    }

    // Handle mouse movement for rotation (only when right-click is held)
    if (rightMouseHeld) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float xOffset = static_cast<float>(mouseX - lastMouseX);
        float yOffset = static_cast<float>(lastMouseY - mouseY); // Reversed y-coordinates
        lastMouseX = mouseX;
        lastMouseY = mouseY;

        camera->rotate(Vector3(yOffset, xOffset, 0.0f));
    }

    // Update previous button state
    wasRightMouseHeld = rightMouseHeld;
}
