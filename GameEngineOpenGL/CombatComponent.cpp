#include "CombatComponent.h"
#include "Engine/Application.h"

CombatComponent::CombatComponent(int health, int damage)
    : health(health), maxHealth(health), damage(damage), inCombat(false) {} // Initialize inCombat as false

void CombatComponent::start() {
    std::cout << "CombatComponent initialized with " << health << " HP and " << damage << " attack power.\n";
}

void CombatComponent::update(float deltaTime) {
    if (health <= 0) {
        std::cout << "Entity " << entity->getID() << " has died.\n";
        Application::getInstance().getSceneManager()->getEntityManager()->deleteEntity(entity->getID());
    }

    // Reset combat status each frame (will be updated in fight())
    inCombat = false;
}

void CombatComponent::fight(CombatComponent* opponent) {
    if (!opponent || !isAlive() || !opponent->isAlive()) return;

    opponent->takeDamage(damage);
    takeDamage(opponent->getDamage());

    std::cout << "Entity " << entity->getID() << " attacked! Remaining HP: " << health << "\n";
    std::cout << "Opponent " << opponent->entity->getID() << " attacked! Remaining HP: " << opponent->getHealth() << "\n";

    // Set both entities to combat mode
    inCombat = true;
    opponent->inCombat = true;
}

bool CombatComponent::isAlive() const {
    return health > 0;
}

void CombatComponent::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

int CombatComponent::getHealth() const {
    return health;
}

int CombatComponent::getDamage() const {
    return damage;
}

// NEW: Check if entity is currently in combat
bool CombatComponent::isInCombat() const {
    return inCombat;
}
