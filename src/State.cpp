#include "ThrowError.h"
#include "State.h"
#include "Sprite.h"
#include "Sound.h"
#include "Camera.h"
#include "Music.h"
#include "Face.h"
#include "TileMap.h"
#include "Constants.h"
#include "InputManager.h"
#include <SDL2/SDL.h>
#include <vector>


#define _USE_MATH_DEFINES
#include <math.h>

State::State(): camera(), music(), objectArray() {
    quitRequested = false;
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

    for (size_t i=0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    camera.Update(dt);

    for (size_t i=0; i < objectArray.size(); i++) {
        if (!objectArray[i]->IsDead()) continue;

        objectArray.erase(objectArray.begin() + i);
        i--;
    }

    if (inputManager.KeyPress(SPACE_KEY)) {
        Vec2 spawnAt = Vec2({ (double)inputManager.GetMouseX(), (double)inputManager.GetMouseY() })
                    +  Vec2({ 0.0, 200.0 }).GetRotated(-PI + PI*(rand() % 1001)/500.0);
        AddObject((int)spawnAt.x, (int)spawnAt.y);
    }
}

void State::Render() {
    for (size_t i=0; i<objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject* enemy(new GameObject());
    enemy->AddComponent(new Sprite(*enemy, "img/penguinface.png"));
    enemy->AddComponent(new Sound(*enemy, "audio/boom.wav"));
    enemy->AddComponent(new Face(*enemy));

	enemy->box.topLeftCorner = { (double)mouseX, (double)mouseY };

    objectArray.emplace_back(enemy);
}

