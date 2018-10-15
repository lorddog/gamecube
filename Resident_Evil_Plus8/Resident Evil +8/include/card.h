//Memory Card lib

#ifndef _CARD_H_
#define _CARD_H_

#include "types.h"
#include "gc_exi.h"


u8 CardReadRaw(u8 slot, u8 *buffer, u16 sector, u8 page, u8 offset, u8 size);
u8 CardRead(u8 slot, u8 *buffer, u32 addr, u32 size);
u8 CardGetStatus(u8 slot);
u16 CardGetID(u8 slot);
u16 CardConnected(u8 slot);

#endif //_CARD_H_
