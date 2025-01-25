#include <typeindex>
#include <typeinfo>

template <typename T, typename... Args>
void Entity::addComponent(Args&&... args) {
    std::size_t typeID = typeid(T).hash_code();
    components[typeID] = std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
std::shared_ptr<T> Entity::getComponent() const {
    std::size_t typeID = typeid(T).hash_code();
    auto it = components.find(typeID);
    return (it != components.end()) ? std::static_pointer_cast<T>(it->second) : nullptr;
}
