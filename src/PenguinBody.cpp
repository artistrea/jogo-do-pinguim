#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "GameObject.h"
#include "Component.h"
#include "Constants.h"
#include "Sprite.h"
#include "State.h"
#include "InputManager.h"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated):
    Component(associated), pcannon(), speed(0.0, 0.0),
    linearSpeed(0.0), angleDeg(0.0), hp(20)
{
    associated.AddComponent(new Sprite(associated, "img/penguin.png"));
    this->player = this;
    SDL_Log("built successfully");
}

PenguinBody::~PenguinBody() {
    this->player = nullptr;
}

void PenguinBody::Start() {
    SDL_Log("started successfully");
    if (this->started) return;
    State &state = State::GetInstance();
    auto go = new GameObject();

    auto cannon = new PenguinCannon(*go, state.GetObjectPtr(&this->associated));
    go->AddComponent(cannon);
    state.AddObject(go);

    this->pcannon = state.GetObjectPtr(go);
    this->started = true;
}

void PenguinBody::Update(double dt) {
    if (this->hp <= 0) {
        if (!this->associated.IsDead()) {
            this->associated.RequestDelete();
        }

        return;
    }

    // TODO: change the movement to be the way asked on the instructions
    auto &inputManager = InputManager::GetInstance();
    // simulating friction:
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


    this->speed = speed + acceleration * dt * 1500;

    if (speed.GetAbs() > 300) speed = speed.GetNormalized() * 300;

    this->angleDeg = this->speed.GetRotation() * 180 / PI;
    this->associated.angleDeg = this->angleDeg;

    this->associated.box.topLeftCorner += speed * dt;
}

void PenguinBody::Render() {

}

bool PenguinBody::Is(std::string type) {
    return "PenguinBody" == type;
}


// class PenguinBody : public Component {
// public:
//     PenguinBody(GameObject &associated);
//     ~PenguinBody();

//     void Start();
//     void Update(double dt);
//     void Render();
//     bool Is(std::string type);

//     static PenguinBody* player;
// private:
//     std::weak_ptr<GameObject> pcannon;
//     Vec2 speed;
//     double linearSpeed;
//     double angleDeg;
//     int hp;
// };

