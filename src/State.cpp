#include "ThrowError.h"
#include "State.h"
#include "Sprite.h"
#include "Sound.h"
#include "Alien.h"
#include "Camera.h"
#include "Music.h"
#include "TileMap.h"
#include "Constants.h"
#include "PenguinBody.h"
#include "CameraFollower.h"
#include "InputManager.h"
#include <SDL2/SDL.h>
#include <vector>


#define _USE_MATH_DEFINES
#include <math.h>

State *State::instance = nullptr;

State& State::GetInstance() {
    if (!State::instance) {
        State::instance = new State();
    }

    return *State::instance;
}


State::State():
    music(),
    quitRequested(false),
    started(false),
    objectArray()
    {
    if (State::instance != nullptr) {
        ThrowError::Error("Tried instancing State more than once!");
    }
}

void State::Start() {
    if (this->started) return;

    this->LoadAssets();

    // @important: we cannot use reference because Start() may add new values
    // INVALID: for (auto const &obj : this->objectArray) {
    for (size_t i = 0; i < this->objectArray.size(); i++) {
        this->objectArray[i]->Start();
    }

    started = true;
}


State::~State() {
    objectArray.clear();
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::LoadAssets() {
    SDL_Log("started loading assets");

    GameObject* bg(new GameObject());
    bg->AddComponent(new Sprite(*bg, "img/ocean.jpg"));
    bg->AddComponent(new CameraFollower(*bg));
    objectArray.push_back(std::shared_ptr<GameObject>(bg));

    GameObject* tilemapObj(new GameObject());
    TileSet* tileSet(new TileSet(64, 64, "img/tileset.png"));
	TileMap* tileMap(new TileMap(*tilemapObj, "map/tileMap.txt", tileSet));

	tilemapObj->AddComponent(tileMap);
	tilemapObj->box.topLeftCorner = {0,0};
	tilemapObj->box.dimensions = {64,64};

    objectArray.push_back(std::shared_ptr<GameObject>(tilemapObj));

    // TODO: descobrir por que diabos se colocar isso depois do alien dá ruim..??
    GameObject *penguin(new GameObject());
    penguin->AddComponent(new PenguinBody(*penguin));
    penguin->box.topLeftCorner = Vec2(704, 640);
    objectArray.push_back(std::shared_ptr<GameObject>(penguin));

    GameObject *alien(new GameObject());
    alien->AddComponent(new Alien(*alien, 3));
    alien->box.topLeftCorner = Vec2(512, 300);
    objectArray.push_back(std::shared_ptr<GameObject>(alien));

    Camera::Follow(penguin);

    music.Open("audio/stageState.ogg");

    music.Play();
    SDL_Log("finished loading assets");
}

void State::Update(double dt) {
    InputManager &inputManager =  InputManager::GetInstance();

    if (
        inputManager.QuitRequested() ||
        inputManager.KeyPress(ESCAPE_KEY)
        ) {
        quitRequested = true;
    }

    Camera::Update(dt);

    for (size_t i=0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    for (size_t i=0; i < objectArray.size(); i++) {
        if (!objectArray[i]->IsDead()) continue;

        objectArray.erase(objectArray.begin() + i);
        i--;
    }
}

void State::Render() {
    for (size_t i=0; i<objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}

std::weak_ptr<GameObject> State::AddObject(GameObject *go) {
    if (this->started) go->Start();

    std::shared_ptr<GameObject> shared_go(go);

    objectArray.emplace_back(shared_go);

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
