#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Game.h"
#include <SDL2/SDL.h>

static const int width = 800;
static const int height = 600;

int main(int argc, char **argv) {
    srand(time(NULL));

    Game::GetInstance().Run();

    return 0;
}