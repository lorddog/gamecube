#ifndef _SERIAL_H_
#define _SERIAL_H_

#include "types.h"


#define SERIALTRANSFER	0x80000000

void SerialInit();
u32 SerialGetType(u8 channel);
void SerialTransfer(u8 channel, u32 *src, u8 srclen, u32 *dst, u8 dstlen);
void SerialSetCommand(u8 channel, u32 command);
void SerialSendCommands();

#endif //_SERIAL_H_
