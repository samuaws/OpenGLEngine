#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager() : activeScene(nullptr) {}

SceneManager::~SceneManager() {}

bool SceneManager::loadScene(const std::string& sceneName) {
    auto it = scenes.find(sceneName);
    if (it != scenes.end()) {
        activeScene = it->second;
        std::cout << "Scene '" << sceneName << "' loaded successfully.\n";
        return true;
    }
    else {
        std::cerr << "Error: Scene '" << sceneName << "' not found.\n";
        return false;
    }
}

bool SceneManager::saveScene(const std::string& sceneName) {
    auto it = scenes.find(sceneName);
    if (it != scenes.end()) {
        // Save logic for the scene (e.g., serialize to file)
        std::cout << "Scene '" << sceneName << "' saved successfully.\n";
        return true;
    }
    else {
        std::cerr << "Error: Scene '" << sceneName << "' not found.\n";
        return false;
    }
}

void SceneManager::createScene(const std::string& sceneName) {
    if (scenes.find(sceneName) == scenes.end()) {
        scenes[sceneName] = std::make_shared<Scene>();
        std::cout << "Scene '" << sceneName << "' created successfully.\n";
    }
    else {
        std::cerr << "Error: Scene '" << sceneName << "' already exists.\n";
    }
}

void SceneManager::setActiveScene(const std::string& sceneName) {
    if (loadScene(sceneName)) {
        std::cout << "Active scene set to '" << sceneName << "'.\n";
    }
}

std::shared_ptr<Scene> SceneManager::getActiveScene() const {
    return activeScene;
}
