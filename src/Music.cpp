
#include "ThrowError.h"
#include "Music.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>

Music::Music() {
    music = nullptr;
}

Music::Music(const char* file) {
    music = nullptr;
    Open(file);
}

Music::~Music() {
    Mix_HaltMusic();
    Mix_FreeMusic(music);
}

// if times == -1, loop infinitely
void Music::Play(int times) {
    // [TODO]: talvez seja melhor verificar nullptr sem emitir exceção?
    int res = Mix_PlayMusic(music, times);
    if (res)
        ThrowError::SDL_Error();
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(const char* file) {
    if (IsOpen()) {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
    }

    music = Mix_LoadMUS(file);

    if (!IsOpen())
        ThrowError::SDL_Error();
}

bool Music::IsOpen() {
    return music != nullptr && music != NULL;
}
