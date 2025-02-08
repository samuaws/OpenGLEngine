#include "CombatComponent.h"
#include "Engine/Application.h"


CombatComponent::CombatComponent(int health, int damage)
    : health(health), maxHealth(health), damage(damage) {}

void CombatComponent::start() {
    std::cout << "CombatComponent initialized with " << health << " HP and " << damage << " attack power.\n";
}

void CombatComponent::update(float deltaTime) {
    if (health <= 0) {
        std::cout << "Entity " << entity->getID() << " has died.\n";
        Application::getInstance().getSceneManager()->getEntityManager()->deleteEntity(entity->getID());
    }
}

void CombatComponent::fight(CombatComponent* opponent) {
    if (!opponent || !isAlive() || !opponent->isAlive()) return;

    opponent->takeDamage(damage);
    takeDamage(opponent->getDamage());

    std::cout << "Entity " << entity->getID() << " attacked! Remaining HP: " << health << "\n";
    std::cout << "Opponent " << opponent->entity->getID() << " attacked! Remaining HP: " << opponent->getHealth() << "\n";
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
