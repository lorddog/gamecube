#ifndef _ARENA_H_
#define _ARENA_H_

#include "types.h"


void ArenaInit();
void ArenaLoSet(u32 ptr);
u32 ArenaLoGet();
void ArenaHiSet(u32 ptr);
u32 ArenaHiGet();
u32 ArenaShrink(u32 size);


#endif //_AREAN_H_
