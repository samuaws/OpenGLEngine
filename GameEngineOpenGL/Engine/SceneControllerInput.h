#ifndef SCENECONTROLLERINPUT_H
#define SCENECONTROLLERINPUT_H

#include "Camera.h"
#include <GLFW/glfw3.h>

class SceneControllerInput {
public:
    SceneControllerInput(Camera* camera, GLFWwindow* window);
    void processInput(float deltaTime);

private:
    Camera* camera;
    GLFWwindow* window;
    double lastMouseX, lastMouseY;
    bool firstMouseMove;
};

#endif // SCENECONTROLLERINPUT_H
