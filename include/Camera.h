#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

class Camera {
private:
    static GameObject* focus;

public:
    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Unfollow(GameObject* mayBeFocusedOn);
    static void Update(double dt);
    static Vec2 pos, speed;
};

#endif
