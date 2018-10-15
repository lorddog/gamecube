#ifndef _JOYPAD_H_
#define _JPYPAD_H_

#include "types.h"
#include "memory.h"


#define MEM_PAD_CHANNEL_BASE	(0xCC006400)
#define MEM_PAD_CHANNEL(chan)	(MEM_PAD_CHANNEL_BASE+(chan*12))

#define PAD_CHANNEL_0	(0)
#define PAD_CHANNEL_1	(1)
#define PAD_CHANNEL_2	(2)
#define PAD_CHANNEL_3	(3)

#define PAD_DIGITAL_LEFT	0x0001
#define PAD_DIGITAL_RIGHT	0x0002
#define PAD_DIGITAL_DOWN	0x0004
#define PAD_DIGITAL_UP		0x0008
#define PAD_DIGITAL_Z		0x0010
#define PAD_DIGITAL_R		0x0020
#define PAD_DIGITAL_L		0x0040
#define PAD_DIGITAL_A		0x0100
#define PAD_DIGITAL_B		0x0200
#define PAD_DIGITAL_X		0x0400
#define PAD_DIGITAL_Y		0x0800
#define PAD_DIGITAL_START	0x1000


typedef struct {
	u8 Up;
	u8 Down;
	u8 Left;
	u8 Right;
	u8 L;
	u8 R;
	u8 A;
	u8 B;
	u8 X;
	u8 Y;
	u8 Z;
	u8 Start;
} PAD_DIGITAL;

typedef struct {
	s8 X;
	s8 Y;
} PAD_ANALOG;

typedef struct {
	u8 L;
	u8 R;
} PAD_TRIGGER;

typedef struct {
	PAD_DIGITAL	Digital;
	PAD_ANALOG	Analog;
	PAD_ANALOG	AnalogC;
	PAD_TRIGGER	Trigger;
} PAD;

void PadReadState(PAD *pPad, u8 PadChannel);
u16 PadDigitalState(u8 chan);
u16 PadDigitalDown(u8 chan);
u16 PadDigitalUp(u8 chan);


#endif //_PAD_H_
