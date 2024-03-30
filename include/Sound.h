#ifndef SOUND_H_
#define SOUND_H_
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "Component.h"

class Sound : public Component {
public:
    Sound(GameObject& associated);
    Sound(GameObject& associated, const char* file);
    ~Sound();
    
    void Play(int times = 1);
    void Stop();
    void Open(const char* file);
    bool IsOpen();
    bool IsPlaying();

    void Update(double dt);
    void Render();
    bool Is(std::string type);
private:
    Mix_Chunk* chunk;
    int channel;
};

#endif
