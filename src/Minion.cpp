#include <string>
#include "Component.h"
#include "Rect.h"
#include "Constants.h"
#include "Sprite.h"
#include "Vec2.h"
#include "GameObject.h"
#include "Minion.h"

Minion::Minion(
    GameObject &associated,
    std::weak_ptr<GameObject> alienCenter,
    double arcOffsetDeg):
        Component(associated),
        alienCenter(alienCenter),
        arc(arcOffsetDeg) {
    associated.AddComponent(new Sprite(associated, "img/minion.png"));
}

Minion::~Minion() {}

void Minion::Update(double dt) {
    GameObject* lockedAlien = alienCenter.lock().get();
    
    if (lockedAlien == nullptr) {
        this->associated.RequestDelete();
        return;
    }

    Vec2 rotateAround = lockedAlien->box.GetCenter();

    double velocity = PI/3;
    Vec2 newCenter(0, 130);
    arc += velocity * dt;
    if (arc > PI) arc -= 2*PI;

    newCenter = rotateAround + newCenter.GetRotated(arc);

    this->associated.box.topLeftCorner = newCenter + this->associated.box.dimensions * -0.5;
}

void Minion::Render() {

}

bool Minion::Is(std::string type) {
    return type == "Minion";
}

void Minion::Shoot(Vec2 target) {
    // TODO: actual shoot
}
