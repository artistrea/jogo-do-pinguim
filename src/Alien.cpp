#include <iostream>
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include "Bullet.h"
#include "Collider.h"
#include "Constants.h"
#include "ThrowError.h"
#include "Minion.h"
#include "Camera.h"
#include "Component.h"
#include "Alien.h"
#include "Sound.h"
#include "Sprite.h"
#include "State.h"
#include "InputManager.h"


void Alien::NotifyCollision(GameObject& collidedWith) {
    Bullet *bullet = (Bullet*)collidedWith.GetComponent("Bullet");
    if (bullet == nullptr) {
        return;
    }

    if (bullet->targetsPlayer) {
        return;
    }

    this->hp -= bullet->GetDamage();
}


Alien::Alien(GameObject& associated, int nMinions):
    Component(associated), hp(5), speed(0.0, 0.0),
    minionArray(nMinions), taskQueue()
{
    auto *sprite = new Sprite(associated, "img/alien.png");
    associated.AddComponent(sprite);
    associated.AddComponent(new Collider(associated));
}

void Alien::Start() {
    if (this->started) return;

    double radBetweenMinions = (2 * PI) / (this->minionArray.size());
    State& stateInstance = State::GetInstance();
    std::weak_ptr<GameObject> associatedSharedPtr = stateInstance.GetObjectPtr(&this->associated);

    for (size_t i = 0; i < this->minionArray.size(); i++) {
        double deg = radBetweenMinions * i;
        auto go = new GameObject();

        go->AddComponent(new Minion(*go, associatedSharedPtr, deg));

        this->minionArray[i] = stateInstance.AddObject(go);
    }

    this->started = true;
}

Alien::~Alien() {
    this->minionArray.clear();
}

void Alien::Update(double dt) {
    InputManager &inputManager = InputManager::GetInstance();

    if (hp <= 0) {
        if (!this->associated.IsDead()) {
            State &stateInstance = State::GetInstance();
            GameObject *go = new GameObject();
            double animationTime = 0.3;
            go->AddComponent(new Sprite(*go, "img/aliendeath.png", 4, animationTime / 4.0, animationTime));
            go->box.SetCenter(this->associated.box.GetCenter());
            Sound* boom = new Sound(*go, "audio/boom.wav");
            go->AddComponent(boom);
            stateInstance.AddObject(go);
            boom->Play();

            this->associated.RequestDelete();
        }
    }

    if (this->associated.IsDead()) return;

    // rotate around itself
    double velocityDeg = -20;
    this->associated.angleDeg += velocityDeg * dt;
    if (this->associated.angleDeg > 360) this->associated.angleDeg -= 360;

    if (inputManager.MousePress(RIGHT_MOUSE_BUTTON) || inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        Vec2 clickAt({ (double)inputManager.GetMouseX(), (double)inputManager.GetMouseY() });
        clickAt += Camera::pos;
        if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
            this->taskQueue.push(
                Action(Action::ActionType::SHOOT, clickAt)
            );
        } else {
            this->taskQueue.push(
                Action(Action::ActionType::MOVE, clickAt)
            );  
        }
    }

    double movespeed = 256.0;
    if (this->taskQueue.size()) {
        Action action = this->taskQueue.front();
        switch (action.type) {
        case Action::ActionType::SHOOT: {
            this->taskQueue.pop();
            Minion* closestMinionToShootLocation = nullptr;
            double closestDistante = __DBL_MAX__;

            for (size_t i=0; i<this->minionArray.size(); i++) {
                auto minionAssociatedGo = this->minionArray[i].lock().get();
                if (minionAssociatedGo == NULL) continue;
                double dist = (action.pos + (minionAssociatedGo->box.GetCenter() * -1)).GetAbs();
                if (dist < closestDistante) {
                    closestMinionToShootLocation = (Minion*)minionAssociatedGo->GetComponent("Minion");
                    closestDistante = dist;
                }
            }
            if (closestMinionToShootLocation == nullptr) {
                ThrowError::Error("Alien wanted to shoot, but closestMinionToShootLocation == nullptr");
            } else {
                closestMinionToShootLocation->Shoot(action.pos);
            }

            break;
        }

        case Action::ActionType::MOVE: {
            this->speed = (action.pos +  this->associated.box.GetCenter() * -1);
            this->speed = this->speed.GetNormalized() * movespeed * dt;
            Rect positionChange(
                this->associated.box.GetCenter(), this->speed
            );

            if (positionChange.Contains(action.pos)) {
                this->associated.box.topLeftCorner = action.pos + (this->associated.box.GetCenter() + (this->associated.box.topLeftCorner * -1)) * -1;
                this->taskQueue.pop();
            } else {
                this->associated.box.topLeftCorner =
                    this->associated.box.topLeftCorner + positionChange.dimensions;
            }
            break;
        }
        default:
            break;
        }
    }
}

void Alien::Render() {

}


bool Alien::Is(std::string type) {
    return type == "Alien";
}

Alien::Action::Action(ActionType type, Vec2 params) {
    this->pos = params;
    this->type = type;
}

Alien::Action::~Action() {}



