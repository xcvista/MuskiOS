
#ifndef _MUSKIOS_MEMORY_H_
#define _MUSKIOS_MEMORY_H_

#include <stddef.h>
#include <stdint.h>

typedef enum _mem_flags
{
	mem_read = 1 << 1;
	mem_write = 1 << 2;
	mem_exec = 1 << 3;
	mem_nonmove = 1 << 4;
	
} mem_flags;

typedef struct _mem_mapitem
{
	void *base;
	size_t length;
	mem_flags flags;
} mem_mapitem;

#endif
