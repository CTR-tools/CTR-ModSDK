#include <common.h>

#define OFFSETOF(TYPE, ELEMENT) ((unsigned int)&(((TYPE *)0)->ELEMENT))

#define NEW_VERTEX(posX, posY, posZ, flag, colR, colG, colB) \
{ \
	.pos = {posX, posY, posZ}, \
	.flags = flag, \
	.color_hi = {colR, colG, colB, 0}, \
	.color_lo = {colR, colG, colB, 0}, \
}

// can't change these, or else triNormalVec has to change
#define sizeX 0x300
#define sizeZ 0x300

#define NEW_BLOCK(qIndex, group4, posX, posZ, flagV, flagQ, colR, colG, colB) \
	.levVertex[9*qIndex+0] = NEW_VERTEX(posX-sizeX/2, 0, posZ-sizeZ/2, flagV, colR, colG, colB),\
	.levVertex[9*qIndex+1] = NEW_VERTEX(posX+sizeX/2, 0, posZ-sizeZ/2, flagV, colR, colG, colB),\
	.levVertex[9*qIndex+2] = NEW_VERTEX(posX-sizeX/2, 0, posZ+sizeZ/2, flagV, colR, colG, colB),\
	.levVertex[9*qIndex+3] = NEW_VERTEX(posX+sizeX/2, 0, posZ+sizeZ/2, flagV, colR, colG, colB),\
	.levVertex[9*qIndex+4] = NEW_VERTEX(posX, 0, posZ-sizeZ/2, flagV, colR, colG, colB),\
	.levVertex[9*qIndex+5] = NEW_VERTEX(posX-sizeX/2, 0, posZ, flagV, colR, colG, colB),\
	.levVertex[9*qIndex+6] = NEW_VERTEX(posX, 0, posZ, flagV, colR, colG, colB),\
	.levVertex[9*qIndex+7] = NEW_VERTEX(posX+sizeX/2, 0, posZ, flagV, colR, colG, colB),\
	.levVertex[9*qIndex+8] = NEW_VERTEX(posX, 0, posZ+sizeZ/2, flagV, colR, colG, colB), \
	.quadBlock[qIndex] = \
	{ \
		.index = {9*qIndex+0,9*qIndex+1,9*qIndex+2,9*qIndex+3,9*qIndex+4,9*qIndex+5,9*qIndex+6,9*qIndex+7,9*qIndex+8}, \
		.quadFlags = flagQ, \
		.draw_order_low = 0, \
		.draw_order_high = 0, \
		.ptr_texture_mid = \
		{ \
			OFFSETOF(struct LevelFile, group4)-4, \
			OFFSETOF(struct LevelFile, group4)-4, \
			OFFSETOF(struct LevelFile, group4)-4, \
			OFFSETOF(struct LevelFile, group4)-4 \
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
		.respawnIndex = -1, \
		.triNormalVecBitShift = 0x12, \
		\
		.ptr_texture_low = OFFSETOF(struct LevelFile, group4)-4, \
		.pvs = OFFSETOF(struct LevelFile, pvs)-4, \
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
	.quadBlock[qIndex].respawnIndex = -1, \
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

// if clutX is 512 in VRAM, the clutX parameter is 32 (512>>4),
// bitshifting must be done for that variable, consistent to PNG names
#define ImageName_Blend(imgX, imgY, clutX, clutY, sizeX, sizeY, bpp, blend) \
	{.clut =  ((clutX >> 0) << 0) | (clutY << 6), \
	.tpage = ((imgX >> 6) << 0) | ((imgY >> 8) << 4) | (blend<<5) | (bpp<<7), \
	.u0 = 0, .v0 = 0, \
	.u1 = sizeX-1, .v1 = 0, \
	.u2 = 0, .v2 = sizeY-1, \
	.u3 = sizeX-1, .v3 = sizeY-1} \

#define PTR_MAP_QUADBLOCK(x) \
	OFFSETOF(struct LevelFile, quadBlock[x].ptr_texture_mid[0])-4,\
	OFFSETOF(struct LevelFile, quadBlock[x].ptr_texture_mid[1])-4,\
	OFFSETOF(struct LevelFile, quadBlock[x].ptr_texture_mid[2])-4,\
	OFFSETOF(struct LevelFile, quadBlock[x].ptr_texture_mid[3])-4,\
	OFFSETOF(struct LevelFile, quadBlock[x].ptr_texture_low)-4,\
	OFFSETOF(struct LevelFile, quadBlock[x].pvs)-4

#define NUM_BLOCKS 20

struct LevelFile
{
	void* ptrMap;
	struct Level level;
	struct mesh_info mInfo;
	struct IconGroup4 group4_ground;
	struct IconGroup4 group4_ramp;
	struct IconGroup4 group4_ramp_flip180;
	struct TextureLayout texlayout_ramp_low;
	struct TextureLayout texlayout_ramp_low_flipV;
	struct SpawnType1 ptrSpawnType1;
	struct WarpballPathNode noderespawnsthing[16];
	struct QuadBlock quadBlock[NUM_BLOCKS];
	struct LevVertex levVertex[NUM_BLOCKS*9];
	struct BSP bsp[3];
	struct PVS pvs;
	int visBitIndex[4];
	struct VisMem visMem;
	
	int VisMem_bitIndex_DstMemcpyP1[8]; // leave empty
	int VisMem_bspList_RenderListP1[3*2];
	int VisMem_bitIndex_DstMemcpyP2[8]; // leave empty
	int VisMem_bspList_RenderListP2[3*2];
	int VisMem_bitIndex_DstMemcpyP3[8]; // leave empty
	int VisMem_bspList_RenderListP3[3*2];
	int VisMem_bitIndex_DstMemcpyP4[8]; // leave empty
	int VisMem_bspList_RenderListP4[3*2];
	
	int map[(31+NUM_BLOCKS*6)+1];
};

struct LevelFile file =
{
	.ptrMap = OFFSETOF(struct LevelFile, map[0])-4,
	
	.level =
	{
		.ptr_mesh_info = OFFSETOF(struct LevelFile, mInfo)-4,
		.visMem = OFFSETOF(struct LevelFile, visMem)-4,
		
		// warning, game will edit rotY by 0x400 after spawn
		
		.DriverSpawn[0].pos = {0,0,0},
		.DriverSpawn[0].rot = {0,0-0x400,0},
		
		.DriverSpawn[1].pos = {0,0,0},
		.DriverSpawn[1].rot = {0,0-0x400,0},
		
		.DriverSpawn[2].pos = {0,0,0},
		.DriverSpawn[2].rot = {0,0-0x400,0},
	
		.DriverSpawn[3].pos = {0,0,0},
		.DriverSpawn[3].rot = {0,0-0x400,0},
		
		.ptrSpawnType1 = OFFSETOF(struct LevelFile, ptrSpawnType1)-4,
		
		.clearColor[0].rgb = {0x0, 0x0, 0x28},
		.clearColor[0].enable = 1,
		
		.cnt_restart_points = 16,
		.ptr_restart_points = OFFSETOF(struct LevelFile, noderespawnsthing[0])-4,
	},
	
	.mInfo =
	{
		.numQuadBlock = NUM_BLOCKS,
		.numVertex = NUM_BLOCKS*9, // not really used
		.unk1 = 0, // idk, fine to leave null
		.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[0])-4,
		.ptrVertexArray = OFFSETOF(struct LevelFile, levVertex[0])-4, // no -4 for some reason?
		.unk2 = 0, // idk, fine to leave null
		.bspRoot = OFFSETOF(struct LevelFile, bsp[0])-4,
		.numBspNodes = 3, // can be anything non-zero
	},
	
	.group4_ground =
	{
		// 512_0_32_20_16_16_0.png		
		.texLayout[0] = ImageName_Blend(512, 0, 32, 20, 16, 16, 0, TRANS_50),
		.texLayout[1] = ImageName_Blend(512, 0, 32, 20, 16, 16, 0, TRANS_50),
		.texLayout[2] = ImageName_Blend(512, 0, 32, 20, 16, 16, 0, TRANS_50),
		.texLayout[3] = ImageName_Blend(512, 0, 32, 20, 16, 16, 0, TRANS_50),
	},
	
	.group4_ramp =
	{
		// 576_0_32_21_32_16_0.png		
		.texLayout[0] = ImageName_Blend(576, 0, 32, 21, 32, 16, 0, TRANS_50),
		.texLayout[1] = ImageName_Blend(576, 0, 32, 21, 32, 16, 0, TRANS_50),
		.texLayout[2] = ImageName_Blend(576, 0, 32, 21, 32, 16, 0, TRANS_50),
		.texLayout[3] = ImageName_Blend(576, 0, 32, 21, 32, 16, 0, TRANS_50),
	},
	
	.group4_ramp_flip180 =
	{
		// 576_0_32_21_32_16_0.png		
		.texLayout[0] = ImageName_Blend(576, 0, 32, 21, 32, 16, 0, TRANS_50),
		.texLayout[1] = ImageName_Blend(576, 0, 32, 21, 32, 16, 0, TRANS_50),
		.texLayout[2] = ImageName_Blend(576, 0, 32, 21, 32, 16, 0, TRANS_50),
		.texLayout[3] = ImageName_Blend(576, 0, 32, 21, 32, 16, 0, TRANS_50),
		
		.texLayout[0].v0 = 16-1,
		.texLayout[0].v1 = 16-1,
		.texLayout[0].v2 = 0,
		.texLayout[0].v3 = 0,
		
		.texLayout[1].v0 = 16-1,
		.texLayout[1].v1 = 16-1,
		.texLayout[1].v2 = 0,
		.texLayout[1].v3 = 0,
		
		.texLayout[2].v0 = 16-1,
		.texLayout[2].v1 = 16-1,
		.texLayout[2].v2 = 0,
		.texLayout[2].v3 = 0,
		
		.texLayout[3].v0 = 16-1,
		.texLayout[3].v1 = 16-1,
		.texLayout[3].v2 = 0,
		.texLayout[3].v3 = 0,
	},
	
	.texlayout_ramp_low 		= ImageName_Blend(640, 0, 32, 22, 12, 12, 0, TRANS_50),
	.texlayout_ramp_low_flipV 	= ImageName_Blend(640, 0, 32, 22, 12, 12, 0, TRANS_50),
	
	.texlayout_ramp_low_flipV.v0 = 12-1,
	.texlayout_ramp_low_flipV.v1 = 12-1,
	.texlayout_ramp_low_flipV.v2 = 0,
	.texlayout_ramp_low_flipV.v3 = 0,
	
	// this must exist, or else camera fly-in
	// checks for "count" without nullptr check,
	// and crashes dereferencing nullptr on real PSX
	.ptrSpawnType1 =
	{
		.count = 0,
	},
	
/*
	// leave this commented out
	NEW_BLOCK
	(
		0, group4_ground,	// index, texture
		0x0, 0x0			// posX, posY (size is always 0x300 x 0x300)
		NULL, 0x1800, 		// vertex flags, quadblock flags
		0xFF, 0x00, 0x00	// colorRGB
	),
*/
	
	// +z is forward
	// +x is left, not right
                                                                           NEW_BLOCK(0, group4_ground, 0x0000, 0x0000, NULL, 0x1800, 0xFF, 0x0, 0x0),NEW_BLOCK(1, group4_ground, 0x0300, 0x0000, NULL, 0x1800, 0xFF, 0x0, 0x0),                                                                           
NEW_BLOCK(2, group4_ground, -0x300, 0x0300, NULL, 0x1800, 0xFF, 0x0, 0x0),NEW_BLOCK(3, group4_ground, 0x0000, 0x0300, NULL, 0x1800, 0xFF, 0x0, 0x0),NEW_BLOCK(4, group4_ground, 0x0300, 0x0300, NULL, 0x1800, 0xFF, 0x0, 0x0),NEW_BLOCK(5, group4_ground, 0x0600, 0x0300, NULL, 0x1800, 0xFF, 0x0, 0x0),
NEW_BLOCK(6, group4_ground, -0x300, 0x0600, NULL, 0x1800, 0xFF, 0x0, 0x0),                                                                                                                                                      NEW_BLOCK(7, group4_ground, 0x0600, 0x0600, NULL, 0x1800, 0xFF, 0x0, 0x0),
NEW_BLOCK(8, group4_ground, -0x300, 0x0900, NULL, 0x1800, 0xFF, 0x0, 0x0),                                                                                                                                                      NEW_BLOCK(9, group4_ground, 0x0600, 0x0900, NULL, 0x1800, 0xFF, 0x0, 0x0),
NEW_BLOCK(10, group4_ground, -0x300, 0x0c00, NULL, 0x1800, 0xFF, 0x0, 0x0),                                                                                                                                                      NEW_BLOCK(11, group4_ground, 0x0600, 0x0c00, NULL, 0x1800, 0xFF, 0x0, 0x0),
NEW_BLOCK(12, group4_ground, -0x300, 0x0f00, NULL, 0x1800, 0xFF, 0x0, 0x0),                                                                                                                                                      NEW_BLOCK(13, group4_ground, 0x0600, 0x0f00, NULL, 0x1800, 0xFF, 0x0, 0x0),
NEW_BLOCK(14, group4_ground, -0x300, 0x1200, NULL, 0x1800, 0xFF, 0x0, 0x0),NEW_BLOCK(15, group4_ground, 0x0000, 0x1200, NULL, 0x1800, 0xFF, 0x0, 0x0),NEW_BLOCK(16, group4_ground, 0x0300, 0x1200, NULL, 0x1800, 0xFF, 0x0, 0x0),NEW_BLOCK(17, group4_ground, 0x0600, 0x1200, NULL, 0x1800, 0xFF, 0x0, 0x0),
                                                                           NEW_BLOCK(18, group4_ground, 0x0000, 0x1500, NULL, 0x1800, 0xFF, 0x0, 0x0),NEW_BLOCK(19, group4_ground, 0x0300, 0x1500, NULL, 0x1800, 0xFF, 0x0, 0x0),                                                                           

	#if 0
	
		0,1,
		3,4,
	2,			5
	6,			7
	8,			9
	10,			11
	12,			13
	14,			17
		15,16
		18,19
	
	#endif
	
	.quadBlock[2].respawnIndex = 0,
	.quadBlock[6].respawnIndex = 1,
	.quadBlock[8].respawnIndex = 2,
	.quadBlock[10].respawnIndex = 3,
	.quadBlock[12].respawnIndex = 4,
	.quadBlock[14].respawnIndex = 5,
	.quadBlock[15].respawnIndex = 6,
	.quadBlock[16].respawnIndex = 7,
	.quadBlock[17].respawnIndex = 8,
	.quadBlock[13].respawnIndex = 9,
	.quadBlock[11].respawnIndex = 10,
	.quadBlock[9].respawnIndex = 11,
	.quadBlock[7].respawnIndex = 12,
	.quadBlock[5].respawnIndex = 13,
	.quadBlock[4].respawnIndex = 14,
	.quadBlock[3].respawnIndex = 15,

	.noderespawnsthing =
	{
		[0] =
		{
			.pos = {-0x300, 0, 0x300},
			.distToFinish = 0x200*15,
			.nextIndex_forward = 1,
			.nextIndex_left = -1,
			.nextIndex_backward = 15,
			.nextIndex_right = -1,
		},
		[1] =
		{
			.pos = {-0x300, 0, 0x600},
			.distToFinish = 0x200*14,
			.nextIndex_forward = 2,
			.nextIndex_left = -1,
			.nextIndex_backward = 0,
			.nextIndex_right = -1,
		},
		[2] =
		{
			.pos = {-0x300, 0, 0x300*3},
			.distToFinish = 0x200*13,
			.nextIndex_forward = 3,
			.nextIndex_left = -1,
			.nextIndex_backward = 1,
			.nextIndex_right = -1,
		},
		[3] =
		{
			.pos = {-0x300, 0, 0x300*4},
			.distToFinish = 0x200*12,
			.nextIndex_forward = 4,
			.nextIndex_left = -1,
			.nextIndex_backward = 2,
			.nextIndex_right = -1,
		},
		[4] =
		{
			.pos = {-0x300, 0, 0x300*5},
			.distToFinish = 0x200*11,
			.nextIndex_forward = 5,
			.nextIndex_left = -1,
			.nextIndex_backward = 3,
			.nextIndex_right = -1,
		},
		[5] =
		{
			.pos = {-0x300, 0, 0x300*6},
			.distToFinish = 0x200*10,
			.nextIndex_forward = 6,
			.nextIndex_left = -1,
			.nextIndex_backward = 4,
			.nextIndex_right = -1,
		},
		[6] =
		{
			.pos = {0, 0, 0x300*6},
			.distToFinish = 0x200*9,
			.nextIndex_forward = 7,
			.nextIndex_left = -1,
			.nextIndex_backward = 5,
			.nextIndex_right = -1,
		},
		[7] =
		{
			.pos = {0x300, 0, 0x300*6},
			.distToFinish = 0x200*8,
			.nextIndex_forward = 8,
			.nextIndex_left = -1,
			.nextIndex_backward = 6,
			.nextIndex_right = -1,
		},
		[8] =
		{
			.pos = {0x600, 0, 0x300*6},
			.distToFinish = 0x200*7,
			.nextIndex_forward = 9,
			.nextIndex_left = -1,
			.nextIndex_backward = 7,
			.nextIndex_right = -1,
		},
		[9] =
		{
			.pos = {0x600, 0, 0x300*5},
			.distToFinish = 0x200*6,
			.nextIndex_forward = 10,
			.nextIndex_left = -1,
			.nextIndex_backward = 8,
			.nextIndex_right = -1,
		},
		[10] =
		{
			.pos = {0x600, 0, 0x300*4},
			.distToFinish = 0x200*5,
			.nextIndex_forward = 11,
			.nextIndex_left = -1,
			.nextIndex_backward = 9,
			.nextIndex_right = -1,
		},
		[11] =
		{
			.pos = {0x600, 0, 0x300*3},
			.distToFinish = 0x200*4,
			.nextIndex_forward = 12,
			.nextIndex_left = -1,
			.nextIndex_backward = 10,
			.nextIndex_right = -1,
		},
		[12] =
		{
			.pos = {0x600, 0, 0x300*2},
			.distToFinish = 0x200*3,
			.nextIndex_forward = 13,
			.nextIndex_left = -1,
			.nextIndex_backward = 11,
			.nextIndex_right = -1,
		},
		[13] =
		{
			.pos = {0x600, 0, 0x300*1},
			.distToFinish = 0x200*2,
			.nextIndex_forward = 14,
			.nextIndex_left = -1,
			.nextIndex_backward = 12,
			.nextIndex_right = -1,
		},
		[14] =
		{
			.pos = {0x300, 0, 0x300*1},
			.distToFinish = 0x200*1,
			.nextIndex_forward = 15,
			.nextIndex_left = -1,
			.nextIndex_backward = 13,
			.nextIndex_right = -1,
		},
		[15] =
		{
			.pos = {0, 0, 0x300*1},
			.distToFinish = 0x200*0,
			.nextIndex_forward = 0,
			.nextIndex_left = -1,
			.nextIndex_backward = 14,
			.nextIndex_right = -1,
		},
	},

	.quadBlock[0].blockID =  20-0-1,
	.quadBlock[1].blockID =  20-1-1,
	.quadBlock[2].blockID =  20-2-1,
	.quadBlock[3].blockID =  20-3-1,
	.quadBlock[4].blockID =  20-4-1,
	.quadBlock[5].blockID =  20-5-1,
	.quadBlock[6].blockID =  20-6-1,
	.quadBlock[7].blockID =  20-7-1,
	.quadBlock[8].blockID =  20-8-1,
	.quadBlock[9].blockID =  20-9-1,
	.quadBlock[10].blockID = 20-10-1,
	.quadBlock[11].blockID = 20-11-1,
	.quadBlock[12].blockID = 20-12-1,
	.quadBlock[13].blockID = 20-13-1,
	.quadBlock[14].blockID = 20-14-1,
	.quadBlock[15].blockID = 20-15-1,
	.quadBlock[16].blockID = 20-16-1,
	.quadBlock[17].blockID = 20-17-1,
	.quadBlock[18].blockID = 20-18-1,
	.quadBlock[19].blockID = 20-19-1,

	// ========== bsp ======================
	
	.bsp =
	{
		// root node
		[0] =
		{
			.flag = 0,
			.id = 0,
			.box =
			{
				.min = {-0x3000, 0xFFE4, -0x3000},
				.max = {0x3000, 0x066E, 0x3000}
			},
			
			.data =
			{
				.branch =
				{
					// need more info on this
					.axis = {0x1000, 0x0, 0x0, 0xFF40},
					
					// 0x4000 signifies leaf node
					.childID = {0x4002, 0x4001},
				}
			}
		},
		
		// leaf with nothing in it
		[1] =
		{
			.flag = 1,
			.id = 1,
			.box =
			{
				// random box that exists nowhere
				.min = {0x2800, 0xFFE4, 0x2800},
				.max = {0x2800, 0x400, 0x2F00}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = 0,
					.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[0])-4
				}
			}
		},
		
		// leaf with 1 quadblock
		[2] =
		{
			.flag = 1,
			.id = 2,
			.box =
			{
				// random box that exists nowhere
				.min = {-0x1100, 0xFFE4, -0x1100},
				.max = {0x2800, 0x400, 0x2800}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = 20,
					.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[0])-4
				}
			}
		},
	},
	
	.pvs =
	{
		.visLeafSrc = OFFSETOF(struct LevelFile, visBitIndex[0]),
		.visFaceSrc = OFFSETOF(struct LevelFile, visBitIndex[0]),
		.visInstSrc = 0,
		.visExtraSrc = 0,
	},
	
	.visBitIndex =
	{
		// all 0xFFFFFFFFFFFF
		-1, -1, -1, -1
	},
	
	.visMem =
	{
		// P1
		.visLeafList[0] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpyP1[0])-4,
		.visFaceList[0] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpyP1[4])-4,
		.bspList[0] = OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP1[0])-4,
		
		// P2
		.visLeafList[1] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpyP2[0])-4,
		.visFaceList[1] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpyP2[4])-4,
		.bspList[1] = OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP2[0])-4,
		
		// P3
		.visLeafList[2] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpyP3[0])-4,
		.visFaceList[2] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpyP3[4])-4,
		.bspList[2] = OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP3[0])-4,
		
		// P4
		.visLeafList[3] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpyP4[0])-4,
		.visFaceList[3] = OFFSETOF(struct LevelFile, VisMem_bitIndex_DstMemcpyP4[4])-4,
		.bspList[3] = OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP4[0])-4,
	},
	
	// initialize for leaf nodes only
	.VisMem_bspList_RenderListP1[2*1+1] = OFFSETOF(struct LevelFile, bsp[1])-4,
	.VisMem_bspList_RenderListP2[2*1+1] = OFFSETOF(struct LevelFile, bsp[1])-4,
	.VisMem_bspList_RenderListP3[2*1+1] = OFFSETOF(struct LevelFile, bsp[1])-4,
	.VisMem_bspList_RenderListP4[2*1+1] = OFFSETOF(struct LevelFile, bsp[1])-4,
	.VisMem_bspList_RenderListP1[2*2+1] = OFFSETOF(struct LevelFile, bsp[2])-4,
	.VisMem_bspList_RenderListP2[2*2+1] = OFFSETOF(struct LevelFile, bsp[2])-4,
	.VisMem_bspList_RenderListP3[2*2+1] = OFFSETOF(struct LevelFile, bsp[2])-4,
	.VisMem_bspList_RenderListP4[2*2+1] = OFFSETOF(struct LevelFile, bsp[2])-4,
	
	.map =
	{
		(31+NUM_BLOCKS*6)<<2,
		
		OFFSETOF(struct LevelFile, level.ptr_mesh_info)-4,
		OFFSETOF(struct LevelFile, level.visMem)-4,
		OFFSETOF(struct LevelFile, level.ptrSpawnType1)-4,
		OFFSETOF(struct LevelFile, level.ptr_restart_points)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrVertexArray)-4,
		OFFSETOF(struct LevelFile, mInfo.bspRoot)-4,
		OFFSETOF(struct LevelFile, bsp[1].data.leaf.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, bsp[2].data.leaf.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, pvs.visLeafSrc)-4,
		OFFSETOF(struct LevelFile, pvs.visFaceSrc)-4,
		OFFSETOF(struct LevelFile, visMem.visLeafList[0])-4,
		OFFSETOF(struct LevelFile, visMem.visLeafList[1])-4,
		OFFSETOF(struct LevelFile, visMem.visLeafList[2])-4,
		OFFSETOF(struct LevelFile, visMem.visLeafList[3])-4,
		OFFSETOF(struct LevelFile, visMem.visFaceList[0])-4,
		OFFSETOF(struct LevelFile, visMem.visFaceList[1])-4,
		OFFSETOF(struct LevelFile, visMem.visFaceList[2])-4,
		OFFSETOF(struct LevelFile, visMem.visFaceList[3])-4,
		OFFSETOF(struct LevelFile, visMem.bspList[0])-4,
		OFFSETOF(struct LevelFile, visMem.bspList[1])-4,
		OFFSETOF(struct LevelFile, visMem.bspList[2])-4,
		OFFSETOF(struct LevelFile, visMem.bspList[3])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP1[2*1+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP2[2*1+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP3[2*1+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP4[2*1+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP1[2*2+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP2[2*2+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP3[2*2+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP4[2*2+1])-4,
		PTR_MAP_QUADBLOCK(0),
		PTR_MAP_QUADBLOCK(1),
		PTR_MAP_QUADBLOCK(2),
		PTR_MAP_QUADBLOCK(3),
		PTR_MAP_QUADBLOCK(4),
		PTR_MAP_QUADBLOCK(5),
		PTR_MAP_QUADBLOCK(6),
		PTR_MAP_QUADBLOCK(7),
		PTR_MAP_QUADBLOCK(8),
		PTR_MAP_QUADBLOCK(9),
		PTR_MAP_QUADBLOCK(10),
		PTR_MAP_QUADBLOCK(11),
		PTR_MAP_QUADBLOCK(12),
		PTR_MAP_QUADBLOCK(13),
		PTR_MAP_QUADBLOCK(14),
		PTR_MAP_QUADBLOCK(15),
		PTR_MAP_QUADBLOCK(16),
		PTR_MAP_QUADBLOCK(17),
		PTR_MAP_QUADBLOCK(18),
		PTR_MAP_QUADBLOCK(19)
	},
};