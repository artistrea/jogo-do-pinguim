#include "ThrowError.h"
#include "GameData.h"
#include "EndState.h"
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

EndState::EndState():
    State(),
    music()
    {
    this->LoadAssets();
}

void EndState::Start() {
    if (this->started) return;

    music.Play();

    this->StartArray();
    Camera::pos = Vec2(0.0, 0.0);

    this->started = true;
}

void EndState::Pause() {
    this->music.Stop();
}

void EndState::Resume() {
    Camera::pos = Vec2(0.0, 0.0);
    this->music.Play();
}


EndState::~EndState() {
    this->music.Stop();
    objectArray.clear();
}

void EndState::LoadAssets() {
    GameObject *go = new GameObject();

    if (GameData::playerVictory) {
        go->AddComponent(new Sprite(*go, "img/win.jpg"));
        
        music.Open("audio/endStateWin.ogg");
    } else {
        go->AddComponent(new Sprite(*go, "img/lose.jpg"));
        music.Open("audio/endStateLose.ogg");
    }

    this->AddObject(go);
}

void EndState::Update(double dt) {
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


    UpdateArray(dt);
}

void EndState::Render() {
    RenderArray();
}
