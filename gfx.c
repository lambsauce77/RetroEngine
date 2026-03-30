#include "gfx.h"
#include "renderer.h"

void gfx_draw_pixel(u32 x, u32 y, u32 clr) {
	renderer_set_pixel(x, y, clr);
}

// TODO: parameters to floats ( sub-pixel movement? )
void gfx_draw_rect(u32 x, u32 y, u32 w, u32 h, u32 clr) {
	for (u32 rect_y = 0; rect_y < h; rect_y++) {
		u32 screen_y = y + rect_y;

		for (u32 rect_x = 0; rect_x < w; rect_x++) {
			u32 screen_x = x + rect_x;

			renderer_set_pixel(screen_x, screen_y, clr);
		}
	}
}