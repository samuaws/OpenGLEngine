#include <typeindex>
#include <typeinfo>

template <typename T, typename... Args>
std::shared_ptr<T> Entity::addComponent(Args&&... args) {
    std::size_t typeID = typeid(T).hash_code();

    // Create and store the component
    auto component = std::make_shared<T>(std::forward<Args>(args)...);
    components[typeID] = component;

    // Return the created component
    return component;
}

template <typename T>
std::shared_ptr<T> Entity::getComponent() const {
    std::size_t typeID = typeid(T).hash_code();
    auto it = components.find(typeID);
    return (it != components.end()) ? std::static_pointer_cast<T>(it->second) : nullptr;
}
