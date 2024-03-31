#ifndef SOUND_H_
#define SOUND_H_
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "Component.h"
#include <string>

class Sound : public Component {
public:
    Sound(GameObject& associated);
    Sound(GameObject& associated, std::string file);
    ~Sound();
    
    void Play(int times = 1);
    void Stop();
    void Open(std::string file);
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
