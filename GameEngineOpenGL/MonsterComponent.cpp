#include "MonsterComponent.h"
#include <iostream>

MonsterComponent::MonsterComponent(MonsterType type) : type(type) {}

void MonsterComponent::start() {
    std::cout << "Monster created: ";
    switch (type) {
    case MonsterType::Goblin: std::cout << "Goblin"; break;
    case MonsterType::Skeleton: std::cout << "Skeleton"; break;
    }
    std::cout << "\n";
}

MonsterType MonsterComponent::getType() const {
    return type;
}
