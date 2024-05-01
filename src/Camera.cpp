#include "Game.h"
#include "Camera.h"
#include "Vec2.h"
#include "InputManager.h"

Vec2 Camera::pos(0, 0), Camera::speed(0, 0);

GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Unfollow(GameObject* mayBeFocusedOn) {
    if (mayBeFocusedOn == focus) Unfollow();
}

void Camera::Update(double dt) {
    if (focus != nullptr) {
        int windowHeight, windowWidth;
        SDL_GetWindowSize(Game::GetInstance().GetWindow(), &windowWidth, &windowHeight);

        pos = focus->box.topLeftCorner + (focus->box.dimensions / 2) + Vec2({ -windowWidth/2.0, -windowHeight/2.0 });
        return;
    }

    InputManager &inputManager = InputManager::GetInstance();

    // simulating friction on camera
    Vec2 acceleration = {-speed.x/1801, -speed.y/1801};
    // Vec2 acceleration = {0, 0};

    if (
        inputManager.IsKeyDown(UP_ARROW_KEY) ||
        inputManager.IsKeyDown(W_KEY)
    ) acceleration += {0, -1};

    if (
        inputManager.IsKeyDown(DOWN_ARROW_KEY) ||
        inputManager.IsKeyDown(S_KEY)
    ) acceleration += {0, 1};

    if (
        inputManager.IsKeyDown(LEFT_ARROW_KEY) ||
        inputManager.IsKeyDown(A_KEY)
    ) acceleration += {-1, 0};

    if (
        inputManager.IsKeyDown(RIGHT_ARROW_KEY) ||
        inputManager.IsKeyDown(D_KEY)
    ) acceleration += {1, 0};


    speed = speed + acceleration * dt * 1500;

    if (speed.GetAbs() > 300) speed = speed.GetNormalized() * 300;

    pos = pos + speed * dt;
}

