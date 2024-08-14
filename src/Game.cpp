#include "ThrowError.h"
#include "Game.h"
#include "State.h"
#include "Resources.h"
#include "InputManager.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <stdint.h>

Game *Game::instance = nullptr;

Game::Game(std::string title, int width, int height) {
    SDL_Log("Game loading started");

    if (Game::instance != nullptr) {
        ThrowError::Error("Tried instancing Game more than once!");
    }

    int sdl_init_result = SDL_Init(
        SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER
        );

    // sdl init retorna diferente de zero se não conseguiu carregar
    if (sdl_init_result != 0) {
        ThrowError::SDL_Error();
    }
    
    int img_formats_to_load = IMG_INIT_JPG;
    int img_init_result = IMG_Init(
            img_formats_to_load
        );
    // img init retorna os loaders que conseguiu carregar
    if (img_init_result != img_formats_to_load) {
        ThrowError::SDL_Error();
    }
    
    int audio_formats_to_load = MIX_INIT_OGG;
    int mix_init_result = Mix_Init(audio_formats_to_load);
    if (mix_init_result != audio_formats_to_load) {
        ThrowError::SDL_Error();
    }

    int mix_open_audio_result = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

    if (mix_open_audio_result != 0) {
        ThrowError::SDL_Error();
    }

    int num_of_channels_to_allocate = 32;
    // int mix_allocate_channels_result =
    Mix_AllocateChannels(num_of_channels_to_allocate);
    // [TODO]
    // Talvez seja melhor deixar um jogo com menos canais de áudio do que dar um throw?
    // if (mix_allocate_channels_result != num_of_channels_to_allocate) {
    //     ThrowError::SDL_Error();
    // }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if (window == NULL || window == nullptr) {
        ThrowError::SDL_Error();
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL || renderer == nullptr) {
        ThrowError::SDL_Error();
    }

    state = new State();
    frameStart = 0;
    dt = 0.0;

    SDL_Log("Game loading ended");
}


Game::~Game() {
    delete state;

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_Quit();
}

void Game::Run() {
    state->Start();

    InputManager &inputManager =  InputManager::GetInstance();

    SDL_Log("reached while");
    while (!state->QuitRequested()) {
        CalculateDeltaTime();

        inputManager.Update();

        int res = SDL_RenderClear(renderer);
        if (res) ThrowError::SDL_Error();

        state->Update(GetDeltaTime());

        state->Render();

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    delete instance;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

SDL_Window* Game::GetWindow() {
    return window;
}

State& Game::GetState() {
    return *state;
}

void Game::CalculateDeltaTime() {
    uint64_t prevFrameStart = frameStart;
    // SDL_GetTicks "is not recommended as of SDL 2.0.18; use SDL_GetTicks64() instead"
    // se por acaso você rodar meu jogo por 49 dias seguidos, não vai dar ruim.
    // É certamente muito útil
    frameStart = SDL_GetTicks64();
    dt = (frameStart - prevFrameStart);
    dt/=1000;
}

double Game::GetDeltaTime() {
    return dt;
}

std::string GAME_TITLE = "Artur Padovesi Piratelli - 211038208";

Game& Game::GetInstance() {
    if (Game::instance == nullptr)
        Game::instance = new Game(
            GAME_TITLE,
            1024, 600
        );

    return *Game::instance;
}
