#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include <memory>
#include <vector>
#include "Component.h"
#include "ScriptComponent.h"
#include "TransformComponent.h"

class Entity {
public:
    Entity(int id);
    ~Entity();

    int getID() const;

    // Add a new component of type T
    template <typename T, typename... Args>
    std::shared_ptr<T> addComponent(Args&&... args) {
        std::size_t typeID = typeid(T).hash_code();
        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        components[typeID] = component;

        // If it's a ScriptComponent, store it separately for updates
        auto scriptComponent = std::dynamic_pointer_cast<ScriptComponent>(component);
        if (scriptComponent) {
            scriptComponent->setEntity(this); //  Set the entity reference
            scriptComponents.push_back(scriptComponent);
        }

        return component;
    }


    // Retrieve an existing component of type T
    template <typename T>
    std::shared_ptr<T> getComponent() {
        std::size_t typeID = typeid(T).hash_code();
        auto it = components.find(typeID);
        if (it != components.end()) {
            return std::dynamic_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    // Initialize default components
    void initializeDefaultComponents();

    // Call start() on all script components
    void startScripts();

    // Call update() on all script components
    void updateScripts(float deltaTime);

private:
    int id;
    std::unordered_map<std::size_t, std::shared_ptr<Component>> components;
    std::vector<std::shared_ptr<ScriptComponent>> scriptComponents;
};

#endif // ENTITY_H
