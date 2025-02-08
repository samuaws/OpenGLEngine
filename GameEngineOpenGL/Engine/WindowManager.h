#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <GLFW/glfw3.h>

class WindowManager {
public:
    WindowManager();
    ~WindowManager();

    bool initializeWindow(int width, int height, const char* title);
    void update();
    bool shouldCloseWindow();
    void shutdown();

    // New getter for the GLFW window
    GLFWwindow* getWindow() const;

private:
    GLFWwindow* window; // Pointer to the GLFW window
};

#endif // WINDOWMANAGER_H
