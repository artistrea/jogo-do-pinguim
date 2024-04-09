#ifndef GAME_H_
#define GAME_H_

#include "State.h"
#include "Camera.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <stdint.h>

class Game {
private:
    Game(std::string title, int width, int height);
    static Game *instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State *state;
    uint64_t frameStart;
    double dt;
    void CalculateDeltaTime();

public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
    double GetDeltaTime();
};

#endif
