#ifndef CUSTOMSCRIPT_H
#define CUSTOMSCRIPT_H

#include "ScriptComponent.h"
#include "TransformComponent.h"
#include <iostream>

class CustomScript : public ScriptComponent {
public:
    void start() override {
        std::cout << "CustomScript started! Entity will now move forward." << std::endl;
    }

    void update(float deltaTime) override {
        if (!entity) return; // Ensure entity is set

        // Ensure the entity has a TransformComponent
        auto transform = entity->getComponent<TransformComponent>();
        if (transform) {
            // Move entity forward (positive Z direction)
            transform->position.z += 1.0f * deltaTime; // Adjust speed if needed

            std::cout << "CustomScript: Moving entity to position "
                << transform->position.x << ", "
                << transform->position.y << ", "
                << transform->position.z << std::endl;
        }
    }
};

#endif // CUSTOMSCRIPT_H
