#include "GameObject.h"
#include "Alien.h"
#include "Minion.h"
#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Component.h"
#include "Collider.h"
#include "Vec2.h"
#include "Bullet.h"
#include "Sprite.h"

#include <string>


void Bullet::NotifyCollision(GameObject& collidedWith) {
    Bullet *bullet = (Bullet*)collidedWith.GetComponent("Bullet");
    Alien *alien = (Alien*)collidedWith.GetComponent("Alien");
    Minion *minion = (Minion*)collidedWith.GetComponent("Minion");
    PenguinBody *penguinBody = (PenguinBody*)collidedWith.GetComponent("PenguinBody");
    PenguinCannon *penguinCannon = (PenguinCannon*)collidedWith.GetComponent("PenguinCannon");
    if (bullet == nullptr) {
        if (this->targetsPlayer && (penguinBody != nullptr || penguinCannon != nullptr)) {
            this->associated.RequestDelete();
        }
        if (!this->targetsPlayer && (alien != nullptr || minion != nullptr)) {
            this->associated.RequestDelete();
        }
    }
}

Bullet::Bullet(
    GameObject& associated,
    Vec2 speed,
    int damage,
    double maxDistance,
    std::string spriteSrc
    ): Component(associated), targetsPlayer(true), speed(speed),
    distanceLeft(maxDistance), damage(damage) {
    associated.AddComponent(new Sprite(associated, spriteSrc, 3, 0.1));
    associated.AddComponent(new Collider(associated));
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
