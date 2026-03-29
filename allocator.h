#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "include.h"

typedef struct {
	u64 capacity;
	u64 position;
}alloc_t;

alloc_t* alloc_create(u64 cap);
void* alloc_push(alloc_t* a, u64 size);
void alloc_pop(alloc_t* a, u64 size);
void alloc_pop_to(alloc_t* a, u64 pos);
void alloc_clear(alloc_t*);
void alloc_destroy(alloc_t*);

alloc_t* global_allocator;

#endif