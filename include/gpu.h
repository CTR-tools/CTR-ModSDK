#pragma once

#ifdef REBUILD_PC
#define ADD_PSX_ADDRESS
#else
#define ADD_PSX_ADDRESS ^ 0x80000000
#endif

force_inline void addPolyF3(u_long* ot, POLY_F3* p)
{
	p->tag = 0x4000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x20;
}

force_inline void addPolyFT3(u_long* ot, POLY_FT3* p)
{
	p->tag = 0x7000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x24;
}

force_inline void addPolyG3(u_long* ot, POLY_G3* p)
{
	p->tag = 0x6000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x30;
}

force_inline void addPolyGT3(u_long* ot, POLY_GT3* p)
{
	p->tag = 0x9000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x34;
}

force_inline void addPolyF4(u_long* ot, POLY_F4* p)
{
	p->tag = 0x5000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x28;
}

force_inline void addPolyFT4(u_long* ot, POLY_FT4* p)
{
	p->tag = 0x9000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x2c;
}

force_inline void addPolyG4(u_long* ot, POLY_G4* p)
{
	p->tag = 0x8000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x38;
}

force_inline void addPolyGT4(u_long* ot, POLY_GT4* p)
{
	p->tag = 0xc000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x3c;
}

force_inline void addSprt8(u_long* ot, SPRT* p)
{
	p->tag = 0x3000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x74;
}

force_inline void addSprt16(u_long* ot, SPRT* p)
{
	p->tag = 0x3000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x7c;
}

force_inline void addSprt(u_long* ot, SPRT* p)
{
	p->tag = 0x4000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x64;
}

force_inline void addTile1(u_long* ot, TILE* p)
{
	p->tag = 0x2000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x68;
}

force_inline void addTile8(u_long* ot, TILE* p)
{
	p->tag = 0x2000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x70;
}

force_inline void addTile16(u_long* ot, TILE* p)
{
	p->tag = 0x2000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x78;
}

force_inline void addTile(u_long* ot, TILE* p)
{
	p->tag = 0x3000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x60;
}

force_inline void addLineF2(u_long* ot, LINE_F2* p)
{
	p->tag = 0x3000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x40;
}

force_inline void addLineG2(u_long* ot, LINE_G2* p)
{
	p->tag = 0x4000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x50;
}

force_inline void addLineF3(u_long* ot, LINE_F3* p)
{
	p->tag = 0x5000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x48;
	p->pad = 0x55555555;
}

force_inline void addLineG3(u_long* ot, LINE_G3* p)
{
	p->tag = 0x7000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x58;
	p->pad = 0x55555555;
	p->p1, p->p2 = 0;
}

force_inline void addLineF4(u_long* ot, LINE_F4* p)
{
	p->tag = 0x6000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x4c;
	p->pad = 0x55555555;
}

force_inline void addLineG4(u_long* ot, LINE_G4* p)
{
	p->tag = 0x9000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 0x5c;
	p->pad = 0x55555555;
	p->p1, p->p2 = 0;
}

#ifndef REBUILD_PC
force_inline void addFill(u_long* ot, FILL* p)
{
	p->tag = 0x3000000 | *ot;
	*ot = ((u_int) p) ADD_PSX_ADDRESS;
	p->code = 2;
}
#endif

// version of psn00bsdk's setXY4 macro that compiles to a smaller bytesize
// based on original compiled code for the game's primitive functions
// this produces bugs if any of the X values are negative and not cast to u_short
// this is terrible code
// please avoid writing something like this, unless you really really need it
#define setXY4CompilerHack(p, s0, t0, s1, t1, s2, t2, s3, t3) \
	*(u_int*)&p->x0 = s0 | (t0 << 16), \
	*(u_int*)&p->x1 = s1 | (t1 << 16), \
	*(u_int*)&p->x2 = s2 | (t2 << 16), \
	*(u_int*)&p->x3 = s3 | (t3 << 16)

// like psn00bsdk's setColor macros but with terrible compiler hacks
// as the color values are read and written as 32-bit ints these have to be used prior to setting code
#define setInt32RGB0(p, color0) \
	*(u_int*)&p->r0 = color0

#define setInt32RGB4(p, color0, color1, color2, color3) \
	*(u_int*)&p->r0 = color0, \
	*(u_int*)&p->r1 = color1, \
	*(u_int*)&p->r2 = color2, \
	*(u_int*)&p->r3 = color3

// clear blending mode bits of the texpage using AND, then set them using OR
// then set image to use semi-transparent mode using the setSemiTrans macro
// (which enables the 2 bit on the primitive's code field)
#define setTransparency(p, transparency) \
	p->tpage = p->tpage & 0xff9f | (transparency - 1) << 5, \
	p->code |= 2

// version of psn00bsdk's setColor macro that simultaneously accepts 4 colors
#define setColor4(p, rgb0, rgb1, rgb2, rgb3) \
	(((P_COLOR *) &((p)->r0))->color = (rgb0)), \
	(((P_COLOR *) &((p)->r1))->color = (rgb1)), \
	(((P_COLOR *) &((p)->r2))->color = (rgb2)), \
	(((P_COLOR *) &((p)->r3))->color = (rgb3))
