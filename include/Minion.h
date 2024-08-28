#ifndef MINION_H
#define MINION_H

#include <string>
#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"

class Minion : public Component {
public:
    Minion(
        GameObject &associated,
        std::weak_ptr<GameObject> alienCenter,
        double arcOffsetDeg
    );
    ~Minion();
    void Update(double dt);
    void Render();
    bool Is(std::string);
    void Shoot(Vec2 target);

    void NotifyCollision(GameObject& collidedWith);
private:
    std::weak_ptr<GameObject> alienCenter;
    double arc;
};

#endif // MINION_H
