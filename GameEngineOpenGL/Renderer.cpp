#include "Renderer.h"
#include <glad/glad.h>  // Include GLAD
#include <GLFW/glfw3.h>
#include <iostream>

Renderer::Renderer() {
    // Constructor logic if needed
}

Renderer::~Renderer() {
    // Destructor logic if needed
}

bool Renderer::initialize() {
    // Initialize GLAD after making the OpenGL context current
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return false;
    }

    setupOpenGL();
    return true;
}

void Renderer::setupOpenGL() {
    // Set OpenGL settings (you can expand this as needed)
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // Set the clear color
    glEnable(GL_DEPTH_TEST);              // Enable depth testing
}

void Renderer::clear() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render() {
    // Example rendering a triangle (expand as needed)
    glBegin(GL_TRIANGLES);    // Start drawing a triangle
    glVertex2f(-0.5f, -0.5f); // Lower left corner
    glVertex2f(0.5f, -0.5f);  // Lower right corner
    glVertex2f(0.0f, 0.5f);  // Top corner
    glEnd();
}
