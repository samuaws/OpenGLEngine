#ifndef ADVENTURER_COMPONENT_H
#define ADVENTURER_COMPONENT_H

#include "Engine/ScriptComponent.h"

enum class AdventurerType { Warrior, Archer, Mage };

class AdventurerComponent : public ScriptComponent {
public:
    AdventurerComponent(AdventurerType type);

    void start() override;
    AdventurerType getType() const;

private:
    AdventurerType type;
};

#endif // ADVENTURER_COMPONENT_H
