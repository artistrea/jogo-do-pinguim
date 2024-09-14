#include "State.h"
#include "TitleState.h"
#include "Text.h"
#include "StageState.h"
#include "GameObject.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"

TitleState::TitleState(): blinkFactor(3) {
    GameObject *go = new GameObject();

    go->AddComponent(new Sprite(*go, "img/title.jpg"));

    this->AddObject(go);

    go = new GameObject();

    go->AddComponent(
        new Text(*go, "font/Call me maybe.ttf",
            16, Text::TextStyle::BLENDED,
            "To Start,",
            {0, 0, 0, 255}
        )
    );
    go->angleDeg = -17;
    go->box.dimensions = {100, 30};
    // go->box.SetCenter({ 470, 530 });
    go->box.SetCenter({ 630, 500 });

    this->AddObject(go);
    
    go = new GameObject();
    this->blinkingText = new Text(*go, "font/Call me maybe.ttf",
            32, Text::TextStyle::BLENDED,
            "Press Space!",
            {0, 0, 0, 255}
        );
    go->AddComponent(
        this->blinkingText
    );

    go->angleDeg = -15;
    go->box.dimensions = {200, 50};
    go->box.SetCenter({ 690, 535 });

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
        inputManager.KeyPress(SPACE_KEY)
    ) {
        Game::GetInstance().Push(new StageState());
    }

    SDL_Color newColor = this->blinkingText->GetColor();
    
    if (newColor.a + blinkFactor < 150 || newColor.a + blinkFactor > 255) {
        blinkFactor = -blinkFactor;
    }

    newColor.a += blinkFactor;

    this->blinkingText->SetColor(
        newColor
    );

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

