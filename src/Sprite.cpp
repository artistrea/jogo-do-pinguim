#include "ThrowError.h"
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
    Component(associated), clipRect() {
    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, std::string file): Component(associated) {
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
    int result = SDL_RenderCopy(
        Game::GetInstance().GetRenderer(),
        texture,
        &clipRect,
        &dest
    );

    if (result) ThrowError::SDL_Error();
}

void Sprite::Render() {
    Render(associated.box.topLeftCorner.x, associated.box.topLeftCorner.y);
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
