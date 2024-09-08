#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "GameObject.h"
#include "Game.h"
#include "Bullet.h"
#include "Collider.h"
#include "Component.h"
#include "Constants.h"
#include "Sprite.h"
#include "StageState.h"
#include "Sound.h"
#include "InputManager.h"

PenguinBody* PenguinBody::player = nullptr;

void PenguinBody::NotifyCollision(GameObject& collidedWith) {
    Bullet *bullet = (Bullet*)collidedWith.GetComponent("Bullet");
    if (bullet == nullptr) {
        return;
    }

    if (!bullet->targetsPlayer) {
        return;
    }

    this->hp -= bullet->GetDamage();
}

PenguinBody::PenguinBody(GameObject &associated):
    Component(associated), pcannon(), speed(0.0, 0.0),
    linearSpeed(0.0), angleDeg(0.0), hp(20)
{
    associated.AddComponent(new Sprite(associated, "img/penguin.png"));
    associated.AddComponent(new Collider(associated));
    this->player = this;
    SDL_Log("built successfully");
}

PenguinBody::~PenguinBody() {
    this->player = nullptr;
}

void PenguinBody::Start() {
    SDL_Log("started successfully");
    if (this->started) return;
    StageState &state = Game::GetInstance().GetState();
    auto go = new GameObject();

    auto cannon = new PenguinCannon(*go, state.GetObjectPtr(&this->associated));
    go->AddComponent(cannon);
    state.AddObject(go);

    this->pcannon = state.GetObjectPtr(go);
    this->started = true;
}

Vec2 PenguinBody::GetPosition() {
    return this->associated.box.GetCenter();
}

void PenguinBody::Update(double dt) {
    if (this->hp <= 0) {
        if (!this->associated.IsDead()) {
            StageState &stateInstance = Game::GetInstance().GetState();
            GameObject *go = new GameObject();
            double animationTime = 1; // the animation is only so long because of the sound
            go->AddComponent(new Sprite(*go, "img/penguindeath.png", 5,animationTime / 5.0, animationTime));
            go->box.SetCenter(this->associated.box.GetCenter());
            Sound* boom = new Sound(*go, "audio/boom.wav");
            go->AddComponent(boom);
            stateInstance.AddObject(go);
            boom->Play();

            Camera::Unfollow(&this->associated);
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

