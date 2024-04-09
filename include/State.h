#ifndef STATE_H_
#define STATE_H_
#include "Sprite.h"
#include "Camera.h"
#include "Music.h"
#include "GameObject.h"
#include <vector>
#include <memory>


class State {
public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(double dt);
    void Render();

    void AddObject(int mouseX, int mouseY);

private:
    Camera camera;
    Music music;
    bool quitRequested;
    std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif