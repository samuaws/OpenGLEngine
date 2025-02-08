#include "WindowManager.h"
#include <iostream>

WindowManager::WindowManager() : window(nullptr) {}

WindowManager::~WindowManager() {}

bool WindowManager::initializeWindow(int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return false;
    }

    // Create the window
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return false;
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);

    return true;
}

void WindowManager::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool WindowManager::shouldCloseWindow() {
    return glfwWindowShouldClose(window);
}

void WindowManager::shutdown() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

GLFWwindow* WindowManager::getWindow() const {
    return window;
}
