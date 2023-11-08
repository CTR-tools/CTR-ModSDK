#include <common.h>

void DECOMP_MainInit_VRAMClear()
{
	DRAWENV drawEnv;
	TILE tile;

	// SoapyMan: Not clear enough but it appears to be TILE but need to clarify in disasm.

	//struct
	//{
	//	int a;
	//	short b1, b2, c, d, e, f;
	//} commands;
	
	SetDefDrawEnv(&drawEnv,0,0,0x400,0x200);
	drawEnv.dfe = 1;
	PutDrawEnv(&drawEnv);

	setTile(&tile);
	termPrim(&tile);

	tile.r0 = tile.g0 = tile.b0 = 0;
	tile.x0 = 0;
	tile.y0 = 0;
	tile.w = 1023;
	tile.h = 511;
	
	//commands.a = 0x3ffffff;
	//
	//commands.b1 = 0;
	//commands.b2 = 512;
	//commands.c = 0;
	//commands.d = 0;
	//commands.e = 1023;
	//commands.f = 511;

	DrawOTag(&tile);
	
	tile.y0 = 511;
	tile.h = 1;
	//commands.d = 511;
	//commands.f = 1;
	DrawOTag(&tile);
}