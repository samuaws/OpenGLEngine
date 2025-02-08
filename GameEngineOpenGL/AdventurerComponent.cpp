#include "AdventurerComponent.h"
#include <iostream>

AdventurerComponent::AdventurerComponent(AdventurerType type) : type(type) {}

void AdventurerComponent::start() {
    std::cout << "Adventurer created: ";
    switch (type) {
    case AdventurerType::Warrior: std::cout << "Warrior"; break;
    case AdventurerType::Archer: std::cout << "Archer"; break;
    case AdventurerType::Mage: std::cout << "Mage"; break;
    }
    std::cout << "\n";
}

AdventurerType AdventurerComponent::getType() const {
    return type;
}
