
#include "array.h"

typedef struct {
	void* buffer;
	u64   size;
	u64   capacity;
	u64   stride;
} ArrayImpl;

Array* array_create(u64 stride) {
	Array* array_alias = malloc(sizeof(ArrayImpl));
	if (array_alias == NULL)
		exit(1);
	if (stride == 0)
		exit(1);

	ArrayImpl* array = (ArrayImpl*)array_alias;
	(*array) = (ArrayImpl){
		.buffer = NULL,
		.size = 0,
		.capacity = 0,
		.stride = stride
	};
	return array_alias;
}

void array_push_back(Array* array_alias, void* element) {
	ArrayImpl* array = (ArrayImpl*)array_alias;
	if (array == NULL)
		exit(1);
	if (element == NULL)
		exit(1);
	if (array->size > array->capacity)
		exit(1);
	if (array->stride == 0)
		exit(1);

	if (array->buffer == NULL) {
		if (array->capacity != 0)
			exit(1);
		if (array->size != 0)
			exit(1);

		array->capacity = 4;
		array->buffer = malloc(array->capacity * array->stride);
		if (array->buffer == NULL)
			exit(1);
	}

	if (array->size >= array->capacity) {
		if (array->size != array->capacity)
			exit(1);
		
		u64 new_capacity = array->capacity * 2;
		void* new_buffer = realloc(array->buffer, new_capacity * array->stride);
		array->capacity = new_capacity;
		array->buffer = new_buffer;
		if (new_buffer == NULL)
			exit(1);
	}

	void* dst = (u8*)array->buffer + (array->size * array->stride);
	void* src = element;
	memcpy(dst, src, array->stride);
	array->size++;
}

u64 array_size(Array* array_alias) {
	ArrayImpl* array = (ArrayImpl*)array_alias;
	if (array == NULL)
		exit(1);

	return array->size;
}

void* array_index(Array* array_alias, u64 index) {
	ArrayImpl* array = (ArrayImpl*)array_alias;
	if (array == NULL)
		exit(1);
	if (array->buffer == NULL)
		exit(1);
	if (index >= array->size)
		exit(1);

	return (u8*)array->buffer + (index * array->stride);
}

void array_remove(Array* array_alias, u64 index) {
	ArrayImpl* array = (ArrayImpl*)array_alias;
	if (array == NULL)
		exit(1);
	if (array->buffer == NULL)
		exit(1);
	if (index >= array->size)
		exit(1);

	if (index == array->size - 1) {
		array->size--;
		return;
	}

	void* dst = (u8*)array->buffer + (index * array->stride);
	void* src = (u8*)array->buffer + ((index + 1) * array->stride);
	u64 bytes = (array->size - index - 1) * array->stride;
	memmove(dst, src, bytes);
	array->size--;
}

void array_remove_unordered(Array* array_alias, u64 index) {
	ArrayImpl* array = (ArrayImpl*)array_alias;
	if (array == NULL)
		exit(1);
	if (array->buffer == NULL)
		exit(1);
	if (index >= array->size)
		exit(1);

	if (index == array->size - 1) {
		array->size--;
		return;
	}

	void* dst = (u8*)array->buffer + (index * array->stride);
	void* src = (u8*)array->buffer + ((array->size - 1) * array->stride);
	memcpy(dst, src, array->stride);
	array->size--;
}

void array_destroy(Array* array_alias) {
	ArrayImpl* array = (ArrayImpl*)array_alias;
	if (array == NULL)
		exit(1);

	free(array->buffer);
	free(array_alias);
}

