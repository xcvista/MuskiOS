
#ifndef _MUSKIOS_MEMORY_H_
#define _MUSKIOS_MEMORY_H_

#include <stddef.h>
#include <stdint.h>
#include <objc/runtime.h>

typedef enum _mem_flags
{
	mem_read = 1 << 1;
	mem_write = 1 << 2;
	mem_exec = 1 << 3;
	mem_nonmove = 1 << 4;
	
} mem_flags;

typedef struct _mem_mapitem
{
	Class isa;
	NSUInteger _retainCount;
	void *base;
	uint32_t flags;
} mem_mapitem;

typedef struct _mem_mallocpage
{
	Class isa;
	NSUInteger _retainCount;
	uint16_t size;
	uint16_t flags;
} mem_mallocpage;

#endif
