#include "ThrowError.h"
#include "Camera.h"
#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

bool Sprite::Is(std::string s) {
    return s == "Sprite";
}

void Sprite::Update(double dt) {

}


Sprite::Sprite(GameObject& associated):
    Component(associated), clipRect(), scale(1.0, 1.0) {
    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, std::string file): Component(associated), scale(1.0, 1.0) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open(std::string file) {
    texture = Resources::GetImage(file);

    if (!IsOpen()) {
        ThrowError::SDL_Error();
    }
    int result = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    if (result) ThrowError::SDL_Error();

    SetClip(0, 0, width, height);
}

void Sprite::SetClip(
    int x, int y,
    int w, int h
) {
    clipRect = {x, y, w, h};

    associated.box.dimensions = {(double)w, (double)h};
}

void Sprite::Render(double x, double y) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = associated.box.dimensions.x;
    dest.h = associated.box.dimensions.y;
    int result = SDL_RenderCopyEx(
        Game::GetInstance().GetRenderer(),
        texture,
        &clipRect,
        &dest,
        this->associated.angleDeg,
        nullptr,
        SDL_FLIP_NONE
    );

    if (result) ThrowError::SDL_Error();
}

void Sprite::Render() {
    Render(associated.box.topLeftCorner.x + (Camera::pos.x * -1), associated.box.topLeftCorner.y + (Camera::pos.y * -1));
}

int Sprite::GetWidth() {
    return width * scale.x;
}
int Sprite::GetHeight() {
    return height * scale.y;
}
bool Sprite::IsOpen() {
    return texture != nullptr && texture != NULL;
}

// if one of the axis is eq to 0.0, won't set axis value
void Sprite::SetScale(Vec2 scale) {
    if (scale.x != 0.0) {
        // TODO: fix this calculation for when previous scale != (1,1)
        this->associated.box.topLeftCorner.x += (1 - scale.x) * this->associated.box.topLeftCorner.x / 2;
    }
    if (scale.y != 0.0) {
        this->associated.box.topLeftCorner.y += (1 - scale.y) * this->associated.box.topLeftCorner.y / 2;
    }
    if (scale.x != 0.0) {
        this->scale.x = scale.x;
    }

    if (scale.y != 0.0) {
        this->scale.y = scale.y;
    }

    this->associated.box.dimensions.y = this->GetHeight();
    this->associated.box.dimensions.x = this->GetWidth();
}

Vec2 Sprite::GetScale() {
    return scale;
}
