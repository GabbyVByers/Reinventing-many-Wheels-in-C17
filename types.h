
#ifndef RUSTY_TYPES_H
#define RUSTY_TYPES_H

#include <stdlib.h>
#include <stdint.h>
#include <float.h>

#define i8_MIN INT8_MIN
#define i16_MIN INT16_MIN
#define i32_MIN INT32_MIN
#define i64_MIN INT64_MIN
#define i8_MAX INT8_MAX
#define i16_MAX INT16_MAX
#define i32_MAX INT32_MAX
#define i64_MAX INT64_MAX
#define u8_MAX UINT8_MAX
#define u16_MAX UINT16_MAX
#define u32_MAX UINT32_MAX
#define u64_MAX UINT64_MAX
#define f32_MIN FLT_MIN
#define f32_MAX FLT_MAX
#define f64_MIN DBL_MIN
#define f64_MAX DBL_MAX

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef _Bool bool;
typedef float f32;
typedef double f64;

static inline void TEST_ASSERT_TYPE_SIZE(void) {
	if (sizeof(i8) != 1) exit(1);
	if (sizeof(i16) != 2) exit(1);
	if (sizeof(i32) != 4) exit(1);
	if (sizeof(i64) != 8) exit(1);
	if (sizeof(u8) != 1) exit(1);
	if (sizeof(u16) != 2) exit(1);
	if (sizeof(u32) != 4) exit(1);
	if (sizeof(u64) != 8) exit(1);
	if (sizeof(bool) != 1) exit(1);
	if (sizeof(f32) != 4) exit(1);
	if (sizeof(f64) != 8) exit(1);
	if (sizeof(size_t) != 8) exit(1);
}

#endif

