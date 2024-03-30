#include "ThrowError.h"
#include "Sprite.h"
#include "Game.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool Sprite::Is(std::string s) {
    return s == "Sprite";
}

void Sprite::Update(double dt) {

}



Sprite::Sprite(GameObject& associated):
    Component(associated), clipRect() {
    texture = nullptr;
}
Sprite::Sprite(GameObject& associated, const char* file): Component(associated) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
}

void Sprite::Open(const char* file) {
    if (IsOpen()) {
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(
        Game::GetInstance().GetRenderer(),
        file
    );

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
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;

    associated.box.dimensions = {(double)w, (double)h};
}

void Sprite::Render() {
    SDL_Rect dest;
    dest.x = associated.box.topLeftCorner.x;
    dest.y = associated.box.topLeftCorner.y;
    dest.w = associated.box.dimensions.x;
    dest.h = associated.box.dimensions.y;
    int result = SDL_RenderCopy(
        Game::GetInstance().GetRenderer(),
        texture,
        &clipRect,
        &dest
    );

    if (result) ThrowError::SDL_Error();
}

int Sprite::GetWidth() {
    return width;
}
int Sprite::GetHeight() {
    return height;
}
bool Sprite::IsOpen() {
    return texture != nullptr && texture != NULL;
}
