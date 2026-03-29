#include "renderer.h"
#include "allocator.h"

alloc_t* buffer_allocator = NULL;

SDL_Renderer* renderer = NULL;

SDL_Texture* render_tex = NULL;

u32 render_w = 0;
u32 render_h = 0;
u32* front_buffer = NULL;
u32* back_buffer = NULL;

#define PIXEL_COUNT (render_w * render_h)
#define PITCH (render_w * sizeof(u32))
#define BUFFER_SIZE (PIXEL_COUNT * sizeof(u32))

#define ALLOC_SIZE (BUFFER_SIZE*3)

u8 renderer_init(SDL_Renderer* r, u32 w, u32 h) {
	ASSERT(0, r);

	render_w = w;
	render_h = h;

	buffer_allocator = alloc_create(ALLOC_SIZE);
	ASSERT(0, buffer_allocator);

	render_tex = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, w, h);
	if (!render_tex) {
		alloc_destroy(buffer_allocator);
		return 0;
	}

	front_buffer = (u32*)alloc_push(buffer_allocator, BUFFER_SIZE);
	back_buffer = (u32*)alloc_push(buffer_allocator, BUFFER_SIZE);

	ASSERT(0, front_buffer && back_buffer);

	renderer = r;
	return 1;
}

void renderer_update() {
	ASSERT(VOID, renderer && render_tex);
	
	SDL_RenderClear(renderer);

	memset(back_buffer, 0, BUFFER_SIZE);

	// render logic
	//

	memcpy(front_buffer, back_buffer, BUFFER_SIZE);

	u32* pixels = NULL;
	int pitch = 0;
	if (SDL_LockTexture(render_tex, NULL, &pixels, &pitch) == 0) {
		// TODO: pitch unused, fix later
		memcpy(pixels, front_buffer, BUFFER_SIZE);
		SDL_UnlockTexture(render_tex);
	}

	SDL_RenderCopy(renderer, render_tex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void renderer_set_pixel(u32 x, u32 y, u32 clr) {
	u32 idx = y * render_w + x;

	ASSERT(VOID, back_buffer && idx < PIXEL_COUNT);

	back_buffer[idx] = clr;
}

void renderer_quit() {
	if (render_tex) {
		SDL_DestroyTexture(render_tex);
	}
	alloc_destroy(buffer_allocator);
}