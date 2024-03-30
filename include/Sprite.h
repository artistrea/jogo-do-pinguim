#ifndef SPRITE_H_
#define SPRITE_H_
#include <iostream>
#include <SDL2/SDL.h>
#include "Component.h"

class Sprite : public Component {
public:
    Sprite(GameObject& associated);
    Sprite(GameObject& associated, const char* file);
    ~Sprite();
    void Open(const char* file);
    void SetClip(
        int x, int y,
        int w, int h
    );
    int GetWidth();
    int GetHeight();
    bool IsOpen();

    void Update(double dt);
    void Render();
    bool Is(std::string type);

    
private:
    SDL_Texture* texture;
    int width, height;
    SDL_Rect clipRect;
};

#endif
