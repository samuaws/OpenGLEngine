#ifndef COMBAT_COMPONENT_H
#define COMBAT_COMPONENT_H

#include "Engine/ScriptComponent.h"
#include "Engine/Entity.h"
#include <iostream>

class CombatComponent : public ScriptComponent {
public:
    CombatComponent(int health, int damage);

    void start() override;
    void update(float deltaTime) override;

    void fight(CombatComponent* opponent);
    bool isAlive() const;
    void takeDamage(int amount);

    int getHealth() const;
    int getDamage() const;

private:
    int health;
    int maxHealth;
    int damage;
};

#endif // COMBAT_COMPONENT_H
