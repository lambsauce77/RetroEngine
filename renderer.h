#ifndef RENDERER_H
#define RENDERER_H

#include "include.h"

u8 renderer_init(SDL_Renderer*, u32 w, u32 h);
void renderer_update(void);
void renderer_set_pixel(u32 x, u32 y, u32 clr);
void renderer_quit(void);

#endif