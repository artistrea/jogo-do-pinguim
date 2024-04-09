#include "InputManager.h"
#include "ThrowError.h"
#include <SDL2/SDL.h>

InputManager *InputManager::instance = nullptr;

void InputManager::Update() {
    updateCounter++;
    quitRequested = false;
	SDL_Event event;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {
        int index;

		switch (event.type)
        {
        case SDL_QUIT:
			quitRequested = true;
            SDL_Log("Opa, quit requested ein");
            break;
        case SDL_MOUSEBUTTONDOWN:
            index = event.button.button;
            mouseState[index] = true;
            mouseUpdate[index] = updateCounter;
            break;
        case SDL_MOUSEBUTTONUP:
            index = event.button.button;
            mouseState[index] = false;
            mouseUpdate[index] = updateCounter;
            break;
        case SDL_KEYDOWN:
            if (event.key.repeat) break;
            index = event.key.keysym.sym;
            keyState[index] = true;
            keyUpdate[index] = updateCounter;
            break;
        case SDL_KEYUP:
            if (event.key.repeat) break;
            index = event.key.keysym.sym;
            keyState[index] = false;
            keyUpdate[index] = updateCounter;
            break;


        default:
            break;
        }

		// if( event.type == SDL_KEYDOWN ) {
		// 	// Se não, crie um objeto
		// 		Vec2 objPos = Vec2( 200, 0 ).GetRotated( PI- + PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
		// 		AddObject((int)objPos.x, (int)objPos.y);
		// }
	}
}


bool InputManager::KeyPress(int key) {
    return (
        keyState[key] &&
        keyUpdate[key] == updateCounter
    );
}

bool InputManager::KeyRelease(int key) {
    return (
        !keyState[key] &&
        keyUpdate[key] == updateCounter
    );
}

bool InputManager::IsKeyDown(int key) {
    return (
        keyState[key]
    );
}



bool InputManager::MousePress(int button) {
    return (
        mouseState[button] &&
        mouseUpdate[button] == updateCounter
    );
}

bool InputManager::MouseRelease(int button) {
    return (
        !mouseState[button] &&
        mouseUpdate[button] == updateCounter
    );
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}


int InputManager::GetMouseY() {
    return mouseY;
}

int InputManager::GetMouseX() {
    return mouseX;
}


bool InputManager::QuitRequested() {
    return quitRequested;
}


InputManager& InputManager::GetInstance() {
    if (!instance) {
        instance = new InputManager();
    }

    return *instance;
}


InputManager::InputManager():
    mouseState{0}, mouseUpdate{0}, quitRequested{false},
    updateCounter{0}, mouseX{0}, mouseY{0} {
    if (InputManager::instance != nullptr) {
        ThrowError::Error("Tried instancing Game more than once!");
    }
}

InputManager::~InputManager() {
    delete instance;
}

