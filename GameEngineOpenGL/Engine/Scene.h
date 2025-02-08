#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>

class Scene {
public:
    Scene(const std::string& name);

    void addEntity(int entityID);
    const std::vector<int>& getEntities() const;
    const std::string& getName() const;

private:
    std::string name;            // Scene name
    std::vector<int> entities;   // List of entity IDs
};

#endif // SCENE_H
