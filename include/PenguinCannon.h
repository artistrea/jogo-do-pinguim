#ifndef PENGUIN_CANNON_H
#define PENGUIN_CANNON_H

#include "Component.h"
#include "GameObject.h"
#include "Timer.h"

class PenguinCannon : public Component {
public:
    PenguinCannon(GameObject &associated, std::weak_ptr<GameObject> penguinBody);

    void Update(double dt);
    void Render();
    bool Is(std::string type);

    void Shoot(Vec2 target);

    void NotifyCollision(GameObject& collidedWith);
private:
    std::weak_ptr<GameObject> pbody;
    double angleDeg;
    Timer shootIntervalTimer;
};


#endif // PENGUIN_CANNON_H
