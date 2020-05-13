#include "Constants.h"
#if WEBASSEMBLY
    #include <emscripten.h>
#endif
#include <SDL2\SDL.h>
#include <stdlib.h>
#include <stdio.h>

struct Vec
{
    int x;
    int y;
};

struct Vec velocity;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
SDL_Rect rect = { 0,0 , 50, 50 };

void update_jskey()
{
    rect.x += velocity.x;
    rect.y += velocity.y;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

int main()
{
    printf("main has run\n");

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

#if WEB_ASSEMBLY
    emscripten_set_main_loop(update_jskey, 0, 0);
#endif
}

void press_up()
{
    printf("PRESS UP\n");
    velocity.y = -1;
}

void press_down()
{
    printf("PRESS DOWN\n");
    velocity.y = 1;
}

void press_right()
{
    printf("PRESS RIGHT\n");
    velocity.x = 1;
}

void press_left()
{
    printf("PRESS LEFT\n");
    velocity.x = -1;
}

void release_up()
{
    printf("RELEASE UP\n");
    velocity.y = 0;
}

void release_down()
{
    printf("RELEASE DOWN\n");
    velocity.y = 0;
}

void release_right()
{
    printf("RELEASE RIGHT\n");
    velocity.x = 0;
}
void release_left()
{
    printf("RELEASE LEFT\n");
    velocity.x = 0;
}