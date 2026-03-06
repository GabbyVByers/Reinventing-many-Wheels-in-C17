
#include "types.h"
#include "arena.h"

int main(void) {
	Arena* my_arena = arena_create(MEGA_BYTE);
	arena_destroy(my_arena);
	return 0;
}

