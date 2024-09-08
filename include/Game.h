#ifndef GAME_H_
#define GAME_H_

#include "StageState.h"
#include "State.h"
#include "Camera.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <stdint.h>
#include <memory.h>
#include <stack>

class Game {
private:
    Game(std::string title, int width, int height);
    static Game *instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State *storedState;
    uint64_t frameStart;
    double dt;
    void CalculateDeltaTime();
    // maybe would be more correct to use stack<shared_ptr>
    // but since game should always be instantiaded, should cause no problems
    std::stack<std::unique_ptr<State>> stateStack;

public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    SDL_Window* GetWindow();
    State& GetCurrentState();
    static Game& GetInstance();
    double GetDeltaTime();
    void Push(State* state);
};

#endif
