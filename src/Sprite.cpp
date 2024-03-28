#include "ThrowError.h"
#include "Sprite.h"
#include "Game.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Sprite::Sprite(): clipRect() {
    texture = nullptr;
}
Sprite::Sprite(const char* file) {
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
}

void Sprite::Render(int x, int y) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = clipRect.w;
    dest.h = clipRect.h;
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
