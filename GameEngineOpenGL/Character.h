#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {
public:
    enum class Team { ADVENTURER, MONSTER };

    Character(const std::string& name, int health, int damage, Team team);

    // Character actions
    void attack(Character& target);
    void takeDamage(int amount);
    bool isAlive() const;

    // Getters
    const std::string& getName() const;
    int getHealth() const;
    int getDamage() const;
    Team getTeam() const;

protected:
    std::string name;
    int health;
    int damage;
    Team team;
};

#endif // CHARACTER_H
