#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"
#include "EntityManager.h"
#include "SceneControllerInput.h"
#include <unordered_map>
#include <memory>
#include <string>

class SceneManager {
public:
    SceneManager(EntityManager* entityManager);
    ~SceneManager();

    // Scene management
    void createScene(const std::string& sceneName);
    bool loadScene(const std::string& sceneName);
    bool saveScene(const std::string& sceneName) const;

    // Entity management in active scene
    void addEntityToActiveScene(int entityID);
    const std::shared_ptr<Scene> getActiveScene() const;

    // Get the EntityManager
    EntityManager* getEntityManager() const;

    void processInput(float deltaTime);
    void initializeSceneInput(Camera* camera, GLFWwindow* window);

private:
    EntityManager* entityManager; // Pointer to the EntityManager
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> activeScene;

    // Helper function to serialize/deserialize a scene
    void serializeScene(const std::shared_ptr<Scene>& scene, const std::string& filePath) const;
    std::shared_ptr<Scene> deserializeScene(const std::string& filePath) const;

    SceneControllerInput* sceneInput;
};

#endif // SCENEMANAGER_H
