#ifndef _DPRINTF_H_
#define _DPRINTF_H_

#include <stdarg.h>

#include "types.h"
#include "string.h"
#include "memory.h"


static char *itoa(u32 num, u8 base);
void dprintf(char *str, char *fmt, ...);
void vdprintf(char *str, char *fmt, va_list list);

#endif //_DPRINTF_H_
