/* low-level RGB bitmap functions, by Parasyte */

#ifndef _BITMAP_H_
#define _BITMAP_H_

#include "types.h"
#include "video.h"
#include "heap.h"
#include "memory.h"


#define BitmapBlitScreen(b)			BitmapBlit((u32*)(BACKBUFFER),VideoWidth,VideoHeight,(b))
#define BitmapBlitTransScreen(b,c)	BitmapBlitTrans((u32*)(BACKBUFFER),VideoWidth,VideoHeight,(b),(c))

typedef struct _BITMAP {
	u16 x;
	u16 y;
	u16 w;
	u16 h;
	u32 *bits;
} BITMAP;

u8 BitmapCreate(BITMAP *bmp, int x, int y, int w, int h);
void BitmapDelete(BITMAP *bmp);
void BitmapBlit(u32 *dst, u16 dst_w, u16 dst_h, BITMAP *bmp);
void BitmapBlitTrans(u32 *dst, u16 dst_w, u16 dst_h, BITMAP *bmp, u32 trans);

#endif //_BITMAP_H_
