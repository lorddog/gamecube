#ifndef _ROM_H_
#define _ROM_H_

#include "types.h"
#include "gc_exi.h"


void GC_ROM_SetRTC(u32 aval);
u32 GC_ROM_GetRTC();
void GC_ROM_ReadSRAM(u8 *abuf);
void GC_ROM_WriteSRAM(u8 *abuf);
void GC_ROM_SRAMCheckSum(u16 *abuf);
void GC_ROM_GetDateTime(u32 value, u32 *year, u32 *month, u32 *cday, u32 *days, u32 *hours, u32 *minutes, u32 *seconds);

#endif //_ROM_H_
