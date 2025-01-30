#include "SceneControllerInput.h"
#include <iostream>

SceneControllerInput::SceneControllerInput(Camera* camera, GLFWwindow* window)
    : camera(camera), window(window), lastMouseX(400), lastMouseY(300), firstMouseMove(true) {}

void SceneControllerInput::processInput(float deltaTime) {
    static bool wasRightMouseHeld = false;  // Track previous right-click state
    static bool wasMiddleMouseHeld = false; // Track previous middle-click state

    // Check if mouse buttons are currently held
    bool rightMouseHeld = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
    bool middleMouseHeld = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;

    // Reset mouse position when a mouse button is first pressed
    if ((rightMouseHeld && !wasRightMouseHeld) || (middleMouseHeld && !wasMiddleMouseHeld)) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        lastMouseX = mouseX;
        lastMouseY = mouseY;
    }

    // Handle movement input (only when right-click is held)
    Vector3 movement(0.0f);
    if (rightMouseHeld) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) movement.z += 1.0f; // Flip W/S
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) movement.z -= 1.0f;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) movement.x -= 1.0f;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) movement.x += 1.0f;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) movement.y += 1.0f;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) movement.y -= 1.0f;

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

    // Handle panning (only when middle mouse button is held)
    if (middleMouseHeld) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float xOffset = static_cast<float>(mouseX - lastMouseX);
        float yOffset = static_cast<float>(lastMouseY - mouseY); // Reversed y-coordinates
        lastMouseX = mouseX;
        lastMouseY = mouseY;

        // Move the camera sideways and up/down based on cursor movement
        camera->pan(Vector3(-xOffset, yOffset, 0.0f) * deltaTime * 0.05f); // Adjust speed as needed
    }

    // Update previous button states
    wasRightMouseHeld = rightMouseHeld;
    wasMiddleMouseHeld = middleMouseHeld;
}
