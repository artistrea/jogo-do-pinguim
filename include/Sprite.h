#ifndef SPRITE_H_
#define SPRITE_H_
#include "Component.h"
#include "Timer.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <memory>

class Sprite : public Component {
public:
    Sprite(GameObject& associated);
    Sprite(GameObject& associated, std::string file, int frameCount=1, double frameTime=1.0, double secondsToSelfDestruct=0.0);
    ~Sprite();
    void Open(std::string file);
    void SetClip(
        int x, int y,
        int w, int h
    );
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    // TODO: either change how this works or make the fact that this mutates the associated GameObject more explicit
    void SetScale(Vec2 scale);
    Vec2 GetScale();

    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(double frameTime);

    void Update(double dt);
    void Render();
    void Render(double x, double y);
    bool Is(std::string type);

private:
    std::shared_ptr<SDL_Texture> texture;
    int width, height;
    SDL_Rect clipRect;
    Vec2 scale;
    int frameCount;
    int currentFrame;
    double timeElapsed;
    double frameTime;
    // TODO: move this from Sprite (doesn't make sense for this behavior to be here)
    double secondsToSelfDestruct;
    Timer selfDestructCounter;
};

#endif
