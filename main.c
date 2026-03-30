#include "include.h"
#include "renderer.h"
#include "allocator.h"
#include "scene.h"
#include "gfx.h"

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

u32 rect_x = 0;

static void example_update(f32 dt) {
	rect_x += 1;
	rect_x %= WINDOW_W;
}

static void example_render(void) {
	gfx_draw_rect(rect_x, 50, 20, 20, 0xFFFFFFFF);
}

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

	if (!renderer_init(renderer, WINDOW_W/4, WINDOW_H/4)) {
		QUIT(1, renderer, window);
	}

	scene_t* example_scene = scene_create();
	
	if (!example_scene) {
		QUIT(1, renderer, window);
	}

	example_scene->update = example_update;
	example_scene->render = example_render;

	scene_select_idx(0);

	u64 last_time = SDL_GetTicks64();

	SDL_Event event;
	
	u8 running = 1;

	while (running) {
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT) {
				running = 0;
			}
		}

		u64 cur_time = SDL_GetTicks64();
		f32 dt = (cur_time - last_time) / 1000.0f;
		last_time = cur_time;

		// TODO: move this to some other file later
		if (cur_scene_idx >= 0 && cur_scene_idx < active_scene_count) {
			scene_update(active_scenes[cur_scene_idx], dt);
		}

		renderer_update();
	}

	renderer_quit();
	QUIT(0, renderer, window);
}