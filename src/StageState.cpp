#include "ThrowError.h"
#include "EndState.h"
#include "Game.h"
#include "GameData.h"
#include "StageState.h"
#include "Collision.h"
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

StageState::StageState():
    State(),
    music(),
    willRequestPop(false),
    requestPopTimer()
    {
}

void StageState::Start() {
    if (this->started) return;

    Alien::alienCount = 0;

    this->LoadAssets();
    StartArray();


    started = true;
}

void StageState::Pause() {
    this->music.Stop();
}

void StageState::Resume() {
    this->music.Play();
}


StageState::~StageState() {
}

void StageState::LoadAssets() {
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

    GameObject *penguin(new GameObject());
    penguin->AddComponent(new PenguinBody(*penguin));
    penguin->box.topLeftCorner = Vec2(704, 640);
    objectArray.push_back(std::shared_ptr<GameObject>(penguin));

    GameObject *alien(new GameObject());
    alien->AddComponent(new Alien(*alien, 3));
    alien->box.topLeftCorner = Vec2(0, 0);
    objectArray.push_back(std::shared_ptr<GameObject>(alien));

    GameObject *alien2(new GameObject());
    alien2->AddComponent(new Alien(*alien2, 3));
    alien2->box.topLeftCorner = Vec2(704, 0);
    objectArray.push_back(std::shared_ptr<GameObject>(alien2));

    GameObject *alien3(new GameObject());
    alien3->AddComponent(new Alien(*alien3, 3));
    alien3->box.topLeftCorner = Vec2(0, 640);
    objectArray.push_back(std::shared_ptr<GameObject>(alien3));

    Camera::Follow(penguin);

    music.Open("audio/stageState.ogg");

    music.Play();
    SDL_Log("finished loading assets");
}

void StageState::Update(double dt) {
    InputManager &inputManager =  InputManager::GetInstance();

    if (
        inputManager.QuitRequested()
        ) {
        quitRequested = true;
    }

    if (
        inputManager.KeyPress(ESCAPE_KEY)
    ) {
        popRequested = true;
    }


    Camera::Update(dt);

    UpdateArray(dt);

    for (size_t i=0; i < objectArray.size(); i++) {
        if (objectArray[i]->GetComponent("Collider") == nullptr) {
            continue;
        }

        for (size_t j=i+1; j < objectArray.size(); j++) {
            if (objectArray[j]->GetComponent("Collider") == nullptr) {
                continue;
            }

            if (Collision::IsColliding(
                objectArray[i]->box, objectArray[j]->box,
                objectArray[i]->angleDeg, objectArray[j]->angleDeg)
            ) {
                objectArray[i]->NotifyCollision(*objectArray[j].get());
                objectArray[j]->NotifyCollision(*objectArray[i].get());
            }
        }
    }

    for (size_t i=0; i < objectArray.size(); i++) {
        if (!objectArray[i]->IsDead()) continue;

        objectArray.erase(objectArray.begin() + i);
        i--;
    }

    // this is done so there is a delay to let the last explosion go off
    if (
        !this->willRequestPop &&
        (Alien::alienCount == 0 || PenguinBody::player == nullptr)
    ) {
        this->willRequestPop = true;
        music.Stop(1800); // so that music fades out
        this->requestPopTimer.Restart();
    }

    if (this->willRequestPop) {
        this->requestPopTimer.Update(dt);
        if (this->requestPopTimer.Get() > 2) {
            if (Alien::alienCount == 0) {
                GameData::playerVictory = true;
            } else {
                GameData::playerVictory = false;
            }

            Game::GetInstance().Push(new EndState());
            this->popRequested = true;
        }
    }
}

void StageState::Render() {
    RenderArray();
}
