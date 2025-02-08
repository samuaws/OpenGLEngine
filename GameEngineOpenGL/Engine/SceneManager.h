#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "EntityManager.h"
#include "Scene.h"
#include "SceneControllerInput.h"
#include <unordered_map>
#include <memory>
#include <string>

class SceneManager {
public:
    SceneManager(EntityManager* entityManager);
    ~SceneManager();

    void createScene(const std::string& sceneName);
    bool loadScene(const std::string& sceneName);
    bool saveScene(const std::string& sceneName) const;
    void addEntityToActiveScene(int entityID);

    const std::shared_ptr<Scene> getActiveScene() const;
    EntityManager* getEntityManager() const;

    void updateActiveScene(float deltaTime); // Update function to execute scripts

    // Scene input management
    void processInput(float deltaTime);
    void initializeSceneInput(Camera* camera, GLFWwindow* window);

private:
    EntityManager* entityManager;
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> activeScene;
    SceneControllerInput* sceneInput;

    void serializeScene(const std::shared_ptr<Scene>& scene, const std::string& filePath) const;
    std::shared_ptr<Scene> deserializeScene(const std::string& filePath) const;
};

#endif // SCENEMANAGER_H
