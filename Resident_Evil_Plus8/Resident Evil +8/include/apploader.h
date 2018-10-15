#ifndef _APPLOADER_H_
#define _APPLOADER_H_

#include "types.h"
#include "dvd.h"
#include "memory.h"
#include "debug.h"
#include "bba.h"

#define BI2_SIMMEMSIZE_OFFSET	0x00000444

typedef u32 (*taplFunc1)(u32, u32, u32);
typedef u32 (*taplFunc2)(u32, u32);
typedef u32 (*taplFunc3)(u32);
typedef u32 (*taplFunc4)(void);


taplFunc4 RunApploader(u32 freemem);

#endif //_APPLOADER_H_
