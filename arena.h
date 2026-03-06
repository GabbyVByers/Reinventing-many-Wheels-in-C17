
#ifndef ARENA_H
#define ARENA_H

#include "arena_node.h"
#include "array.h"
#include "types.h"

typedef void Arena;
Arena* arena_create(u64 capacity_per_node);
void*  arena_alloc(Arena* arena_alias, u64 bytes);
void   arena_clear(Arena* arena_alias);
void   arena_destroy(Arena* arena_alias);

#endif

