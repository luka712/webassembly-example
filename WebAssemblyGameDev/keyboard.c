#include "Constants.h"

#include <SDL2/SDL.h>
#if WEBASSEMBLY
	#include <emscripten.h>
#endif
#include <stdio.h>
#include <stdbool.h>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;
SDL_Rect drawRect = { 0,0 , 100, 100 };

bool left_key_press = false;
bool right_key_press = false;
bool up_key_press = false;
bool down_key_press = false;

bool is_running = true;

void key_press()
{
	switch (event.key.keysym.sym)
	{
	case SDLK_LEFT:
		if (!left_key_press) {
			printf("left arrow key press\n");
		}
		left_key_press = true;
		break;
	case SDLK_RIGHT:
		if (!right_key_press) {
			printf("right arrow key press\n");
		}
		right_key_press = true;
		break;
	case SDLK_UP:
		if (!up_key_press) {
			printf("up arrow key press\n");
		}
		up_key_press = true;
		break;
	case SDLK_DOWN:
		if (!down_key_press) {
			printf("down arrow key press\n");
		}
		down_key_press = true;
		break;
	default:
		printf("unknown key press\n");
		break;
	}
}

void key_release()
{
	switch (event.key.keysym.sym)
	{
	case SDLK_LEFT:
		if (left_key_press) {
			printf("left arrow key release\n");
		}
		left_key_press = false;
		break;
	case SDLK_RIGHT:
		if (right_key_press) {
			printf("right arrow key release\n");
		}
		right_key_press = false;
		break;
	case SDLK_UP:
		if (up_key_press) {
			printf("up arrow key release\n");
		}
		up_key_press = false;
		break;
	case SDLK_DOWN:
		if (down_key_press) {
			printf("down arrow key release\n");
		}
		down_key_press = false;
		break;
	}
}

void input_loop()
{
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			key_press();
		}
		else if (event.type)
		{
			key_release();
		}
	}
}

void draw()
{
	if (left_key_press)
	{
		drawRect.x--;
	}
	else if (right_key_press)
	{
		drawRect.x++;
	}

	if (up_key_press)
	{
		drawRect.y--;
	}
	else if (down_key_press)
	{
		drawRect.y++;
	}

	SDL_SetRenderDrawColor(renderer, 200, 0, 200, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
	SDL_RenderFillRect(renderer, &drawRect);
	SDL_RenderPresent(renderer);
}

void update()
{
	input_loop();
	draw();
}

int main_()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

#if WEBASSEMBLY
	emscripten_set_main_loop(update, 0, 0);
#else
	while (true)
	{
		update();
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			break;
		}

		SDL_Delay(1000 / 60);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
#endif

	return 0;
}
