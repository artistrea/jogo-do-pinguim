#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include "Resources.h"
#include "Game.h"
#include "ThrowError.h"
#define MAX_PATH_LEN 300


// coloque aqui o basePath necessário no seu OS:
std::string Resources::basePath("./assets/");

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

const char* Resources::GetFullPath(std::string file) {
    const int bufferLengthNeedsToBe = file.size() + basePath.size() + 1;

    if (bufferLengthNeedsToBe >= MAX_PATH_LEN) {
        ThrowError::Error("Resources::GetFullPath needs more buffer space for file path.");
    }
    char* path = new char[MAX_PATH_LEN];

    snprintf(path, 8 * MAX_PATH_LEN,
        "%s%s", basePath.c_str(), file.c_str()
    );

    return path;
}

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
    if (imageTable.find(file) == imageTable.end()) {
        imageTable[file] = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(
            Game::GetInstance().GetRenderer(),
            GetFullPath(file)
        ), [](SDL_Texture* texture){ SDL_DestroyTexture(texture); });
    }

    return imageTable.find(file)->second;
}

void Resources::ClearImages() {
    for (auto itr = imageTable.begin(); itr != imageTable.end();) {
        if (itr->second.use_count() == 1) {
            itr = imageTable.erase(itr);
        } else {
            itr++;
        }
    }

    imageTable.clear();
}


Mix_Music* Resources::GetMusic(std::string file) {
    if (musicTable.find(file) == musicTable.end()) {
        musicTable[file] = Mix_LoadMUS(
            GetFullPath(file)
        );
    }

    return musicTable.find(file)->second;
}

void Resources::ClearMusics() {
    Mix_HaltMusic();
    for (auto itr = musicTable.begin(); itr != musicTable.end();) {
        Mix_FreeMusic(itr->second);
        itr = musicTable.erase(itr);
    }

    musicTable.clear();
}


Mix_Chunk* Resources::GetSound(std::string file) {
    if (soundTable.find(file) == soundTable.end()) {
        soundTable[file] = Mix_LoadWAV(
            GetFullPath(file)
        );
    }

    return soundTable.find(file)->second;
}

void Resources::ClearSounds() {
    Mix_HaltChannel(-1);
    for (auto itr = soundTable.begin(); itr != soundTable.end();) {
        Mix_FreeChunk(itr->second);
        itr = soundTable.erase(itr);
    }

    soundTable.clear();
}

