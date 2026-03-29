#include "include.h"
#include "renderer.h"
#include "allocator.h"

#define WINDOW_W 1280
#define WINDOW_H 720

#define GLOBAL_MEMORY (MiB(100))

#define QUIT(value, renderer, window) \
do{ \
	if(renderer){SDL_DestroyRenderer(renderer);} \
	if(window){SDL_DestroyWindow(window);} \
	SDL_Quit(); \
	alloc_destroy(global_allocator); \
	return(value); \
}while(0)

int main(void) {

	global_allocator = alloc_create(GLOBAL_MEMORY);

	if (!global_allocator) {
		QUIT(1, NULL, NULL);
	}

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		QUIT(1, NULL, NULL);
	}

	SDL_Window* window = SDL_CreateWindow(
		"Retro Engine", 
		 SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 
		WINDOW_W,
		WINDOW_H,
		0);

	if (!window) {
		QUIT(1, NULL, NULL);
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, SDL_RENDERER_ACCELERATED, 0);

	if (!renderer) {
		QUIT(1, NULL, window);
	}

	if (!renderer_init(renderer, WINDOW_W, WINDOW_H)) {
		QUIT(1, renderer, window);
	}

	SDL_Event event;
	
	u8 running = 1;

	while (running) {
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT) {
				running = 0;
			}
		}

		renderer_update();
	}

	renderer_quit();
	QUIT(0, renderer, window);
}