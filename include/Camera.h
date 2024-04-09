#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

class Camera {
private:
    GameObject* focus;

public:
    void Follow(GameObject* newFocus);
    void Unfollow();
    void Update(double dt);
    Vec2 pos, speed;
};

#endif
