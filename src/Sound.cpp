#include <iostream>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include "Sound.h"
#include "ThrowError.h"
#include "Resources.h"
#include <string>

Sound::Sound(GameObject& associated):
    Component(associated), chunk(nullptr) {}

Sound::Sound(GameObject& associated, std::string file):
    Sound(associated) {
    Open(file);
}

Sound::~Sound() {
    if (!IsOpen()) return;

    Stop();
}

bool Sound::IsPlaying() {
    return IsOpen() && Mix_Playing(channel) == 1;
}

void Sound::Play(int times) {
    channel = Mix_PlayChannel(-1, chunk, times-1);

    if (channel == -1) {
        SDL_LogWarn(SDL_LOG_CATEGORY_AUDIO, "Could not play sound: ");
        SDL_LogWarn(SDL_LOG_CATEGORY_AUDIO, SDL_GetError());
    }
}

void Sound::Stop() {
    if (!IsOpen()) return;

    if (channel == -1) {
        SDL_LogWarn(SDL_LOG_CATEGORY_AUDIO, "Tried stopping non started audio.");
        return;
    }
    Mix_HaltChannel(channel);
}

void Sound::Open(std::string file) {
    chunk = Resources::GetSound(file);

    if (!IsOpen()) {
        ThrowError::SDL_Error();
    } 
}

bool Sound::IsOpen() {
    return chunk != nullptr && chunk != NULL;
}


void Sound::Update(double dt) {

}

void Sound::Render() {

}

bool Sound::Is(std::string type) {
    return type == "Sound";
}


