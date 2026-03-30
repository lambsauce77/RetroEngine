#include "allocator.h"

#define ALLOC_START (sizeof(alloc_t))
#define ALLOC_ALIGN (sizeof(void*))

alloc_t* alloc_create(u64 cap) {
	alloc_t* a = malloc(cap);
	ASSERT(NULL, a);

	a->capacity = cap;
	a->position = ALLOC_START;

	return a;
}

void* alloc_push(alloc_t* a, u64 size){
	if (!a) {
		printf("Allocation error! Allocator is null\n");
		return NULL;
	}

	u64 aligned_pos = ALIGN_UP_POW2(a->position, ALLOC_ALIGN);
	u64 new_pos = aligned_pos + size;

	if (new_pos > a->capacity) {
		// alloc failure
		printf("Allocation error! Memory out of range\n");
		return NULL;
	}

	a->position = new_pos;

	u8* out = (u8*)a + aligned_pos;

	// maybe opt.
	memset(out, 0, size);

	printf("Allocated %llu bytes\n", size);

	return out;
}

void alloc_pop(alloc_t* a, u64 size) {
	ASSERT(VOID, a);

	size = MIN(size, a->position - ALLOC_START);
	a->position -= size;
}

void alloc_pop_to(alloc_t* a, u64 pos){
	ASSERT(VOID, a);

	u64 size = pos < a->position ? a->position - pos : 0;
	alloc_pop(a, size);
}

void alloc_clear(alloc_t* a) {
	ASSERT(VOID, a);

	alloc_pop_to(a, ALLOC_START);
}

void alloc_destroy(alloc_t* a){
	ASSERT(VOID, a);

	printf("Freed %llu bytes\n", (a->position - ALLOC_START));

	free(a);
}