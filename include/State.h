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
    void Start();
    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
    static State &GetInstance();

private:
    Music music;
    bool quitRequested;
    bool started;
    std::vector<std::shared_ptr<GameObject>> objectArray;
    static State *instance;
};

#endif