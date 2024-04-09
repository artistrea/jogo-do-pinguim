#include "Camera.h"
#include "Vec2.h"
#include "InputManager.h"

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(double dt) {
    if (focus != nullptr) {
        pos = focus->box.topLeftCorner + (focus->box.dimensions / 2);
    }

    InputManager &inputManager = InputManager::GetInstance();

    speed = {0, 0};
    if (
        inputManager.IsKeyDown(UP_ARROW_KEY) ||
        inputManager.IsKeyDown(W_KEY)
    ) speed += {0, -1};

    if (
        inputManager.IsKeyDown(DOWN_ARROW_KEY) ||
        inputManager.IsKeyDown(S_KEY)
    ) speed += {0, 1};

    if (
        inputManager.IsKeyDown(LEFT_ARROW_KEY) ||
        inputManager.IsKeyDown(A_KEY)
    ) speed += {-1, 0};

    if (
        inputManager.IsKeyDown(RIGHT_ARROW_KEY) ||
        inputManager.IsKeyDown(D_KEY)
    ) speed += {1, 0};

    pos += speed.GetNormalized();
}

