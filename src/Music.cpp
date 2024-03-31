
#include "ThrowError.h"
#include "Music.h"
#include "Resources.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <string>

Music::Music() {
    music = nullptr;
}

Music::Music(std::string file) {
    music = nullptr;
    Open(file);
}

Music::~Music() {}

// if times == -1, loop infinitely
void Music::Play(int times) {
    int res = Mix_PlayMusic(music, times);
    if (res)
        ThrowError::SDL_Error();
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
    music = Resources::GetMusic(file);

    if (!IsOpen())
        ThrowError::SDL_Error();
}

bool Music::IsOpen() {
    return music != nullptr && music != NULL;
}
