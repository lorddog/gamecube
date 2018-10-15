#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdarg.h>

#include "types.h"
#include "bba.h"
#include "dprintf.h"


void DebugInit(UDPHANDLE *uh);
void DebugNetPrint(char *fmt, ...);

#endif //_DEBUG_H_
