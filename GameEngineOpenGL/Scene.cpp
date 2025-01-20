#include "Scene.h"
#include <iostream>

Scene::Scene() {
    std::cout << "Scene created.\n";
}

Scene::~Scene() {
    std::cout << "Scene destroyed.\n";
}

void Scene::initialize() {
    std::cout << "Scene initialized.\n";
}

void Scene::cleanup() {
    std::cout << "Scene cleaned up.\n";
}
