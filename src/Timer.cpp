#include <SDL2/SDL.h>
#include "Timer.h"


Timer::Timer(): time(0.0) {}

void Timer::Update(double dt) {
    this->time += dt;
}

void Timer::Restart() {
    this->time = 0.0;
}

double Timer::Get() {
    SDL_Log("time: %f, should be bigger than \nINFO: time: %f", this->time, 3853200000.0);
    return this->time;
}

