
#include "arena_node.h"

typedef struct {
	void* buffer;
	u64   offset;
	u64   capacity;
} ArenaNodeImpl;

ArenaNode* arena_node_create(u64 capacity) {
	ArenaNode* arena_node_alias = malloc(sizeof(ArenaNodeImpl));
	if (arena_node_alias == NULL)
		exit(1);
	if (capacity == 0)
		exit(1);
	if (capacity % MAX_ALIGN != 0)
		exit(1);

	ArenaNodeImpl* arena_node = (ArenaNodeImpl*)arena_node_alias;
	(*arena_node) = (ArenaNodeImpl){
		.buffer = malloc(capacity),
		.offset = 0,
		.capacity = capacity
	};
	if (arena_node->buffer == NULL)
		exit(1);

	return arena_node_alias;
}

void* arena_node_alloc(ArenaNode* arena_node_alias, u64 bytes) {
	ArenaNodeImpl* arena_node = (ArenaNodeImpl*)arena_node_alias;
	if (arena_node == NULL)
		exit(1);
	if (bytes == 0)
		exit(1);

	bytes = ((((u64)bytes + (MAX_ALIGN - 1)) / MAX_ALIGN) * MAX_ALIGN);
	if (bytes > arena_node->capacity - arena_node->offset)
		return NULL; // RETS NULL INSTEAD OF CRASH

	void* ptr = (u8*)arena_node->buffer + arena_node->offset;
	arena_node->offset += bytes;
	return ptr;
}

void arena_node_clear(ArenaNode* arena_node_alias) {
	ArenaNodeImpl* arena_node = (ArenaNodeImpl*)arena_node_alias;
	if (arena_node == NULL)
		exit(1);

	arena_node->offset = 0;
}

void arena_node_destroy(ArenaNode* arena_node_alias) {
	ArenaNodeImpl* arena_node = (ArenaNodeImpl*)arena_node_alias;
	if (arena_node == NULL)
		exit(1);

	free(arena_node->buffer);
	free(arena_node_alias);
}

