#ifndef GAME_H_
#define GAME_H_

#include "State.h"
#include <iostream>
#include <SDL2/SDL.h>

class Game {
private:
    Game(const char* title, int width, int height);
    static Game *instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State *state;

public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
};

#endif
