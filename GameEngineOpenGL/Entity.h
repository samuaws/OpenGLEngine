#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include <memory>
#include "Component.h"
#include "TransformComponent.h"

class Entity {
public:
    explicit Entity(int id);
    ~Entity();

    // Add a component to the entity
    template <typename T, typename... Args>
    void addComponent(Args&&... args);

    // Get a component from the entity
    template <typename T>
    std::shared_ptr<T> getComponent() const;

    // Get entity ID
    int getID() const;

private:
    int id;
    std::unordered_map<std::size_t, std::shared_ptr<Component>> components;

    // Initialize with a default TransformComponent
    void initializeDefaultComponents();
};

#include "Entity.inl"

#endif // ENTITY_H
