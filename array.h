
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <string.h>
#include "types.h"

typedef void Array;
Array* array_create(u64 stride);
void   array_push_back(Array* array_alias, void* element);
u64    array_size(Array* array_alias);
void*  array_index(Array* array_alias, u64 index);
void   array_remove(Array* array_alias, u64 index);
void   array_remove_unordered(Array* array_alias, u64 index);
void   array_destroy(Array* array_alias);

#endif

