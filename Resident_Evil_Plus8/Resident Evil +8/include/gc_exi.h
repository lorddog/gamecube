#ifndef _EXI_H_
#define _EXI_H_

#include "types.h"


#define EXI_BASE	0xCC006800
#define EXI_STATUS0	*(vu32*)0xCC006800
#define EXI_DMABUF0	*(vu32*)0xCC006804
#define EXI_DMALEN0	*(vu32*)0xCC006808
#define EXI_DMACNT0	*(vu32*)0xCC00680C
#define EXI_IMMDAT0	*(vu32*)0xCC006810
#define EXI_STATUS1	*(vu32*)0xCC006814
#define EXI_DMABUF1	*(vu32*)0xCC006818
#define EXI_DMALEN1	*(vu32*)0xCC00681C
#define EXI_DMACNT1	*(vu32*)0xCC006820
#define EXI_IMMDAT1	*(vu32*)0xCC006824
#define EXI_STATUS2	*(vu32*)0xCC006828
#define EXI_DMABUF2	*(vu32*)0xCC00682C
#define EXI_DMALEN2	*(vu32*)0xCC006830
#define EXI_DMACNT2	*(vu32*)0xCC006834
#define EXI_IMMDAT2	*(vu32*)0xCC006838

#define EXI_CONTROL_TYPE_READ	0
#define EXI_CONTROL_TYPE_WRITE	1

#define EXI_CONTROL_IMM			0
#define EXI_CONTROL_ENABLE		1
#define EXI_CONTROL_DMA			2

#define EXI_MEMORY_CARD_59		0x00000004
#define EXI_MEMORY_CARD_123		0x00000008
#define EXI_MEMORY_CARD_251		0x00000010
#define EXI_MEMORY_CARD_507		0x00000020
#define EXI_MEMORY_CARD_1019	0x00000040
#define EXI_MEMORY_CARD_2043	0x00000080
#define EXI_USB_ADAPTER			0x01010000
#define EXI_IS_VIEWER			0x05070000
#define EXI_MODEM				0x02020000
#define EXI_ETHER				0x04020200

void GC_EXI_Init();
int GC_EXI_Probe(u32 channel);
void GC_EXI_Select(u32 channel, u32 device, u32 frequency);
void GC_EXI_Deselect(u32 channel);
void GC_EXI_Imm(u32 channel, u8 *abuffer, u32 size, u32 type);
void GC_EXI_ImmEx(u32 channel, u8 *abuffer, u32 size, u32 type);
void GC_EXI_Dma(u32 channel, u8 *abuffer, u32 size, u32 type);
u32 GC_EXI_RetrieveID(u32 channel, u32 device);
char *GC_EXI_GetType(int type);


#endif //_EXI_H_
