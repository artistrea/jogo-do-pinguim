#ifndef FACE_H_
#define FACE_H_
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "Component.h"
#include "Timer.h"
#include <queue>

class Alien : public Component {
public:
    Alien(GameObject& associated, int nMinions);
    ~Alien();

    void Start();
    void Update(double dt);
    void Render();
    bool Is(std::string type);
    void Shoot(Vec2 at);

    void NotifyCollision(GameObject& collidedWith);

    static int alienCount;
private:
    int hp;
    Vec2 speed;
    std::vector<std::weak_ptr<GameObject>> minionArray;
    enum AlienState { MOVING, RESTING };
    enum AlienState state;
    Timer restTimer;
    int restTimeInSeconds;
    Vec2 destination;
};

#endif
