#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.h"
#include <string>

class GameObject;

class Component {
public:
    Component(GameObject &associated);
    virtual ~Component();
    void virtual Start();
    void virtual Update(double dt) = 0;
    void virtual Render() = 0;
    bool virtual Is(std::string type) = 0;
    void virtual NotifyCollision(GameObject& collidedWith);

protected:
    GameObject &associated;
    bool started;
};

#endif
