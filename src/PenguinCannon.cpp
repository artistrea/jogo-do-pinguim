#include "Bullet.h"
#include "Camera.h"
#include "Collider.h"
#include "Constants.h"
#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"
#include "State.h"
#include "InputManager.h"

void PenguinCannon::NotifyCollision(GameObject& collidedWith) {
    GameObject* bodyGo = this->pbody.lock().get();
    if (bodyGo != nullptr) {
        bodyGo->NotifyCollision(collidedWith);
    }
}

PenguinCannon::PenguinCannon(GameObject &associated, std::weak_ptr<GameObject> penguinBody):
    Component(associated), pbody(penguinBody), angleDeg(0.0), shootIntervalTimer()
{
    shootIntervalTimer.Update(1000.0);
    associated.AddComponent(new Sprite(associated, "img/cubngun.png"));
    associated.AddComponent(new Collider(associated));
}

void PenguinCannon::Update(double dt) {
    auto *body = pbody.lock().get();

    if (body == nullptr) {
        this->associated.RequestDelete();
        return;
    }

    this->associated.box.topLeftCorner =
        body->box.GetCenter() + this->associated.box.dimensions / -2;
    
    auto &inputManager = InputManager::GetInstance();

    Vec2 pointTowards(inputManager.GetMouseX() + Camera::pos.x, inputManager.GetMouseY() + Camera::pos.y);

    this->angleDeg = (pointTowards + this->associated.box.GetCenter() * -1).GetRotation() * 180 / PI;

    this->associated.angleDeg = this->angleDeg;
    shootIntervalTimer.Update(dt);
    if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        if (shootIntervalTimer.Get() >= 0.5) {
            shootIntervalTimer.Restart();
            this->Shoot(pointTowards);
        }
    }
}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(std::string type) {
    return type == "PenguinCannon";
}

void PenguinCannon::Shoot(Vec2 target) {
    Vec2 speed = (target + this->associated.box.GetCenter() * -1);
    speed = speed.GetNormalized() * 512.0;

    auto &state = Game::GetInstance().GetState();
    auto go = new GameObject();
    Bullet* bullet = new Bullet(*go, speed, 1, 1024.0, "img/minionbullet2.png");
    bullet->targetsPlayer = false;
    go->AddComponent(bullet);

    go->box.topLeftCorner.x = this->associated.box.GetCenter().x - go->box.dimensions.x / 2;
    go->box.topLeftCorner.y = this->associated.box.GetCenter().y - go->box.dimensions.y / 2;
    go->box.topLeftCorner+=speed*0.15;

    go->angleDeg =
         ((go->box.GetCenter() * -1) + target).GetRotation() * 180 / PI;
 
    // SDL_Log("rotating is %f", go->angleDeg);
    // SDL_Log("speed is %f %f", speed.x, speed.y);
    // SDL_Log("TopLeftCorner is %f %f", go->box.topLeftCorner.x, go->box.topLeftCorner.y);
    // SDL_Log("Dimensions is %f %f", go->box.dimensions.x, go->box.dimensions.y);
    // SDL_Log("Minion shooting");

    state.AddObject(go);
}
