#ifndef COLLIDER_H
#define COLLIDER_H

#include "GameObject.h"

class Collider : public Component {
public:
    Collider(GameObject& associated, Vec2 scale = Vec2(1.0, 1.0), Vec2 offset = Vec2(0.0, 0.0));
    Rect box;
    void Update(double dt);
    void Render();
    bool Is(std::string type);
    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);


private:
    Vec2 scale;
    Vec2 offset;
};

#endif // COLLIDER_H
