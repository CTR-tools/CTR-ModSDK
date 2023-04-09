#ifndef __PSXGPU_H
#include <psn00bsdk/include/psxgpu.h>
#endif

#define force_inline static inline __attribute__((always_inline))

force_inline void addPolyF3(u_long* ot, POLY_F3* p)
{
	p->tag = 0x4000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x20;
}

force_inline void addPolyFT3(u_long* ot, POLY_FT3* p)
{
	p->tag = 0x7000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x24;
}

force_inline void addPolyG3(u_long* ot, POLY_G3* p)
{
	p->tag = 0x6000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x30;
}

force_inline void addPolyGT3(u_long* ot, POLY_GT3* p)
{
	p->tag = 0x9000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x34;
}

force_inline void addPolyF4(u_long* ot, POLY_F4* p)
{
	p->tag = 0x5000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x28;
}

force_inline void addPolyFT4(u_long* ot, POLY_FT4* p)
{
	p->tag = 0x9000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x2c;
}

force_inline void addPolyG4(u_long* ot, POLY_G4* p)
{
	p->tag = 0x8000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x38;
}

force_inline void addPolyGT4(u_long* ot, POLY_GT4* p)
{
	p->tag = 0xc000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x3c;
}

force_inline void addSprt8(u_long* ot, SPRT* p)
{
	p->tag = 0x3000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x74;
}

force_inline void addSprt16(u_long* ot, SPRT* p)
{
	p->tag = 0x3000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x7c;
}

force_inline void addSprt(u_long* ot, SPRT* p)
{
	p->tag = 0x4000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x64;
}

force_inline void addTile1(u_long* ot, TILE* p)
{
	p->tag = 0x2000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x68;
}

force_inline void addTile8(u_long* ot, TILE* p)
{
	p->tag = 0x2000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x70;
}

force_inline void addTile16(u_long* ot, TILE* p)
{
	p->tag = 0x2000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x78;
}

force_inline void addTile(u_long* ot, TILE* p)
{
	p->tag = 0x3000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x60;
}

force_inline void addLineF2(u_long* ot, LINE_F2* p)
{
	p->tag = 0x3000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x40;
}

force_inline void addLineG2(u_long* ot, LINE_G2* p)
{
	p->tag = 0x4000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x50;
}

force_inline void addLineF3(u_long* ot, LINE_F3* p)
{
	p->tag = 0x5000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x48;
	p->pad = 0x55555555;
}

force_inline void addLineG3(u_long* ot, LINE_G3* p)
{
	p->tag = 0x7000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x58;
	p->pad = 0x55555555;
	p->p1, p->p2 = 0;
}

force_inline void addLineF4(u_long* ot, LINE_F4* p)
{
	p->tag = 0x6000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x4c;
	p->pad = 0x55555555;
}

force_inline void addLineG4(u_long* ot, LINE_G4* p)
{
	p->tag = 0x9000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x5c;
	p->pad = 0x55555555;
	p->p1, p->p2 = 0;
}

force_inline void addFill(u_long* ot, FILL* p)
{
	p->tag = 0x3000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 2;
}

force_inline void addVram2Vram(u_long* ot, VRAM2VRAM* p)
{
	p->tag = 0x8000000 | *ot;
	*ot = ((u_int) p) ^ 0x80000000;
	p->code = 0x80;
	p->pad[0], p->pad[1], p->pad[2], p->pad[3] = 0;
}

// clear blending mode bits of the texpage using AND, then set them using OR
// then set image to use semi-transparent mode using the setSemiTrans macro
// (which enables the 2 bit on the primitive's code field)
#define setTransparency(p, transparency) \
	p->tpage = p->tpage & 0xff9f | (transparency - 1) << 5, \
	p->code |= 2

// macros for setting the rgb values in primitives using pointer blah blah
// this is *maybe* what naughty dog did?
// all primitive functions pass colors as a single 32-bit integer value
// these macros are used prior to any of the primitive functions seen in this
// header as they overwrite the primitive's code value
#define setInt32RGB0(p, color0) \
	*(u_int*)&p->r0 = color0,

#define setInt32RGB4(p, color0, color1, color2, color3) \
	*(u_int*)&p->r0 = color0, \
	*(u_int*)&p->r1 = color1, \
	*(u_int*)&p->r2 = color2, \
	*(u_int*)&p->r3 = color3
