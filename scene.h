#ifndef SCENE_H
#define SCENE_H

#define MAX_ACTIVE_SCENES 256

// callback functions
typedef void (*scene_update_cb)(f32 dt);
typedef void (*scene_render_cb)(void);

typedef struct {
	// array of objects etc.
	scene_update_cb update;
	scene_render_cb render;
}scene_t;

extern i32 cur_scene_idx; // negative when no current scene
extern u32 active_scene_count;
extern scene_t* active_scenes[MAX_ACTIVE_SCENES];

scene_t* scene_create(void);
void scene_update(scene_t*, f32 dt);
void scene_render(scene_t*);
void scene_select_idx(u32 idx);

#endif