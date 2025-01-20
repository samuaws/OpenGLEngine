#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <GLFW/glfw3.h>

class WindowManager {
public:
    WindowManager();
    ~WindowManager();

    bool initializeWindow(int width, int height, const char* title);  // Initialize the window
    bool shouldCloseWindow(); // Check if the window should close
    void update();            // Handle rendering and window updates
    void shutdown();          // Cleanup and close the window

private:
    GLFWwindow* window;  // The GLFW window instance
};

#endif // WINDOWMANAGER_H
