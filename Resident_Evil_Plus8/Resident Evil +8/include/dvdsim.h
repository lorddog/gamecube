// DVD Simulation routines

#ifndef _DVDSIM_H_
#define _DVDSIM_H_

#include "types.h"
#include "bba.h"
#include "memory.h"


//u8 DVDsimInit(u8 bbamode, ip4 srcaddr, u16 srcport, ip4 dstaddr, u16 dstport);
int DVDsimReadRaw(void *dst, u32 src, u32 len);

#endif //_DVDSIM_H_
