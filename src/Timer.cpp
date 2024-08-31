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
    return this->time;
}

