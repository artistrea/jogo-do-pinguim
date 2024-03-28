#include "ThrowError.h"
#include <SDL2/SDL.h>
#include <stdexcept>

void ThrowError::Error(const char* message) {
    // windows não escreve o log de exceção no console.
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, message);
    throw std::runtime_error(message);
}

void ThrowError::SDL_Error() {
    ThrowError::Error(SDL_GetError());
}


