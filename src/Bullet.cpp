#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"
#include "Bullet.h"
#include "Sprite.h"

#include <string>


Bullet::Bullet(
    GameObject& associated,
    Vec2 speed,
    int damage,
    double maxDistance,
    std::string spriteSrc
    ): Component(associated), speed(speed),
    distanceLeft(maxDistance), damage(damage) {
    associated.AddComponent(new Sprite(associated, spriteSrc, 3, 0.1));
}

void Bullet::Update(double dt) {
    if (this->distanceLeft <= 0) return;

    Vec2 distMoved = this->speed * dt;

    this->associated.box.topLeftCorner += distMoved;
    this->distanceLeft -= distMoved.GetAbs();
    if (this->distanceLeft <= 0) this->associated.RequestDelete();
}

void Bullet::Render() {}

bool Bullet::Is(std::string type) {
    return type == "Bullet";
}

int Bullet::GetDamage() {
    return this->damage;
}
