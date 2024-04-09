#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>
#include <SDL2/SDL.h>

#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN

#define W_KEY               SDLK_w
#define A_KEY               SDLK_a
#define S_KEY               SDLK_s
#define D_KEY               SDLK_d

#define SPACE_KEY           SDLK_SPACE
#define ESCAPE_KEY          SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT

class InputManager {
public:
    void Update();

    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);
    

    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);
    
    int GetMouseY();
    int GetMouseX();
    
    bool QuitRequested();
    
    static InputManager& GetInstance();

private:
    InputManager();
    ~InputManager();

    bool mouseState[6];
    int mouseUpdate[6];
    
    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;

    bool quitRequested;
    int updateCounter,
        mouseX, mouseY;

    static InputManager* instance;
};

#endif