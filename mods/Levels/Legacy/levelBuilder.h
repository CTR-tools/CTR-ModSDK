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

enum Split
{
	SPLIT_X,
	SPLIT_Y,
	SPLIT_Z
};

#define BSP_BRANCH(ID, AXIS, CHILD1, CHILD2) \
[ID] = \
{ \
	.flag = 0, \
	.id = ID, \
	.data = \
	{ \
		.branch = \
		{ \
			.axis = { \
				AXIS == SPLIT_X ? 0x1000 : 0, \
				AXIS == SPLIT_Y ? 0x1000 : 0, \
				AXIS == SPLIT_Z ? 0x1000 : 0, 0xFF40 \
			}, \
			.childID = {CHILD1, CHILD2}, \
		} \
	} \
}

#define BSP_LEAF(ID, FIRST, COUNT) \
[ID] = \
{ \
	.flag = 1, \
	.id = ID, \
	.data = \
	{ \
		.leaf = \
		{ \
			.numQuads = COUNT, \
			.ptrQuadBlockArray = LEV_OFFSETOF(quadBlock[FIRST]) \
		} \
	} \
}

// can't change these, or else triNormalVec has to change
#define sizeX 0x300
#define sizeZ 0x300

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
		},\
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
		.pvs = LEV_OFFSETOF(pvs) \
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
	.quadBlock[qIndex].checkpointIndex = -1
	
#define SET_POSY_FLAT(qIndex, posY) \
	.levVertex[9*qIndex+0].pos[1] = posY, \
	.levVertex[9*qIndex+1].pos[1] = posY, \
	.levVertex[9*qIndex+2].pos[1] = posY, \
	.levVertex[9*qIndex+3].pos[1] = posY, \
	.levVertex[9*qIndex+4].pos[1] = posY, \
	.levVertex[9*qIndex+5].pos[1] = posY, \
	.levVertex[9*qIndex+6].pos[1] = posY, \
	.levVertex[9*qIndex+7].pos[1] = posY, \
	.levVertex[9*qIndex+8].pos[1] = posY
	
#define SET_POSY_RAMP(qIndex, posY, height, low1, low2, low3, mid1, mid2, mid3, hi1, hi2, hi3) \
	.levVertex[9*qIndex+low1].pos[1] = posY, \
	.levVertex[9*qIndex+low2].pos[1] = posY, \
	.levVertex[9*qIndex+low3].pos[1] = posY, \
	.levVertex[9*qIndex+mid1].pos[1] = posY+(height/2), \
	.levVertex[9*qIndex+mid2].pos[1] = posY+(height/2), \
	.levVertex[9*qIndex+mid3].pos[1] = posY+(height/2), \
	.levVertex[9*qIndex+hi1].pos[1] = posY+height, \
	.levVertex[9*qIndex+hi2].pos[1] = posY+height, \
	.levVertex[9*qIndex+hi3].pos[1] = posY+height

// if clutX is 512 in VRAM, the clutX parameter is 32 (512>>4),
// bitshifting must be done for that variable, consistent to PNG names
#define ImageName_Blend(imgX, imgY, clutX, clutY, sizeX, sizeY, bpp, blend) \
	{.clut =  ((clutX >> 0) << 0) | (clutY << 6), \
	.tpage = ((imgX >> 6) << 0) | ((imgY >> 8) << 4) | (blend<<5) | (bpp<<7), \
	.u0 = ((imgX&0x3f)<<(2-bpp))+0, .v0 = (imgY&0xff)+0, \
	.u1 = ((imgX&0x3f)<<(2-bpp))+sizeX-1, .v1 = (imgY&0xff)+0, \
	.u2 = ((imgX&0x3f)<<(2-bpp))+0, .v2 = (imgY&0xff)+sizeY-1, \
	.u3 = ((imgX&0x3f)<<(2-bpp))+sizeX-1, .v3 = (imgY&0xff)+sizeY-1} \
	
#define ImageName_Scroll(imgX, imgY, clutX, clutY, sizeX, sizeY, bpp, blend, scale) \
	{.clut =  ((clutX >> 0) << 0) | (clutY << 6), \
	.tpage = ((imgX >> 6) << 0) | ((imgY >> 8) << 4) | (blend<<5) | (bpp<<7), \
	.u0 = ((imgX&0x3f)<<(2-bpp))+0, .v0 = ((imgY&0xff)+0)-scale, \
	.u1 = ((imgX&0x3f)<<(2-bpp))+sizeX-1, .v1 = ((imgY&0xff)+0)-scale, \
	.u2 = ((imgX&0x3f)<<(2-bpp))+0, .v2 = ((imgY&0xff)+sizeY-1)-scale, \
	.u3 = ((imgX&0x3f)<<(2-bpp))+sizeX-1, .v3 = ((imgY&0xff)+sizeY-1)-scale} \

	
// top/bottom left/right assuming you're rotation is 0,0,0
#define TEX_2X2(qIndex, BottomRight, BottomLeft, TopRight, TopLeft) \
	.quadBlock[qIndex].ptr_texture_mid = \
	{ \
		LEV_OFFSETOF(BottomRight), \
		LEV_OFFSETOF(BottomLeft), \
		LEV_OFFSETOF(TopRight), \
		LEV_OFFSETOF(TopLeft) \
	}

#define SetQuadBlockAnimTex(qIndex, animtex) \
	.quadBlock[qIndex].ptr_texture_mid[0] = LEV_OFFSETOF(animtex)|1, \
	.quadBlock[qIndex].ptr_texture_mid[1] = LEV_OFFSETOF(animtex)|1, \
	.quadBlock[qIndex].ptr_texture_mid[2] = LEV_OFFSETOF(animtex)|1, \
	.quadBlock[qIndex].ptr_texture_mid[3] = LEV_OFFSETOF(animtex)|1
