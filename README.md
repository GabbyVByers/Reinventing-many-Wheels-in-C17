
# Simple C Utilities Library

## Rusty Types
## Arenas
## Arrays
## Strings 

```c
typedef void Arena;
Arena* arena_create(u64 capacity_per_node);
void*  arena_alloc(Arena* arena_alias, u64 bytes);
void   arena_clear(Arena* arena_alias);
void   arena_destroy(Arena* arena_alias);
```

```c
typedef void Array;
Array* array_create(u64 stride);
void   array_push_back(Array* array_alias, void* element);
u64    array_size(Array* array_alias);
void*  array_index(Array* array_alias, u64 index);
void   array_remove(Array* array_alias, u64 index);
void   array_remove_unordered(Array* array_alias, u64 index);
void   array_destroy(Array* array_alias);
```

