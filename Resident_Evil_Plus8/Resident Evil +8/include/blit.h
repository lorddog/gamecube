#ifndef _BLIT_H_
#define _BLIT_H_

#include "types.h"


#define BlitScreen(x,y,src,src_w,src_h)						Blit((u32*)(BACKBUFFER),(x),(y),VideoWidth,VideoHeight,(src),(src_w),(src_h));
#define BlitExScreen(x,y,src,src_w,src_h,src_tw,src_th)		BlitEx((u32*)(BACKBUFFER),(x),(y),VideoWidth,VideoHeight,(src),(src_w),(src_h),(src_tw),(src_th));

void BlitRGB(u32 *dst,s32 x,s32 y,s32 dst_width,s32 dst_height,const u8 *src,s32 src_width,s32 src_height);
void Blit(u32 *dst,s32 x,s32 y,s32 dst_width,s32 dst_height,const u32 *src,s32 src_width,s32 src_height);
void BlitEx(u32 *dst,s32 x,s32 y,s32 dst_width,s32 dst_height,const u32 *src,s32 src_width,s32 src_height,s32 src_width_total,s32 src_height_total);

#endif //_BLIT_H_
