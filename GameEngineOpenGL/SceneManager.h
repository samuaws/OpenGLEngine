#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>
#include <unordered_map>
#include <memory>
#include "Scene.h"

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    // Load a scene by name or ID
    bool loadScene(const std::string& sceneName);

    // Save the current scene
    bool saveScene(const std::string& sceneName);

    // Create a new scene
    void createScene(const std::string& sceneName);

    // Set the active scene
    void setActiveScene(const std::string& sceneName);

    // Get the active scene
    std::shared_ptr<Scene> getActiveScene() const;

private:
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> activeScene;
};

#endif // SCENEMANAGER_H
