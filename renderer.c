#include "renderer.h"

SDL_Renderer* renderer = NULL;

SDL_Texture* render_tex = NULL;

u32 render_w = 0;
u32 pixel_count = 0;
u32* front_buffer = NULL;
u32* back_buffer = NULL;

u8 renderer_init(SDL_Renderer* r, u32 w, u32 h) {
	if (!r) {
		return 0;
	}

	render_tex = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, w, h);

	if (!render_tex) {
		return 1;
	}

	render_w = w;
	pixel_count = w * h;

	// alloc buffers

	renderer = r;
	return 1;
}

void renderer_update() {
	if (!renderer) {
		return;
	}

	SDL_RenderClear(renderer);


	SDL_RenderCopy(renderer, render_tex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void renderer_set_pixel(u32 x, u32 y, u32 clr) {
	u32 idx = x * render_w + y;

	if (!back_buffer || idx >= pixel_count) {
		return;
	}
	back_buffer[idx] = clr;
}

void renderer_quit() {
	if (render_tex) {
		SDL_DestroyTexture(render_tex);
	}
}