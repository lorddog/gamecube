#ifndef _HEAP_H_
#define _HEAP_H_

#include "types.h"


#define HEAP_COUNT	1024
#define HEAP_BASE	0x80700000
#define HEAP_SIZE	7*1024*1024

typedef struct _HEAP_BLOCK
{
	u32 base;
	u32 size;
	u32 status;
	u32 padding;
} HEAP_BLOCK;

void __HeapInit(u32 *ptr,u32 size);
void HeapInit();
HEAP_BLOCK *__HeapNew();
void *HeapAllocate(u32 size);
void HeapFree(void *ptr);

#endif //_HEAP_H_
