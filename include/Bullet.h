#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"
#include <string>

class Bullet : public Component {
public:
    Bullet(GameObject& associated,
        Vec2 speed,
        int damage,
        double maxDistance,
        std::string spriteSrc
        );
    void Update(double dt);
    void Render();
    bool Is(std::string type);
    int GetDamage();
    void NotifyCollision(GameObject& collidedWith);

    bool targetsPlayer;

private:
    Vec2 speed;
    double distanceLeft;
    int damage;
};

#endif // BULLET_H
