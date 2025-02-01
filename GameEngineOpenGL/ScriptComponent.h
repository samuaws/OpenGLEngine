#ifndef SCRIPT_COMPONENT_H
#define SCRIPT_COMPONENT_H

#include "Component.h"

// Forward Declaration (Tells the compiler "Entity exists" without including it)
class Entity;

class ScriptComponent : public Component {
public:
    virtual ~ScriptComponent() = default;

    // Called once when the entity is initialized
    virtual void start() {}

    // Called every frame with delta time
    virtual void update(float deltaTime) {}

    //  Set the entity this script is attached to
    void setEntity(Entity* ent) { entity = ent; }

protected:
    Entity* entity = nullptr; //  Pointer to the entity (defined later)
};

#endif // SCRIPT_COMPONENT_H
