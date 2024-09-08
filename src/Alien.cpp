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
#include "PenguinBody.h"
#include "State.h"
#include "InputManager.h"
#include "Game.h"

int Alien::alienCount = 0;

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
    minionArray(nMinions), state(Alien::AlienState::MOVING),
    restTimer(), destination(PenguinBody::player->GetPosition() + Vec2(250 + rand() % 250, 0).GetRotated(rand())),
    restTimeInSeconds(5)
{
    this->alienCount++;
    SDL_Log("alienCount=%d", this->alienCount);
    auto *sprite = new Sprite(associated, "img/alien.png");
    associated.AddComponent(sprite);
    associated.AddComponent(new Collider(associated));
}

void Alien::Start() {
    if (this->started) return;

    double radBetweenMinions = (2 * PI) / (this->minionArray.size());
    State& stateInstance = Game::GetInstance().GetState();
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
    if (hp <= 0) {
        if (!this->associated.IsDead()) {
            this->alienCount--;
            SDL_Log("alienCount=%d", this->alienCount);

            State &stateInstance = Game::GetInstance().GetState();
            GameObject *go = new GameObject();
            double animationTime = 1; // the animation is only so long because of the sound
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

    double movespeed = 256.0;

    // state machine as alien AI
    switch (this->state) {
    case AlienState::MOVING: {
        this->speed = (this->destination +  this->associated.box.GetCenter() * -1);
        this->speed = this->speed.GetNormalized() * movespeed * dt;
        Rect positionChange(
            this->associated.box.GetCenter(), this->speed
        );

        if (positionChange.Contains(this->destination)) {
            this->associated.box.topLeftCorner = this->destination + (this->associated.box.GetCenter() + (this->associated.box.topLeftCorner * -1)) * -1;
            if (PenguinBody::player != nullptr) {
                this->Shoot(PenguinBody::player->GetPosition());
            }
            this->restTimer.Restart();
            this->restTimeInSeconds = rand() % 10 + 5;
            this->state = AlienState::RESTING;
        } else {
            this->associated.box.topLeftCorner =
                this->associated.box.topLeftCorner + positionChange.dimensions;
        }

        break;
    }
    case AlienState::RESTING: {
        this->restTimer.Update(dt);

        if ((this->restTimer.Get() - (int)this->restTimer.Get()) < 0.2) {
            if (PenguinBody::player != nullptr) {
                this->Shoot(PenguinBody::player->GetPosition());
            }
        }

        if (this->restTimer.Get() > (double)this->restTimeInSeconds) {
            if (PenguinBody::player != nullptr) {
                this->destination = PenguinBody::player->GetPosition();
                this->destination += Vec2(250 + rand() % 250, 0).GetRotated(rand());
            }

            this->state = Alien::AlienState::MOVING;
        }
        break;
    }
    default:
        break;
    }
}

void Alien::Render() {

}

void Alien::Shoot(Vec2 at) {
    Minion* closestMinionToShootLocation = nullptr;
    double closestDistante = __DBL_MAX__;

    for (size_t i=0; i < this->minionArray.size(); i++) {
        auto minionAssociatedGo = this->minionArray[i].lock().get();
        if (minionAssociatedGo == NULL) continue;
        double dist = (at + (minionAssociatedGo->box.GetCenter() * -1)).GetAbs();
        if (dist < closestDistante) {
            closestMinionToShootLocation = (Minion*)minionAssociatedGo->GetComponent("Minion");
            closestDistante = dist;
        }
    }
    if (closestMinionToShootLocation == nullptr) {
        ThrowError::Error("Alien wanted to shoot, but closestMinionToShootLocation == nullptr");
    } else {
        closestMinionToShootLocation->Shoot(at);
    }
}

bool Alien::Is(std::string type) {
    return type == "Alien";
}
