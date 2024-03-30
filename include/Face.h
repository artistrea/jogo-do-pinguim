#ifndef FACE_H_
#define FACE_H_
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "Component.h"

class Face : public Component {
public:
    Face(GameObject& associated);
    ~Face();

    void Damage(int damage);

    void Update(double dt);
    void Render();

    bool Is(std::string type);
    bool IsDying();
private:
    int hitpoints;
    bool isDying;
};

#endif
