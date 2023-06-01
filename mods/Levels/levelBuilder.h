#define LEV_OFFSETOF(ELEMENT) OFFSETOF(struct LevelFile, ELEMENT)-4

#define NEW_VERTEX(posX, posY, posZ, flag, colR, colG, colB) \
{ \
	.pos = {posX, posY, posZ}, \
	.flags = flag, \
	.color_hi = {colR, colG, colB, 0}, \
	.color_lo = {colR, colG, colB, 0}, \
}

enum BitsPerPixel
{
	BPP_4 = 0,
	BPP_8 = 1,
	BPP_16 = 2
};

// can't change these, or else triNormalVec has to change
#define sizeX 0x300
#define sizeZ 0x300

/*
	NEW_BLOCK
	(
		// index, texture
		0, texgroup_ground,

		// posX, posZ
		// +z is forward, +x is left, not right
		// size of a quadblock is always 0x300 x 0x300, as per the above macros
		0x0, 0x0,

		// vertex flags, quadblock flags
		NULL, 0x1800,

		// RGB color
		RGBtoBGR(0xFF0000),
	),
*/

#define NEW_BLOCK(qIndex, texgroup, posX, posZ, flagV, flagQ, color) \
	.levVertex[9*qIndex+0] = NEW_VERTEX(posX-sizeX/2, 0, posZ-sizeZ/2, flagV, GetRed(color), GetGreen(color), GetBlue(color)),\
	.levVertex[9*qIndex+1] = NEW_VERTEX(posX+sizeX/2, 0, posZ-sizeZ/2, flagV, GetRed(color), GetGreen(color), GetBlue(color)),\
	.levVertex[9*qIndex+2] = NEW_VERTEX(posX-sizeX/2, 0, posZ+sizeZ/2, flagV, GetRed(color), GetGreen(color), GetBlue(color)),\
	.levVertex[9*qIndex+3] = NEW_VERTEX(posX+sizeX/2, 0, posZ+sizeZ/2, flagV, GetRed(color), GetGreen(color), GetBlue(color)),\
	.levVertex[9*qIndex+4] = NEW_VERTEX(posX, 0, posZ-sizeZ/2, flagV, GetRed(color), GetGreen(color), GetBlue(color)),\
	.levVertex[9*qIndex+5] = NEW_VERTEX(posX-sizeX/2, 0, posZ, flagV, GetRed(color), GetGreen(color), GetBlue(color)),\
	.levVertex[9*qIndex+6] = NEW_VERTEX(posX, 0, posZ, flagV, GetRed(color), GetGreen(color), GetBlue(color)),\
	.levVertex[9*qIndex+7] = NEW_VERTEX(posX+sizeX/2, 0, posZ, flagV, GetRed(color), GetGreen(color), GetBlue(color)),\
	.levVertex[9*qIndex+8] = NEW_VERTEX(posX, 0, posZ+sizeZ/2, flagV, GetRed(color), GetGreen(color), GetBlue(color)), \
	.quadBlock[qIndex] = \
	{ \
		.index = {9*qIndex+0,9*qIndex+1,9*qIndex+2,9*qIndex+3,9*qIndex+4,9*qIndex+5,9*qIndex+6,9*qIndex+7,9*qIndex+8}, \
		.quadFlags = flagQ, \
		.draw_order_low = 0, \
		.draw_order_high = 0, \
		.ptr_texture_mid = \
		{ \
			LEV_OFFSETOF(texgroup), \
			LEV_OFFSETOF(texgroup), \
			LEV_OFFSETOF(texgroup), \
			LEV_OFFSETOF(texgroup) \
		}, \
		\
		.bbox = \
		{ \
			.min = {posX-sizeX/2, 0, posZ-sizeZ/2}, \
			.max = {posX+sizeX/2, 0, posZ+sizeZ/2} \
		}, \
		.terrain_type = 0, \
		.weather_intensity = 0, \
		.weather_vanishRate = 0, \
		.speedImpact = 0, \
		\
		.blockID = 0, \
		.checkpointIndex = qIndex, \
		.triNormalVecBitShift = 0x12, \
		\
		.ptr_texture_low = LEV_OFFSETOF(texgroup), \
		.pvs = LEV_OFFSETOF(pvs), \
		\
		.triNormalVecDividend = \
		{ \
			/* hi 2 */ \
			0x1C71, \
			0x1C71, \
			0x1C71, \
			0x1C71, \
			0x1C71, \
			0x1C71, \
			0x1C71, \
			0x1C71, \
			\
			/* lo 2 */ \
			0x1C71, \
			0x1C71, \
		} \
	}
	
// get vertex numbers from here:
// posted by DCxDemo, 4/25/2020 2:44pm, in #ctr-mod-ideas
// https://discord.com/channels/527135227546435584/534794647738908683/703677797440159744
#define MAKE_RAMP(qIndex, height, low1, low2, low3, mid1, mid2, mid3, hi1, hi2, hi3) \
	.levVertex[9*qIndex+low1].pos[1] = 0, \
	.levVertex[9*qIndex+low2].pos[1] = 0, \
	.levVertex[9*qIndex+low3].pos[1] = 0, \
	.levVertex[9*qIndex+mid1].pos[1] = height/2, \
	.levVertex[9*qIndex+mid2].pos[1] = height/2, \
	.levVertex[9*qIndex+mid3].pos[1] = height/2, \
	.levVertex[9*qIndex+hi1].pos[1] = height, \
	.levVertex[9*qIndex+hi2].pos[1] = height, \
	.levVertex[9*qIndex+hi3].pos[1] = height, \
	.quadBlock[qIndex].checkpointIndex = -1, \
	.quadBlock[qIndex].bbox.max[1] = height, \
	.quadBlock[qIndex].triNormalVecDividend = \
	{ \
		/* hi 2 */ \
		0x1971, \
		0x1971, \
		0x1971, \
		0x1971, \
		0x1971, \
		0x1971, \
		0x1971, \
		0x1971, \
		\
		/* lo 2 */ \
		0x1971,  \
		0x1971,  \
	}
	
#define SET_POSY_FLAT(qIndex, posY) \
	.levVertex[9*qIndex+0].pos[1] = posY, \
	.levVertex[9*qIndex+1].pos[1] = posY, \
	.levVertex[9*qIndex+2].pos[1] = posY, \
	.levVertex[9*qIndex+3].pos[1] = posY, \
	.levVertex[9*qIndex+4].pos[1] = posY, \
	.levVertex[9*qIndex+5].pos[1] = posY, \
	.levVertex[9*qIndex+6].pos[1] = posY, \
	.levVertex[9*qIndex+7].pos[1] = posY, \
	.levVertex[9*qIndex+8].pos[1] = posY, \
	.quadBlock[qIndex].bbox.min[1] = posY, \
	.quadBlock[qIndex].bbox.max[1] = posY
	
#define SET_POSY_RAMP(qIndex, posY, height, low1, low2, low3, mid1, mid2, mid3, hi1, hi2, hi3) \
	.levVertex[9*qIndex+low1].pos[1] = posY, \
	.levVertex[9*qIndex+low2].pos[1] = posY, \
	.levVertex[9*qIndex+low3].pos[1] = posY, \
	.levVertex[9*qIndex+mid1].pos[1] = posY+(height/2), \
	.levVertex[9*qIndex+mid2].pos[1] = posY+(height/2), \
	.levVertex[9*qIndex+mid3].pos[1] = posY+(height/2), \
	.levVertex[9*qIndex+hi1].pos[1] = posY+height, \
	.levVertex[9*qIndex+hi2].pos[1] = posY+height, \
	.levVertex[9*qIndex+hi3].pos[1] = posY+height, \
	.quadBlock[qIndex].bbox.min[1] = posY, \
	.quadBlock[qIndex].bbox.max[1] = posY+height

// if clutX is 512 in VRAM, the clutX parameter is 32 (512>>4),
// bitshifting must be done for that variable, consistent to PNG names
#define ImageName_Blend(imgX, imgY, clutX, clutY, sizeX, sizeY, bpp, blend) \
	{.clut =  ((clutX >> 0) << 0) | (clutY << 6), \
	.tpage = ((imgX >> 6) << 0) | ((imgY >> 8) << 4) | (blend<<5) | (bpp<<7), \
	.u0 = ((imgX&0x3f)<<(2-bpp))+0, .v0 = (imgY&0xff)+0, \
	.u1 = ((imgX&0x3f)<<(2-bpp))+sizeX-1, .v1 = (imgY&0xff)+0, \
	.u2 = ((imgX&0x3f)<<(2-bpp))+0, .v2 = (imgY&0xff)+sizeY-1, \
	.u3 = ((imgX&0x3f)<<(2-bpp))+sizeX-1, .v3 = (imgY&0xff)+sizeY-1} \
	
// top/bottom left/right assuming you're rotation is 0,0,0
#define TEX_2X2(qIndex, BottomRight, BottomLeft, TopRight, TopLeft) \
	.quadBlock[qIndex].ptr_texture_mid = \
	{ \
		LEV_OFFSETOF(BottomRight), \
		LEV_OFFSETOF(BottomLeft), \
		LEV_OFFSETOF(TopRight), \
		LEV_OFFSETOF(TopLeft) \
	}

#define PTR_MAP_QUADBLOCK(x) \
	LEV_OFFSETOF(quadBlock[x].ptr_texture_mid[0]),\
	LEV_OFFSETOF(quadBlock[x].ptr_texture_mid[1]),\
	LEV_OFFSETOF(quadBlock[x].ptr_texture_mid[2]),\
	LEV_OFFSETOF(quadBlock[x].ptr_texture_mid[3]),\
	LEV_OFFSETOF(quadBlock[x].ptr_texture_low),\
	LEV_OFFSETOF(quadBlock[x].pvs)

#define TurboPadImage(imgX, imgY, clutX, clutY, sizeX, sizeY, bpp, blend, scale) \
	{.clut =  ((clutX >> 0) << 0) | (clutY << 6), \
	.tpage = ((imgX >> 6) << 0) | ((imgY >> 8) << 4) | (blend<<5) | (bpp<<7), \
	.u0 = ((imgX&0x3f)<<(2-bpp))+0, .v0 = ((imgY&0xff)+0)-scale, \
	.u1 = ((imgX&0x3f)<<(2-bpp))+sizeX-1, .v1 = ((imgY&0xff)+0)-scale, \
	.u2 = ((imgX&0x3f)<<(2-bpp))+0, .v2 = ((imgY&0xff)+sizeY-1)-scale, \
	.u3 = ((imgX&0x3f)<<(2-bpp))+sizeX-1, .v3 = ((imgY&0xff)+sizeY-1)-scale} \

#define TurboPadScroll(tp_imgX, tp_imgY, tp_clutX, tp_clutY, tp_sizeX, tp_sizeY, tp_bpp, tp_blend, scale) \
	{ \
		.far    = TurboPadImage(tp_imgX, tp_imgY, tp_clutX, tp_clutY, tp_sizeX, tp_sizeY, tp_bpp, tp_blend, scale), \
		.middle = TurboPadImage(tp_imgX, tp_imgY, tp_clutX, tp_clutY, tp_sizeX, tp_sizeY, tp_bpp, tp_blend, scale), \
		.near   = TurboPadImage(tp_imgX, tp_imgY, tp_clutX, tp_clutY, tp_sizeX, tp_sizeY, tp_bpp, tp_blend, scale), \
		.mosaic = TurboPadImage(tp_imgX, tp_imgY, tp_clutX, tp_clutY, tp_sizeX, tp_sizeY, tp_bpp, tp_blend, scale), \
	},

#define SetQuadBlockAnimTex(qIndex, animtex) \
	.quadBlock[qIndex].ptr_texture_mid[0] = LEV_OFFSETOF(animtex)|1, \
	.quadBlock[qIndex].ptr_texture_mid[1] = LEV_OFFSETOF(animtex)|1, \
	.quadBlock[qIndex].ptr_texture_mid[2] = LEV_OFFSETOF(animtex)|1, \
	.quadBlock[qIndex].ptr_texture_mid[3] = LEV_OFFSETOF(animtex)|1
