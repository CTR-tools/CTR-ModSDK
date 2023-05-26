#include <common.h>
#include "../../levelBuilder.h"

#define NUM_BLOCKS 64

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
	struct CheckpointNode noderespawnsthing[NUM_BLOCKS]; // all empty, this is a battle map
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
		
		.DriverSpawn[1].pos = {-0xA80,0,0},
		.DriverSpawn[1].rot = {0,0-0x400,0},
		
		.DriverSpawn[2].pos = {-0xA80,0,0x1500+0xA80},
		.DriverSpawn[2].rot = {0,0x800-0x400,0},
		
		.DriverSpawn[3].pos = {0,0,0x1500+0xA80},
		.DriverSpawn[3].rot = {0,0x800-0x400,0},
		
		.ptrSpawnType1 = OFFSETOF(struct LevelFile, ptrSpawnType1)-4,
		
		.clearColor[0].rgb = {0x0, 0x0, 0x28},
		.clearColor[0].enable = 1,
		
		// only non-zero for Race maps
		// battle maps need array, but still set CNT to zero
		.cnt_restart_points = 0,
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
		.texLayout[0] = ImageName_Blend(512, 0, 32, 20, 16, 16, 0, TRANS_50), // very far
		.texLayout[1] = ImageName_Blend(512, 0, 32, 20, 16, 16, 0, TRANS_50), // far
		.texLayout[2] = ImageName_Blend(512, 0, 32, 20, 16, 16, 0, TRANS_50), // close
		.texLayout[3] = ImageName_Blend(512, 0, 32, 20, 16, 16, 0, TRANS_50), // very close
	},
	
	.group4_ramp =
	{
		// 576_0_32_21_32_16_0.png		
		.texLayout[0] = ImageName_Blend(576, 0, 32, 21, 32, 16, 0, TRANS_50), // very far
		.texLayout[1] = ImageName_Blend(576, 0, 32, 21, 32, 16, 0, TRANS_50), // far
		.texLayout[2] = ImageName_Blend(576, 0, 32, 21, 32, 16, 0, TRANS_50), // close
		.texLayout[3] = ImageName_Blend(576, 0, 32, 21, 32, 16, 0, TRANS_50), // very close
	},
	
	.group4_ramp_flip180 =
	{
		// 576_0_32_21_32_16_0.png		
		.texLayout[0] = ImageName_Blend(576, 0, 32, 21, 32, 16, 0, TRANS_50), // very far
		.texLayout[1] = ImageName_Blend(576, 0, 32, 21, 32, 16, 0, TRANS_50), // far
		.texLayout[2] = ImageName_Blend(576, 0, 32, 21, 32, 16, 0, TRANS_50), // close
		.texLayout[3] = ImageName_Blend(576, 0, 32, 21, 32, 16, 0, TRANS_50), // very close
		
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
	
	// spawn
	NEW_BLOCK(0, group4_ground, -0x180, 0, NULL, 0x1800, 0xFF, 0x0, 0x0),
	NEW_BLOCK(1, group4_ground, 0x180, 0, NULL, 0x1800, 0xFF, 0x20, 0x0),
	
	// forward
	NEW_BLOCK(2, group4_ground, -0x180, 0x300, NULL, 0x1800, 0xFF, 0x20, 0x0),
	NEW_BLOCK(3, group4_ground, 0x180, 0x300, NULL, 0x1800, 0xFF, 0x40, 0x0),
	
	// forward
	NEW_BLOCK(4, group4_ground, -0x180, 0x600, NULL, 0x1800, 0xFF, 0x40, 0x0),
	NEW_BLOCK(5, group4_ground, 0x180, 0x600, NULL, 0x1800, 0xFF, 0x60, 0x0),
	
	// forward
	NEW_BLOCK(6, group4_ground, -0x180, 0x900, NULL, 0x1800, 0xFF, 0x60, 0x0),
	NEW_BLOCK(7, group4_ground, 0x180, 0x900, NULL, 0x1800, 0xFF, 0x80, 0x0),
		
	// forward
	NEW_BLOCK(8, group4_ground, -0x180, 0xC00, NULL, 0x1800, 0xFF, 0x80, 0x0),
	NEW_BLOCK(9, group4_ground, 0x180, 0xC00, NULL, 0x1800, 0xFF, 0x80, 0x0),
	
	// right
	NEW_BLOCK(10, group4_ground, -0x480, 0x900, NULL, 0x1800, 0xFF, 0x80, 0x0),
	NEW_BLOCK(11, group4_ground, -0x480, 0xC00, NULL, 0x1800, 0, 0xFF, 0),
	
	// right
	NEW_BLOCK(12, group4_ground, -0x780, 0x900, NULL, 0x1800, 0, 0xFF, 0),
	NEW_BLOCK(13, group4_ground, -0x780, 0xC00, NULL, 0x1800, 0, 0xFF, 0x20),
	
	// right
	NEW_BLOCK(14, group4_ground, -0xA80, 0x900, NULL, 0x1800, 0, 0xFF, 0x20),
	NEW_BLOCK(15, group4_ground, -0xA80, 0xC00, NULL, 0x1800, 0, 0xFF, 0x40),
	
	// right
	NEW_BLOCK(16, group4_ground, -0xD80, 0x900, NULL, 0x1800, 0, 0xFF, 0x40),
	NEW_BLOCK(17, group4_ground, -0xD80, 0xC00, NULL, 0x1800, 0, 0xFF, 0x60),
	
	// down
	NEW_BLOCK(18, group4_ground, -0xA80, 0x600, NULL, 0x1800, 0, 0xFF, 0x60),
	NEW_BLOCK(19, group4_ground, -0xD80, 0x600, NULL, 0x1800, 0, 0xFF, 0x80),
	
	// down
	NEW_BLOCK(20, group4_ground, -0xA80, 0x300, NULL, 0x1800, 0, 0, 0xFF),
	NEW_BLOCK(21, group4_ground, -0xD80, 0x300, NULL, 0x1800, 0x20, 0, 0xFF),
	
	// down
	NEW_BLOCK(22, group4_ground, -0xA80, 0x0, NULL, 0x1800, 0x20, 0, 0xFF),
	NEW_BLOCK(23, group4_ground, -0xD80, 0x0, NULL, 0x1800, 0x40, 0, 0xFF),
	
	// left
	NEW_BLOCK(24, group4_ground, -0x780, 0, NULL, 0x1800, 0x40, 0, 0xFF),
	NEW_BLOCK(25, group4_ground, -0x780, 0x300, NULL, 0x1800, 0x60, 0, 0xFF),
	
	// left
	NEW_BLOCK(26, group4_ground, -0x480, 0, NULL, 0x1800, 0x60, 0, 0xFF),
	NEW_BLOCK(27, group4_ground, -0x480, 0x300, NULL, 0x1800, 0x80, 0, 0xFF),
	
	// ramp
	NEW_BLOCK(28, group4_ramp, -0xA80, 0xF00, NULL, 0x9800, 0x80, 0x80, 0x80), // coll (1800)
	NEW_BLOCK(29, group4_ramp, -0x180, 0xF00, NULL, 0x9800, 0x80, 0x80, 0x80), // coll (1800)
	NEW_BLOCK(30, group4_ramp, -0xA80, 0xF00, NULL, 0x1840, 0x80, 0x80, 0x80), // turbo (1840)
	NEW_BLOCK(31, group4_ramp, -0x180, 0xF00, NULL, 0x1840, 0x80, 0x80, 0x80), // turbo (1840)
		
	.quadBlock[28].draw_order_low = 0x380E000,
	.quadBlock[29].draw_order_low = 0x380E000,
	.quadBlock[30].draw_order_low = 0x380E000,
	.quadBlock[31].draw_order_low = 0x380E000,
	
	.quadBlock[28].ptr_texture_low = OFFSETOF(struct LevelFile, texlayout_ramp_low)-4,
	.quadBlock[29].ptr_texture_low = OFFSETOF(struct LevelFile, texlayout_ramp_low)-4,
	.quadBlock[30].ptr_texture_low = OFFSETOF(struct LevelFile, texlayout_ramp_low)-4,
	.quadBlock[31].ptr_texture_low = OFFSETOF(struct LevelFile, texlayout_ramp_low)-4,
	
	MAKE_RAMP(
		28, 0x100, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	MAKE_RAMP(
		29, 0x100,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	MAKE_RAMP(
		30, 0x100,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	MAKE_RAMP(
		31, 0x100,
		0,4,1,
		5,6,7,
		2,8,3
	),
		
	// turn into turbo, if flagsQ is 0x1840
	.quadBlock[30].terrain_type = 1,
	.quadBlock[31].terrain_type = 1,
	
	.quadBlock[0].blockID =  32-0-1,
	.quadBlock[1].blockID =  32-1-1,
	.quadBlock[2].blockID =  32-2-1,
	.quadBlock[3].blockID =  32-3-1,
	.quadBlock[4].blockID =  32-4-1,
	.quadBlock[5].blockID =  32-5-1,
	.quadBlock[6].blockID =  32-6-1,
	.quadBlock[7].blockID =  32-7-1,
	.quadBlock[8].blockID =  32-8-1,
	.quadBlock[9].blockID =  32-9-1,
	.quadBlock[10].blockID = 32-10-1,
	.quadBlock[11].blockID = 32-11-1,
	.quadBlock[12].blockID = 32-12-1,
	.quadBlock[13].blockID = 32-13-1,
	.quadBlock[14].blockID = 32-14-1,
	.quadBlock[15].blockID = 32-15-1,
	.quadBlock[16].blockID = 32-16-1,
	.quadBlock[17].blockID = 32-17-1,
	.quadBlock[18].blockID = 32-18-1,
	.quadBlock[19].blockID = 32-19-1,
	.quadBlock[20].blockID = 32-20-1,
	.quadBlock[21].blockID = 32-21-1,
	.quadBlock[22].blockID = 32-22-1,
	.quadBlock[23].blockID = 32-23-1,
	.quadBlock[24].blockID = 32-24-1,
	.quadBlock[25].blockID = 32-25-1,
	.quadBlock[26].blockID = 32-26-1,
	.quadBlock[27].blockID = 32-27-1,
	.quadBlock[28].blockID = 32-28-1,
	.quadBlock[29].blockID = 32-29-1,
	.quadBlock[30].blockID = 32-30-1,
	.quadBlock[31].blockID = 32-31-1,
	
	// ========== Other Side Of Map ======================
	
	// spawn
	NEW_BLOCK(32, group4_ground, -0x180, 0x1500+0, NULL, 0x1800, 0x30, 0x30, 0x30),
	NEW_BLOCK(33, group4_ground, 0x180, 0x1500+0, NULL, 0x1800, 0x60, 0x60, 0x60),
	
	// forward
	NEW_BLOCK(34, group4_ground, -0x180, 0x1500+0x300, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	NEW_BLOCK(35, group4_ground, 0x180, 0x1500+0x300, NULL, 0x1800, 0x30, 0x30, 0x30),
	
	// forward
	NEW_BLOCK(36, group4_ground, -0x180, 0x1500+0x600, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	NEW_BLOCK(37, group4_ground, 0x180, 0x1500+0x600, NULL, 0x1800, 0xD0, 0xD0, 0xD0),
	
	// forward
	NEW_BLOCK(38, group4_ground, -0x180, 0x1500+0x900, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	NEW_BLOCK(39, group4_ground, 0x180, 0x1500+0x900, NULL, 0x1800, 0x70, 0x70, 0x70),
		
	// forward
	NEW_BLOCK(40, group4_ground, -0x180, 0x1500+0xC00, NULL, 0x1800, 0x70, 0x70, 0x70),
	NEW_BLOCK(41, group4_ground, 0x180, 0x1500+0xC00, NULL, 0x1800, 0xD0, 0xD0, 0xD0),
	
	// right
	NEW_BLOCK(42, group4_ground, -0x480, 0x1500+0x900, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	NEW_BLOCK(43, group4_ground, -0x480, 0x1500+0xC00, NULL, 0x1800, 0xD0, 0xD0, 0xD0),
	
	// right
	NEW_BLOCK(44, group4_ground, -0x780, 0x1500+0x900, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	NEW_BLOCK(45, group4_ground, -0x780, 0x1500+0xC00, NULL, 0x1800, 0x40, 0x40, 0x40),
	
	// right
	NEW_BLOCK(46, group4_ground, -0xA80, 0x1500+0x900, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	NEW_BLOCK(47, group4_ground, -0xA80, 0x1500+0xC00, NULL, 0x1800, 0x70, 0x70, 0x70),
	
	// right
	NEW_BLOCK(48, group4_ground, -0xD80, 0x1500+0x900, NULL, 0x1800, 0x70, 0x70, 0x70),
	NEW_BLOCK(49, group4_ground, -0xD80, 0x1500+0xC00, NULL, 0x1800, 0xD0, 0xD0, 0xD0),
	
	// down
	NEW_BLOCK(50, group4_ground, -0xA80, 0x1500+0x600, NULL, 0x1800, 0xD0, 0xD0, 0xD0),
	NEW_BLOCK(51, group4_ground, -0xD80, 0x1500+0x600, NULL, 0x1800, 0x70, 0x70, 0x70),
	
	// down
	NEW_BLOCK(52, group4_ground, -0xA80, 0x1500+0x300, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	NEW_BLOCK(53, group4_ground, -0xD80, 0x1500+0x300, NULL, 0x1800, 0x60, 0x60, 0x60),
	
	// down
	NEW_BLOCK(54, group4_ground, -0xA80, 0x1500+0x0, NULL, 0x1800, 0x60, 0x60, 0x60),
	NEW_BLOCK(55, group4_ground, -0xD80, 0x1500+0x0, NULL, 0x1800, 0x30, 0x30, 0x30),
	
	// left
	NEW_BLOCK(56, group4_ground, -0x780, 0x1500+0, NULL, 0x1800, 0x30, 0x30, 0x30),
	NEW_BLOCK(57, group4_ground, -0x780, 0x1500+0x300, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	
	// left
	NEW_BLOCK(58, group4_ground, -0x480, 0x1500+0, NULL, 0x1800, 0x60, 0x60, 0x60),
	NEW_BLOCK(59, group4_ground, -0x480, 0x1500+0x300, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	
	// ramp
	NEW_BLOCK(60, group4_ramp_flip180, -0xA80, 0x1500-0x300, NULL, 0x9800, 0x80, 0x80, 0x80), // coll (1800)
	NEW_BLOCK(61, group4_ramp_flip180, -0x180, 0x1500-0x300, NULL, 0x9800, 0x80, 0x80, 0x80), // coll (1800)
	NEW_BLOCK(62, group4_ramp_flip180, -0xA80, 0x1500-0x300, NULL, 0x1840, 0x80, 0x80, 0x80), // turbo (1840)
	NEW_BLOCK(63, group4_ramp_flip180, -0x180, 0x1500-0x300, NULL, 0x1840, 0x80, 0x80, 0x80), // turbo (1840)
	
	.quadBlock[60].draw_order_low = 0x380E000,
	.quadBlock[61].draw_order_low = 0x380E000,
	.quadBlock[62].draw_order_low = 0x380E000,
	.quadBlock[63].draw_order_low = 0x380E000,
	
	.quadBlock[60].ptr_texture_low = OFFSETOF(struct LevelFile, texlayout_ramp_low_flipV)-4,
	.quadBlock[61].ptr_texture_low = OFFSETOF(struct LevelFile, texlayout_ramp_low_flipV)-4,
	.quadBlock[62].ptr_texture_low = OFFSETOF(struct LevelFile, texlayout_ramp_low_flipV)-4,
	.quadBlock[63].ptr_texture_low = OFFSETOF(struct LevelFile, texlayout_ramp_low_flipV)-4,
	
	MAKE_RAMP(
		60, 0x100, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		61, 0x100,
		2,8,3,
		5,6,7,
		0,4,1 
	),
	
	MAKE_RAMP(
		62, 0x100,
		2,8,3,
		5,6,7,
		0,4,1 
	),
	
	MAKE_RAMP(
		63, 0x100,
		2,8,3,
		5,6,7,
		0,4,1 
	),
		
	// turn into turbo, if flagsQ is 0x1840
	.quadBlock[62].terrain_type = 1,
	.quadBlock[63].terrain_type = 1,
	
	.quadBlock[32].blockID = 64-0-1,
	.quadBlock[33].blockID = 64-1-1,
	.quadBlock[34].blockID = 64-2-1,
	.quadBlock[35].blockID = 64-3-1,
	.quadBlock[36].blockID = 64-4-1,
	.quadBlock[37].blockID = 64-5-1,
	.quadBlock[38].blockID = 64-6-1,
	.quadBlock[39].blockID = 64-7-1,
	.quadBlock[40].blockID = 64-8-1,
	.quadBlock[41].blockID = 64-9-1,
	.quadBlock[42].blockID = 64-10-1,
	.quadBlock[43].blockID = 64-11-1,
	.quadBlock[44].blockID = 64-12-1,
	.quadBlock[45].blockID = 64-13-1,
	.quadBlock[46].blockID = 64-14-1,
	.quadBlock[47].blockID = 64-15-1,
	.quadBlock[48].blockID = 64-16-1,
	.quadBlock[49].blockID = 64-17-1,
	.quadBlock[50].blockID = 64-18-1,
	.quadBlock[51].blockID = 64-19-1,
	.quadBlock[52].blockID = 64-20-1,
	.quadBlock[53].blockID = 64-21-1,
	.quadBlock[54].blockID = 64-22-1,
	.quadBlock[55].blockID = 64-23-1,
	.quadBlock[56].blockID = 64-24-1,
	.quadBlock[57].blockID = 64-25-1,
	.quadBlock[58].blockID = 64-26-1,
	.quadBlock[59].blockID = 64-27-1,
	.quadBlock[60].blockID = 64-28-1,
	.quadBlock[61].blockID = 64-29-1,
	.quadBlock[62].blockID = 64-30-1,
	.quadBlock[63].blockID = 64-31-1,
	
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
				.min = {-0x1100, 0xFFE4, 0x1100},
				.max = {0x1100, 0x400, 0x2500}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = 32,
					.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[32])-4
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
				.max = {0x1100, 0x400, 0x1100}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = 32,
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
		PTR_MAP_QUADBLOCK(19),
		PTR_MAP_QUADBLOCK(20),
		PTR_MAP_QUADBLOCK(21),
		PTR_MAP_QUADBLOCK(22),
		PTR_MAP_QUADBLOCK(23),
		PTR_MAP_QUADBLOCK(24),
		PTR_MAP_QUADBLOCK(25),
		PTR_MAP_QUADBLOCK(26),
		PTR_MAP_QUADBLOCK(27),
		PTR_MAP_QUADBLOCK(28),
		PTR_MAP_QUADBLOCK(29),
		PTR_MAP_QUADBLOCK(30),
		PTR_MAP_QUADBLOCK(31),
		PTR_MAP_QUADBLOCK(32),
		PTR_MAP_QUADBLOCK(33),
		PTR_MAP_QUADBLOCK(34),
		PTR_MAP_QUADBLOCK(35),
		PTR_MAP_QUADBLOCK(36),
		PTR_MAP_QUADBLOCK(37),
		PTR_MAP_QUADBLOCK(38),
		PTR_MAP_QUADBLOCK(39),
		PTR_MAP_QUADBLOCK(40),
		PTR_MAP_QUADBLOCK(41),
		PTR_MAP_QUADBLOCK(42),
		PTR_MAP_QUADBLOCK(43),
		PTR_MAP_QUADBLOCK(44),
		PTR_MAP_QUADBLOCK(45),
		PTR_MAP_QUADBLOCK(46),
		PTR_MAP_QUADBLOCK(47),
		PTR_MAP_QUADBLOCK(48),
		PTR_MAP_QUADBLOCK(49),
		PTR_MAP_QUADBLOCK(50),
		PTR_MAP_QUADBLOCK(51),
		PTR_MAP_QUADBLOCK(52),
		PTR_MAP_QUADBLOCK(53),
		PTR_MAP_QUADBLOCK(54),
		PTR_MAP_QUADBLOCK(55),
		PTR_MAP_QUADBLOCK(56),
		PTR_MAP_QUADBLOCK(57),
		PTR_MAP_QUADBLOCK(58),
		PTR_MAP_QUADBLOCK(59),
		PTR_MAP_QUADBLOCK(60),
		PTR_MAP_QUADBLOCK(61),
		PTR_MAP_QUADBLOCK(62),
		PTR_MAP_QUADBLOCK(63)
	},
};
