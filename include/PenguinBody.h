#ifndef PENGUIN_BODY_H
#define PENGUIN_BODY_H

#include "Component.h"
#include "GameObject.h"

class PenguinBody : public Component {
public:
    PenguinBody(GameObject &associated);
    ~PenguinBody();

    void NotifyCollision(GameObject &collidedWith);
    void Start();
    void Update(double dt);
    void Render();
    bool Is(std::string type);
    Vec2 GetPosition();

    static PenguinBody* player;
private:
    std::weak_ptr<GameObject> pcannon;
    Vec2 speed;
    double linearSpeed;
    double angleDeg;
    int hp;
};


#endif // PENGUIN_BODY_H
