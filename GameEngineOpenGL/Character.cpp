#include "Character.h"
#include <iostream>

Character::Character(const std::string& name, int health, int damage, Team team)
    : name(name), health(health), damage(damage), team(team) {}

void Character::attack(Character& target) {
    std::cout << name << " attacks " << target.getName() << " for " << damage << " damage!\n";
    target.takeDamage(damage);
}

void Character::takeDamage(int amount) {
    health -= amount;
    std::cout << name << " takes " << amount << " damage! Remaining HP: " << health << "\n";
}

bool Character::isAlive() const {
    return health > 0;
}

const std::string& Character::getName() const {
    return name;
}

int Character::getHealth() const {
    return health;
}

int Character::getDamage() const {
    return damage;
}

Character::Team Character::getTeam() const {
    return team;
}
