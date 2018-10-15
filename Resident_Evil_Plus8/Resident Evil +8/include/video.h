#ifndef _VIDEO_H_
#define _VIDEO_H_

#include "types.h"
#include "memory.h"


#define VIDEOMODE_NTSC	0
#define VIDEOMODE_PAL	1
#define VIDEOMODE_MPAL	2

#define VIDEO_MODE			*(u32*)(0x800000CC)

#define VI_VTIMING			*(vu16*)(0xCC002000)
#define VIDEO_TOPFIELD_L	*(vu32*)(0xCC00201C)
#define VIDEO_TOPFIELD_R	*(vu32*)(0xCC002020)
#define VIDEO_BOTTOMFIELD_L	*(vu32*)(0xCC002024)
#define VIDEO_BOTTOMFIELD_R	*(vu32*)(0xCC002028)
#define VIDEO_VCOUNT		*(vu16*)(0xCC00202C)
#define VIDEO_HCOUNT		*(vu16*)(0xCC00202E)
#define VI_DISPINT0			*(vu32*)(0xCC002030)
#define VI_DISPINT1			*(vu32*)(0xCC002034)
#define VI_SCALEWIDTH		*(vu16*)(0xCC002048)

#define BACKBUFFER			video_xfb[video_curxfb]
#define FRONTBUFFER			video_xfb[video_curxfb^1]

#define COLOR_BLACK			(0x00800080)
#define COLOR_MAROON		(0x266A26C0)
#define COLOR_GREEN			(0x4B554B4A)
#define COLOR_OLIVE			(0x7140718A)
#define COLOR_NAVY			(0x0EC00E75)
#define COLOR_PURPLE		(0x34AA34B5)
#define COLOR_TEAL			(0x59955940)
#define COLOR_GRAY			(0x80808080)
#define COLOR_SILVER		(0xC080C080)
#define COLOR_RED			(0x4C544CFF)
#define COLOR_LIME			(0x952B9515)
#define COLOR_YELLOW		(0xE100E194)
#define COLOR_BLUE			(0x1DFF1D6B)
#define COLOR_FUCHSIA		(0x69D469EA)
#define COLOR_AQUA			(0xB2ABB200)
#define COLOR_WHITE			(0xFF80FF80)
#define COLOR_MONEYGREEN	(0xD076D074)
#define COLOR_SKYBLUE		(0xC399C36A)
#define COLOR_CREAM			(0xFA79FA82)
#define COLOR_MEDGRAY		(0xA082A07F)


extern u8 *video_xfb[2];
extern u8 video_curxfb;
extern u16 VideoWidth,VideoHeight;

void VSync();
void VideoInit();
void VideoReset();
void VideoFlip();
void VideoClear(u32 color);
void VideoSetBlack(u8 black);
u32 YUV2RGB(u8 Y, u8 U, u8 V);
u32 RGB2YCbYCr(u8 R, u8 G, u8 B);

#endif
