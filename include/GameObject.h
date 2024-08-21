#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Component.h"
#include "Rect.h"
#include <vector>
#include <memory>

class Component;

class GameObject {
public:
    GameObject();
    ~GameObject();

    void Start();
    void Update(double dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(std::string type);

    Rect box;
    double angleDeg;

private:
    std::vector<std::unique_ptr<Component>> components;
    bool isDead;
    bool started;
};

#endif
