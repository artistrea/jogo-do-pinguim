#include "State.h"
#include "TitleState.h"
#include "StageState.h"
#include "GameObject.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"

TitleState::TitleState() {
    GameObject *go = new GameObject();

    go->AddComponent(new Sprite(*go, "img/title.jpg"));

    this->AddObject(go);
}

TitleState::~TitleState() {

}


void TitleState::LoadAssets() {

}

void TitleState::Update(double dt) {
    InputManager &inputManager =  InputManager::GetInstance();

    if (
        inputManager.QuitRequested() ||
        inputManager.KeyPress(ESCAPE_KEY)
        ) {
        quitRequested = true;
    }
    if (
        inputManager.MousePress(LEFT_MOUSE_BUTTON)
    ) {
        Game::GetInstance().Push(new StageState());
    }

    UpdateArray(dt);
}

void TitleState::Render() {
    RenderArray();
}


void TitleState::Start() {
    StartArray();
    Camera::pos = Vec2(0.0, 0.0);
}

void TitleState::Pause() {
    
}

void TitleState::Resume() {
    Camera::pos = Vec2(0.0, 0.0);
}

