#ifndef SPRITE_H_
#define SPRITE_H_
#include <iostream>
#include <SDL2/SDL.h>

class Sprite {
public:
    Sprite();
    Sprite(const char* file);
    ~Sprite();
    void Open(const char* file);
    void SetClip(
        int x, int y,
        int w, int h
    );
    void Render(int x, int y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    
private:
    SDL_Texture* texture;
    int width, height;
    SDL_Rect clipRect;
};

#endif
