#include "ThrowError.h"
#include "State.h"
#include "Sprite.h"
#include "Sound.h"
#include "Camera.h"
#include "Music.h"
#include "TileMap.h"
#include "Constants.h"
#include "CameraFollower.h"
#include "InputManager.h"
#include <SDL2/SDL.h>
#include <vector>


#define _USE_MATH_DEFINES
#include <math.h>

State::State():
    music(),
    objectArray(),
    quitRequested(false),
    started(false) {}

void State::Start() {
    if (this->started) return;

    this->LoadAssets();

    for (auto &obj : this->objectArray) {
        obj->Start();
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
    objectArray.emplace_back(bg);

    GameObject* tilemapObj(new GameObject());
    TileSet* tileSet(new TileSet(64, 64, "img/tileset.png"));
	TileMap* tileMap(new TileMap(*tilemapObj, "map/tileMap.txt", tileSet));

	tilemapObj->AddComponent(tileMap);
	tilemapObj->box.topLeftCorner = {0,0};
	tilemapObj->box.dimensions = {64,64};

    objectArray.emplace_back(tilemapObj);

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
