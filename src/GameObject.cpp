#include "Sound.h"
#include "Component.h"
#include "Camera.h"
#include "GameObject.h"
#include "Rect.h"
#include <vector>
#include <memory>
#include <SDL2/SDL.h>

GameObject::GameObject(): angleDeg(0.0), components(), isDead(false), started(false) {}

GameObject::~GameObject() {
    components.clear();
}

void GameObject::Start() {
    if (this->started) return;

    for (auto &comp: this->components) {
        comp->Start();
    }

    this->started = true;
}

void GameObject::Update(double dt) {
    for (auto iter = components.rbegin(); iter != components.rend(); iter++) {
        (*iter)->Update(dt);
    }
}

void GameObject::Render() {
    for (auto iter = components.rbegin(); iter != components.rend(); iter++) {
        (*iter)->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    if (this->started) cpt->Start();

    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    // [TODO]: entender por que que isso dava erro:
    // for (auto iter = components.rbegin(); iter != components.rend(); iter++) {
    //     if ((*iter).get() == cpt) {
    //         components.erase(iter.base());
    //         return;
    //     }
    // }

    for (std::size_t i = 0; i<components.size(); i++) {
        if (components[i].get() == cpt) {
            components.erase(components.begin() + i);
            return;
        }
    }
}

Component* GameObject::GetComponent(std::string type) {
    for (std::size_t i = 0; i<components.size(); i++) {
        if (components[i]->Is(type)) {
            return components[i].get();
        }
    }

    return nullptr;
}



