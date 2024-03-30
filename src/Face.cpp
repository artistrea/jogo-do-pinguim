
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "Component.h"
#include "Face.h"
#include "Sound.h"

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
        if (
            ((Sound* )associated.GetComponent("Sound"))->IsPlaying()
        ) return;

        associated.RequestDelete();
    }
}

void Face::Render() {

}


bool Face::Is(std::string type) {
    return type == "Face";
}

