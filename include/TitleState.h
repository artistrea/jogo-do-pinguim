#ifndef TITLE_STATE_H_
#define TITLE_STATE_H_

#include "State.h"
#include "Text.h"

class TitleState: public State {
private:
    Text* blinkingText;
    int blinkFactor;

public:
    TitleState();
    ~TitleState();

    void LoadAssets();
    void Update(double dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};

#endif
