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
    virtual ~State();

    virtual void LoadAssets() = 0;
    virtual void Update(double dt) = 0;
    virtual void Render() = 0;

    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;

    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

    bool QuitRequested();
    bool PopRequested();

protected:
    void StartArray();
    virtual void UpdateArray(double dt);
    virtual void RenderArray();

    bool popRequested;
    bool quitRequested;
    bool started;

    std::vector<std::shared_ptr<GameObject>> objectArray;
};

#endif