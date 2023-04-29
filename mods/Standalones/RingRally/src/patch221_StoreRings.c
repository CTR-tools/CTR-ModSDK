#include "ring.h"

struct RingData ringData[] =
{
	// position data is taken from
	// 8009900C->2D4 -- player data
	
	// Starting Line, Uka
	[CocoPark_BASE+0] =
	{
		.modelIndex = 0x40-0x3e,
		.posX = 0xFFFD7799>>12,
		.posY = 0x101EA>>12,
		.posZ = 0xFFE93B51>>12,
		.rot = 0,
	},
	
	// Corner of first turn, Uka
	[CocoPark_BASE+1] =
	{
		.modelIndex = 0x40-0x3e,
		.posX = 0xFFE9125D>>12,
		.posY = 0x1F20>>12,
		.posZ = 0xFFEC7C2D>>12,
		.rot = 0,
	},
	
	// grass hill jump, Uka
	[CocoPark_BASE+2] =
	{
		.modelIndex = 0x40-0x3e,
		.posX = 0xFFDF68C0>>12,
		.posY = 0x34FAD>>12,
		.posZ = 0xCD408>>12,
		.rot = 0x100, // actually 0x400
	},
	
	// tunnel enter, Aku
	[CocoPark_BASE+3] =
	{
		.modelIndex = 0x3e - 0x3e,
		.posX = 0xFFE8613C>>12,
		.posY = 0x1F2D>>12,
		.posZ = 0x11982B>>12,
		.rot = 0,
	},
	
	// tunnel top, Aku
	[CocoPark_BASE+4] =
	{
		.modelIndex = 0x3e - 0x3e,
		.posX = 0xFFFD964D>>12,
		.posY = 0x3EAD2>>12,
		.posZ = 0xD700E>>12,
		.rot = 0,
	},
	
	// exit tunnel, Uka
	[CocoPark_BASE+5] =
	{
		.modelIndex = 0x40-0x3e,
		.posX = 0x1F7BFC>>12,
		.posY = 0xDFD6>>12,
		.posZ = 0x138ABD>>12,
		.rot = 0,
	},
	
	// cut grass, Uka
	[CocoPark_BASE+6] =
	{
		.modelIndex = 0x40-0x3e,
		.posX = 0x29B65E,
		.posY = 0x1F3F,
		.posZ = 0xF7E76,
		.rot = 0,
	},
	
	// end turbo pad, Uka
	[CocoPark_BASE+7] =
	{
		.modelIndex = 0x40-0x3e,
		.posX = 0xE115F,
		.posY = 0x2004,
		.posZ = 0xFFEA4FB1,
		.rot = 0,
	},
	
	// first turbo pad, Uka
	[CocoPark_BASE+8] =
	{
		.modelIndex = 0x40-0x3e,
		.posX = 0xFFDA5E62,
		.posY = 0x9C50,
		.posZ = 0x15232E,
		.rot = 0x100, // actually 0x400
	},
};