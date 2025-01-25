#include "SceneManager.h"
#include <iostream>
#include <fstream>
//#include <nlohmann/json.hpp> // JSON library for serialization

//using json = nlohmann::json;

SceneManager::SceneManager(EntityManager* entityManager) : entityManager(entityManager), activeScene(nullptr) {}

SceneManager::~SceneManager() {}

void SceneManager::createScene(const std::string& sceneName) {
    if (scenes.find(sceneName) != scenes.end()) {
        std::cerr << "Scene '" << sceneName << "' already exists.\n";
        return;
    }

    scenes[sceneName] = std::make_shared<Scene>(sceneName);
    std::cout << "Scene '" << sceneName << "' created successfully.\n";
}

//bool SceneManager::loadScene(const std::string& sceneName) {
//    if (scenes.find(sceneName) == scenes.end()) {
//        std::cerr << "Scene '" << sceneName << "' not found. Attempting to load from file...\n";
//
//        auto loadedScene = deserializeScene(sceneName + ".json");
//        if (loadedScene) {
//            scenes[sceneName] = loadedScene;
//            activeScene = loadedScene;
//            std::cout << "Scene '" << sceneName << "' loaded from file successfully.\n";
//            return true;
//        }
//
//        std::cerr << "Failed to load scene '" << sceneName << "'.\n";
//        return false;
//    }
//
//    activeScene = scenes[sceneName];
//    std::cout << "Scene '" << sceneName << "' is now active.\n";
//    return true;
//}
//
//bool SceneManager::saveScene(const std::string& sceneName) const {
//    auto it = scenes.find(sceneName);
//    if (it == scenes.end()) {
//        std::cerr << "Scene '" << sceneName << "' not found.\n";
//        return false;
//    }
//
//    serializeScene(it->second, sceneName + ".json");
//    std::cout << "Scene '" << sceneName << "' saved to file successfully.\n";
//    return true;
//}

void SceneManager::addEntityToActiveScene(int entityID) {
    if (!activeScene) {
        std::cerr << "No active scene to add an entity to.\n";
        return;
    }

    activeScene->addEntity(entityID);
    std::cout << "Entity " << entityID << " added to active scene.\n";
}

const std::shared_ptr<Scene> SceneManager::getActiveScene() const {
    return activeScene;
}

//void SceneManager::serializeScene(const std::shared_ptr<Scene>& scene, const std::string& filePath) const {
//    json j;
//    j["name"] = scene->getName();
//    j["entities"] = scene->getEntities();
//
//    std::ofstream file(filePath);
//    if (!file.is_open()) {
//        std::cerr << "Failed to open file for writing: " << filePath << "\n";
//        return;
//    }
//
//    file << j.dump(4); // Pretty print with 4 spaces
//}
//
//std::shared_ptr<Scene> SceneManager::deserializeScene(const std::string& filePath) const {
//    std::ifstream file(filePath);
//    if (!file.is_open()) {
//        std::cerr << "Could not open file: " << filePath << "\n";
//        return nullptr;
//    }
//
//    json j;
//    file >> j;
//
//    auto scene = std::make_shared<Scene>(j["name"].get<std::string>());
//    for (int entityID : j["entities"]) {
//        scene->addEntity(entityID);
//    }
//
//    return scene;
//}
