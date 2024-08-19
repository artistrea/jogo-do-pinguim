#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "Constants.h"
#include "Minion.h"
#include "Camera.h"
#include "Component.h"
#include "Alien.h"
#include "Sound.h"
#include "Sprite.h"
#include "State.h"
#include "InputManager.h"

Alien::Alien(GameObject& associated, int nMinions):
    Component(associated), hp(30), speed(0.0, 0.0),
    minionArray(nMinions), taskQueue()
{
    // ALIEN CREATE
    associated.AddComponent(new Sprite(associated, "img/alien.png"));
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
        this->associated.RequestDelete();
    }

    if (this->associated.IsDead()) return;

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

    double movespeed = 10.0;
    if (this->taskQueue.size()) {
        Action action = this->taskQueue.front();
        switch (action.type) {
        case Action::ActionType::SHOOT:
            /* TODO */
            this->taskQueue.pop();
            break;

        case Action::ActionType::MOVE: {
            this->speed = (action.pos +  this->associated.box.topLeftCorner * -1);
            this->speed = this->speed.GetNormalized() * movespeed;
            Rect positionChange(
                this->associated.box.topLeftCorner, this->speed
            );

            if (positionChange.Contains(action.pos)) {
                this->associated.box.topLeftCorner = action.pos;
                this->taskQueue.pop();
            } else {
                this->associated.box.topLeftCorner =
                    positionChange.topLeftCorner + positionChange.dimensions;
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



