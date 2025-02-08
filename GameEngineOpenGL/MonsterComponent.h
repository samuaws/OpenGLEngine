#ifndef MONSTER_COMPONENT_H
#define MONSTER_COMPONENT_H

#include "Engine/ScriptComponent.h"

enum class MonsterType { Goblin, Skeleton };

class MonsterComponent : public ScriptComponent {
public:
    MonsterComponent(MonsterType type);

    void start() override;
    MonsterType getType() const;

private:
    MonsterType type;
};

#endif // MONSTER_COMPONENT_H
