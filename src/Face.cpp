
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "Camera.h"
#include "Component.h"
#include "Face.h"
#include "Sound.h"
#include "InputManager.h"

Face::Face(GameObject& associated): Component(associated), hitpoints(30), isDying(false) {}

Face::~Face() {}


void Face::Damage(int damage) {
    if (hitpoints <= 0) return;

    hitpoints -= damage;
    if (hitpoints > 0) return;
    
    isDying = true;
    
    ((Sound* )associated.GetComponent("Sound"))->Play();
    associated.RemoveComponent(
        associated.GetComponent("Sprite")
    );
}

bool Face::IsDying() {
    return isDying;
}

void Face::Update(double dt) {
    if (isDying) {
        Camera::Unfollow(&associated);
        if (
            ((Sound* )associated.GetComponent("Sound"))->IsPlaying()
        ) return;

        associated.RequestDelete();
        return;
    }

    Rect relativeBox(
        associated.box.topLeftCorner + (Camera::pos * -1),
        associated.box.dimensions
    );

    InputManager &inputManager = InputManager::GetInstance();
    if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        if (relativeBox.Contains(
            Vec2({ (double)inputManager.GetMouseX(), (double)inputManager.GetMouseY() })
            )
        ) {
            Damage(std::rand()%10 + 10);
        }
    }
}

void Face::Render() {

}


bool Face::Is(std::string type) {
    return type == "Face";
}

