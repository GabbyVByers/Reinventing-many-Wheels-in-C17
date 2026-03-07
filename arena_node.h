
#ifndef ARENA_NODE_H
#define ARENA_NODE_H

#include <stdlib.h>
#include "types.h"

#define KILO_BYTE (((u64)1) << 10)
#define MEGA_BYTE (((u64)1) << 20)
#define GIGA_BYTE (((u64)1) << 30)
#define KILO_BYTES(n) (((u64)n) << 10)
#define MEGA_BYTES(n) (((u64)n) << 20)
#define GIGA_BYTES(n) (((u64)n) << 30)
#define MAX_ALIGN ((size_t)sizeof(void*))

typedef void ArenaNode;
ArenaNode* arena_node_create(u64 capacity);
void*      arena_node_alloc(ArenaNode* arena_alias, u64 bytes);
void       arena_node_clear(ArenaNode* arena_alias);
void       arena_node_destroy(ArenaNode* arena_alias);

#endif

