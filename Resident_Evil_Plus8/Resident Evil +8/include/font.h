#ifndef _FONT_H_
#define _FONT_H_

#include "types.h"
#include "video.h"
#include "string.h"
#include "blit.h"


#define FONTYUV		0
#define FONT1BPP	1


void FontInit(const u32 *ptr, u32 width, u32 height, u32 total_width, u8 bpp);
void FontChar1BPP(int x, int y, char c);
void FontChar(int x, int y, char c);
void FontString(int x, int y, char *s);
void FontStringCentre(int y, char *s);
void FontStringLength(int x, int y, char *s, u32 length);

#endif //_FONT_H_
