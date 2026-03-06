
#include "arena.h"

typedef struct {
	u64 capacity_per_node;
	Array* arena_nodes;
} ArenaImpl;

Arena* arena_create(u64 capacity_per_node) {
	Arena* arena_alias = malloc(sizeof(ArenaImpl));
	if (arena_alias == NULL)
		exit(1);
	if (capacity_per_node == 0)
		exit(1);
	if (capacity_per_node % MAX_ALIGN != 0)
		exit(1);
	
	Array* arena_nodes = array_create(sizeof(ArenaNode*));
	ArenaNode* node = arena_node_create(capacity_per_node);
	array_push_back(arena_nodes, &node);
	
	ArenaImpl* arena = (ArenaImpl*)arena_alias;
	(*arena) = (ArenaImpl){
		.capacity_per_node = capacity_per_node,
		.arena_nodes = arena_nodes
	};

	return arena_alias;
}

void* arena_alloc(Arena* arena_alias, u64 bytes) {
	ArenaImpl* arena = (ArenaImpl*)arena_alias;
	if (arena == NULL)
		exit(1);
	if (arena->arena_nodes == NULL)
		exit(1);

	if (bytes >= arena->capacity_per_node) {
		bytes = ((bytes + MAX_ALIGN - 1) / MAX_ALIGN) * MAX_ALIGN;
		Array* nodes = arena->arena_nodes;
		ArenaNode* node = arena_node_create(bytes);
		array_push_back(nodes, &node);
		void* ptr = arena_node_alloc(node, bytes);
		if (ptr == NULL)
			exit(1);
		return ptr;
	}

	void* ptr = NULL;
	Array* nodes = arena->arena_nodes;
	u64 num_nodes = array_size(nodes);
	for (u64 i = 0; i < num_nodes; i++) {
		ArenaNode* node = *(ArenaNode**)array_index(nodes, i);
		ptr = arena_node_alloc(node, bytes);
		if (ptr != NULL)
			return ptr;
	}

	ArenaNode* node = arena_node_create(arena->capacity_per_node);
	ptr = arena_node_alloc(node, bytes);
	if (ptr == NULL)
		exit(1);

	array_push_back(nodes, &node);
	return ptr;
}

void arena_clear(Arena* arena_alias) {
	ArenaImpl* arena = (ArenaImpl*)arena_alias;
	if (arena == NULL)
		exit(1);
	if (arena->arena_nodes == NULL)
		exit(1);

	Array* nodes = arena->arena_nodes;
	u64 num_nodes = array_size(nodes);
	for (u64 i = 0; i < num_nodes; i++) {
		ArenaNode* node = *(ArenaNode**)array_index(nodes, i);
		arena_node_clear(node);
	}
}

void arena_destroy(Arena* arena_alias) {
	ArenaImpl* arena = (ArenaImpl*)arena_alias;
	if (arena == NULL)
		exit(1);
	if (arena->arena_nodes == NULL)
		exit(1);

	Array* nodes = arena->arena_nodes;
	u64 num_nodes = array_size(nodes);
	for (u64 i = 0; i < num_nodes; i++) {
		ArenaNode* node = *(ArenaNode**)array_index(nodes, i);
		arena_node_destroy(node);
	}

	array_destroy(nodes);
	free(arena_alias);
}

