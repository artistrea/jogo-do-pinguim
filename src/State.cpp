#include "State.h"
#include "GameObject.h"

State::State(): popRequested(false), quitRequested(false), started(false) {
}

State::~State() {
    this->objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject *go) {
    if (this->started) go->Start();

    std::shared_ptr<GameObject> shared_go(go);

    objectArray.push_back(shared_go);

    return std::weak_ptr<GameObject>(shared_go);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for (auto &obj: this->objectArray) {
        if (obj.get() == go) {
            return std::weak_ptr<GameObject>(obj);
        }
    }

    return std::weak_ptr<GameObject>();
}

bool State::QuitRequested() {
    return this->quitRequested;
}

bool State::PopRequested() {
    return this->popRequested;
}

void State::StartArray() {
    // @important: we cannot use reference because Start() may add new values
    // INVALID: for (auto const &obj : this->objectArray) {
    for (size_t i=0; i<objectArray.size(); i++) {
        objectArray[i]->Start();
    }
}

void State::UpdateArray(double dt) {
    for (size_t i=0; i<objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray() {
    for (size_t i=0; i<objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}


