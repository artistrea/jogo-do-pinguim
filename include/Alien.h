#ifndef FACE_H_
#define FACE_H_
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "Component.h"
#include <queue>

class Alien : public Component {
public:
    Alien(GameObject& associated, int nMinions);
    ~Alien();

    void Start();
    void Update(double dt);
    void Render();
    bool Is(std::string type);
private:
    int hp;
    Vec2 speed;
    // Parece sem sentido usar weak pointer na classe que gerencia o lifetime do ponteiro...
    std::vector<std::weak_ptr<GameObject>> minionArray;

    class Action {
    public:
        typedef enum { MOVE, SHOOT } ActionType;
        Action(ActionType type, Vec2 params); // could separate params by enum with overloading
        ~Action();
        ActionType type;
        Vec2 pos;
    };
    std::queue<Action> taskQueue;
};

#endif
