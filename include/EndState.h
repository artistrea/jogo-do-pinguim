#ifndef END_STATE_H_
#define END_STATE_H_
#include "Sprite.h"
#include "State.h"
#include "Camera.h"
#include "Music.h"
#include "GameObject.h"
#include <vector>
#include <memory>


class EndState: public State {
public:
    EndState();
    ~EndState();

    void LoadAssets();
    void Update(double dt);
    void Render();

    void Start();
    void Pause();
    void Resume();

private:
    Music music;
};

#endif
