#ifndef _FST_H_
#define _FST_H_

#include "types.h"
#include "dvd.h"
#include "dvdsim.h"
#include "heap.h"
#include "memory.h"


u8 FSTInit(u32 freemem);
u8 FSTsimInit(u32 freemem);
u32 *FSTPtr();
char *FSTStr();
u32 FSTSize();
u32 FSTCount();
u8 *FSTFileString(u32 index);
u32 FSTFileIsDir(u32 index);
u32 FSTFileSize(u32 index);
u32 FSTFileOffset(u32 index);
u32 FSTFileIndex(char *filename);

#endif
