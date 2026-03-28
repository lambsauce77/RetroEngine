#include "gfx.h"
#include "renderer.h"

void gfx_set_pixel(u32 x, u32 y, u32 clr) {
	renderer_set_pixel(x, y, clr);
}