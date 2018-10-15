#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "types.h"

#define MEMORYLOW	0x80000000
#define MEMORYHIGH	0x81800000


void InvalidateDC(u32 dst, u32 len);
void InvalidateIC(u32 dst, u32 len);
void FlushDC(u32 dst, u32 len);

int MemoryEqual32(u32 *dst,u32 *src,u32 count);
int MemoryEqual8(u8 *dst,u8 *src,u32 count);
int __MemoryEqualIgnore32(u32 *dst,u32 *src,u32 count);
void MemoryCopy32(u32 *dst,u32 *src,u32 count);
void MemoryFill32(u32 *dst,u32 src,u32 count);
void MemoryCopy16(u16 *dst,u16 *src,u32 count);
void MemoryFill16(u16 *dst,u16 src,u32 count);
void MemoryCopy8(u8 *dst,u8 *src,u32 count);
void MemoryFill8(u8 *dst,u8 src,u32 count);

#endif //_MEMORY_H_
