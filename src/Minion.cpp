#include <string>
#include "Bullet.h"
#include "Component.h"
#include "Rect.h"
#include "Constants.h"
#include "Sprite.h"
#include "State.h"
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
    auto *sprite = new Sprite(associated, "img/minion.png");

    this->associated.angleDeg = arcOffsetDeg * 180 / PI;
    // escala aleatória entre [1.0, 1.5]
    double newScale = (double)((rand() % 51) + 100) / 100.0;

    sprite->SetScale(Vec2{ newScale, newScale });

    associated.AddComponent(sprite);
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
    Vec2 newCenter(0, 140);
    arc += velocity * dt;
    if (arc > PI) arc -= 2*PI;

    // rotate around itself
    this->associated.angleDeg = arc * 180 / PI;

    newCenter = rotateAround + newCenter.GetRotated(arc);

    this->associated.box.topLeftCorner = newCenter + this->associated.box.dimensions * -0.5;
}

void Minion::Render() {

}

bool Minion::Is(std::string type) {
    return type == "Minion";
}

void Minion::Shoot(Vec2 target) {
    Vec2 speed = (target + this->associated.box.GetCenter() * -1);
    speed = speed.GetNormalized() * 512.0;

    auto &state = State::GetInstance();
    auto go = new GameObject();

    go->AddComponent(new Bullet(*go, speed, 1, 1024.0, "img/minionbullet1.png"));

    go->box.topLeftCorner.x = this->associated.box.GetCenter().x - go->box.dimensions.x / 2;
    go->box.topLeftCorner.y = this->associated.box.GetCenter().y - go->box.dimensions.y / 2;
    go->box.topLeftCorner+=speed*0.1;

    go->angleDeg =
         ((go->box.GetCenter() * -1) + target).GetRotation() * 180 / PI;
 
    // SDL_Log("rotating is %f", go->angleDeg);
    // SDL_Log("speed is %f %f", speed.x, speed.y);
    // SDL_Log("TopLeftCorner is %f %f", go->box.topLeftCorner.x, go->box.topLeftCorner.y);
    // SDL_Log("Dimensions is %f %f", go->box.dimensions.x, go->box.dimensions.y);
    // SDL_Log("Minion shooting");

    state.AddObject(go);
}
