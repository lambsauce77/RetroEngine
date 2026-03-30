#include "include.h"
#include "scene.h"
#include "allocator.h"
#include "gfx.h"

i32 cur_scene_idx = -1;
u32 active_scene_count = 0;
scene_t* active_scenes[MAX_ACTIVE_SCENES];

scene_t* scene_create(void) {
	scene_t* s = (scene_t*)alloc_push(global_allocator, sizeof(scene_t));
	ASSERT(NULL, s && (active_scene_count < MAX_ACTIVE_SCENES));

	active_scenes[active_scene_count++] = s;
	return s;
}

void scene_update(scene_t* s, f32 dt){
	ASSERT(VOID, s && s->update);

	s->update(dt);
}

void scene_render(scene_t* s){
	ASSERT(VOID, s && s->render);

	s->render();
}

void scene_select_idx(u32 idx) {
	cur_scene_idx = idx < active_scene_count ? idx : -1;
}