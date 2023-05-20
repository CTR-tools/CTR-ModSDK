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

#define NEW_BLOCK(qIndex, posX, posZ, flagV, flagQ, colR, colG, colB) \
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
		.visFromQuadBlock = OFFSETOF(struct LevelFile, visFromQuadBlock)-4, \
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

#define PTR_MAP_QUADBLOCK(x) \
	OFFSETOF(struct LevelFile, quadBlock[x].ptr_texture_mid[0])-4,\
	OFFSETOF(struct LevelFile, quadBlock[x].ptr_texture_mid[1])-4,\
	OFFSETOF(struct LevelFile, quadBlock[x].ptr_texture_mid[2])-4,\
	OFFSETOF(struct LevelFile, quadBlock[x].ptr_texture_mid[3])-4,\
	OFFSETOF(struct LevelFile, quadBlock[x].ptr_texture_low)-4,\
	OFFSETOF(struct LevelFile, quadBlock[x].visFromQuadBlock)-4

#define NUM_BLOCKS 64

struct LevelFile
{
	void* ptrMap;
	struct Level level;
	struct mesh_info mInfo;
	struct IconGroup4 group4;
	struct SpawnType1 ptrSpawnType1;
	struct QuadBlock quadBlock[NUM_BLOCKS];
	struct LevVertex levVertex[NUM_BLOCKS*9];
	struct VisData visData[3];
	struct VisFromQuadBlock visFromQuadBlock;
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
	
	int map[1000];
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
		
		.DriverSpawn[1].pos = {0,0,0xA80},
		.DriverSpawn[1].rot = {0,0xC00-0x400,0},
		
		.DriverSpawn[2].pos = {-0xA80,0,0xA80},
		.DriverSpawn[2].rot = {0,0x800-0x400,0},
		
		.DriverSpawn[3].pos = {-0xA80,0,0},
		.DriverSpawn[3].rot = {0,0x400-0x400,0},
		
		.ptrSpawnType1 = OFFSETOF(struct LevelFile, ptrSpawnType1)-4
	},
	
	.mInfo =
	{
		.numQuadBlock = NUM_BLOCKS,
		.numVertex = NUM_BLOCKS*9, // not really used
		.unk1 = 0, // idk, fine to leave null
		.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[0])-4,
		.ptrVertexArray = OFFSETOF(struct LevelFile, levVertex[0])-4, // no -4 for some reason?
		.unk2 = 0, // idk, fine to leave null
		.ptrVisDataArray = OFFSETOF(struct LevelFile, visData[0])-4,
		.numVisData = 3, // can be anything non-zero
	},
	
	// A quadblock can draw 32 textures,
	.group4 =
	{
		// duplicate for low LOD
		.texLayout[0] = 
		{
			.clut = (512 >> 10) | (0 >> 6),
			.tpage = 0x4180 | (8) | (0<<4),
			.u0 = 3, .v0 = 1,
			.u1 = 3, .v1 = 3,
			.u2 = 1, .v2 = 1,
			.u3 = 1, .v3 = 3,	
		},

		// duplicate for low LOD
		.texLayout[1] = 
		{
			.clut = (512 >> 10) | (0 >> 6),
			.tpage = 0x4180 | (8) | (0<<4),
			.u0 = 3, .v0 = 1,
			.u1 = 3, .v1 = 3,
			.u2 = 1, .v2 = 1,
			.u3 = 1, .v3 = 3,	
		},
		
		// duplicate for low LOD
		.texLayout[2] = 
		{
			.clut = (512 >> 10) | (0 >> 6),
			.tpage = 0x4180 | (8) | (0<<4),
			.u0 = 3, .v0 = 1,
			.u1 = 3, .v1 = 3,
			.u2 = 1, .v2 = 1,
			.u3 = 1, .v3 = 3,	
		},
		
		// drawn directly under player
		.texLayout[3] = 
		{
			// Change since first custom level,
			// dont use 512,256, use 512,0,
			// because DecalMP overwrites 512,256
			
			// X(b6) Y(b10)
			// row of 16 pixels, or row of 256 pixels,
			// this is how it chooses what colors to use
			.clut = (512 >> 10) | (0 >> 6), // was 256>>6 for 512,256
			
			// each page is 256x256 large
			
			// pageX(b4), 
			// pageY(b1), 
			// blending(b2), 
			// bitDepth(b2), 
			// restBits(b7)
			.tpage = 0x4180 | (8) | (0<<4), // page = (2,1) (512,0) ------- 1<<4 was 512,256
			
			// coordinates within page
			.u0 = 3, .v0 = 1,
			.u1 = 3, .v1 = 3,
			.u2 = 1, .v2 = 1,
			.u3 = 1, .v3 = 3,			
		},
	},
	
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
		0, 					// index
		0x0, 0x0			// posX, posY (size is always 0x300 x 0x300)
		NULL, 0x1800, 		// vertex flags, quadblock flags
		0xFF, 0x00, 0x00	// colorRGB
	),
*/
	
	// +z is forward
	// +x is left, not right
	
	// spawn
	NEW_BLOCK(0, -0x180, 0, NULL, 0x1800, 0xFF, 0x0, 0x0),
	NEW_BLOCK(1, 0x180, 0, NULL, 0x1800, 0xFF, 0x20, 0x0),
	
	// forward
	NEW_BLOCK(2, -0x180, 0x300, NULL, 0x1800, 0xFF, 0x20, 0x0),
	NEW_BLOCK(3, 0x180, 0x300, NULL, 0x1800, 0xFF, 0x40, 0x0),
	
	// forward
	NEW_BLOCK(4, -0x180, 0x600, NULL, 0x1800, 0xFF, 0x40, 0x0),
	NEW_BLOCK(5, 0x180, 0x600, NULL, 0x1800, 0xFF, 0x60, 0x0),
	
	// forward
	NEW_BLOCK(6, -0x180, 0x900, NULL, 0x1800, 0xFF, 0x60, 0x0),
	NEW_BLOCK(7, 0x180, 0x900, NULL, 0x1800, 0xFF, 0x80, 0x0),
		
	// forward
	NEW_BLOCK(8, -0x180, 0xC00, NULL, 0x1800, 0xFF, 0x80, 0x0),
	NEW_BLOCK(9, 0x180, 0xC00, NULL, 0x1800, 0xFF, 0x80, 0x0),
	
	// right
	NEW_BLOCK(10, -0x480, 0x900, NULL, 0x1800, 0xFF, 0x80, 0x0),
	NEW_BLOCK(11, -0x480, 0xC00, NULL, 0x1800, 0, 0xFF, 0),
	
	// right
	NEW_BLOCK(12, -0x780, 0x900, NULL, 0x1800, 0, 0xFF, 0),
	NEW_BLOCK(13, -0x780, 0xC00, NULL, 0x1800, 0, 0xFF, 0x20),
	
	// right
	NEW_BLOCK(14, -0xA80, 0x900, NULL, 0x1800, 0, 0xFF, 0x20),
	NEW_BLOCK(15, -0xA80, 0xC00, NULL, 0x1800, 0, 0xFF, 0x40),
	
	// right
	NEW_BLOCK(16, -0xD80, 0x900, NULL, 0x1800, 0, 0xFF, 0x40),
	NEW_BLOCK(17, -0xD80, 0xC00, NULL, 0x1800, 0, 0xFF, 0x60),
	
	// down
	NEW_BLOCK(18, -0xA80, 0x600, NULL, 0x1800, 0, 0xFF, 0x60),
	NEW_BLOCK(19, -0xD80, 0x600, NULL, 0x1800, 0, 0xFF, 0x80),
	
	// down
	NEW_BLOCK(20, -0xA80, 0x300, NULL, 0x1800, 0, 0, 0xFF),
	NEW_BLOCK(21, -0xD80, 0x300, NULL, 0x1800, 0x20, 0, 0xFF),
	
	// down
	NEW_BLOCK(22, -0xA80, 0x0, NULL, 0x1800, 0x20, 0, 0xFF),
	NEW_BLOCK(23, -0xD80, 0x0, NULL, 0x1800, 0x40, 0, 0xFF),
	
	// left
	NEW_BLOCK(24, -0x780, 0, NULL, 0x1800, 0x40, 0, 0xFF),
	NEW_BLOCK(25, -0x780, 0x300, NULL, 0x1800, 0x60, 0, 0xFF),
	
	// left
	NEW_BLOCK(26, -0x480, 0, NULL, 0x1800, 0x60, 0, 0xFF),
	NEW_BLOCK(27, -0x480, 0x300, NULL, 0x1800, 0x80, 0, 0xFF),
	
	// ramp
	NEW_BLOCK(28, -0xA80, 0xF00, NULL, 0x1800, 0xFF, 0xFF, 0xFF), // coll (1800)
	NEW_BLOCK(29, -0x180, 0xF00, NULL, 0x1800, 0xFF, 0xFF, 0xFF), // coll (1800)
	NEW_BLOCK(30, -0xA80, 0xF00, NULL, 0x1840, 0xFF, 0xFF, 0xFF), // turbo (1840)
	NEW_BLOCK(31, -0x180, 0xF00, NULL, 0x1840, 0xFF, 0xFF, 0xFF), // turbo (1840)
	
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
	NEW_BLOCK(32, -0x180, 0x1500+0, NULL, 0x1800, 0x30, 0x30, 0x30),
	NEW_BLOCK(33, 0x180, 0x1500+0, NULL, 0x1800, 0x60, 0x60, 0x60),
	
	// forward
	NEW_BLOCK(34, -0x180, 0x1500+0x300, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	NEW_BLOCK(35, 0x180, 0x1500+0x300, NULL, 0x1800, 0x30, 0x30, 0x30),
	
	// forward
	NEW_BLOCK(36, -0x180, 0x1500+0x600, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	NEW_BLOCK(37, 0x180, 0x1500+0x600, NULL, 0x1800, 0xD0, 0xD0, 0xD0),
	
	// forward
	NEW_BLOCK(38, -0x180, 0x1500+0x900, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	NEW_BLOCK(39, 0x180, 0x1500+0x900, NULL, 0x1800, 0x70, 0x70, 0x70),
		
	// forward
	NEW_BLOCK(40, -0x180, 0x1500+0xC00, NULL, 0x1800, 0x70, 0x70, 0x70),
	NEW_BLOCK(41, 0x180, 0x1500+0xC00, NULL, 0x1800, 0xD0, 0xD0, 0xD0),
	
	// right
	NEW_BLOCK(42, -0x480, 0x1500+0x900, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	NEW_BLOCK(43, -0x480, 0x1500+0xC00, NULL, 0x1800, 0xD0, 0xD0, 0xD0),
	
	// right
	NEW_BLOCK(44, -0x780, 0x1500+0x900, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	NEW_BLOCK(45, -0x780, 0x1500+0xC00, NULL, 0x1800, 0x40, 0x40, 0x40),
	
	// right
	NEW_BLOCK(46, -0xA80, 0x1500+0x900, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	NEW_BLOCK(47, -0xA80, 0x1500+0xC00, NULL, 0x1800, 0x70, 0x70, 0x70),
	
	// right
	NEW_BLOCK(48, -0xD80, 0x1500+0x900, NULL, 0x1800, 0x70, 0x70, 0x70),
	NEW_BLOCK(49, -0xD80, 0x1500+0xC00, NULL, 0x1800, 0xD0, 0xD0, 0xD0),
	
	// down
	NEW_BLOCK(50, -0xA80, 0x1500+0x600, NULL, 0x1800, 0xD0, 0xD0, 0xD0),
	NEW_BLOCK(51, -0xD80, 0x1500+0x600, NULL, 0x1800, 0x70, 0x70, 0x70),
	
	// down
	NEW_BLOCK(52, -0xA80, 0x1500+0x300, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	NEW_BLOCK(53, -0xD80, 0x1500+0x300, NULL, 0x1800, 0x60, 0x60, 0x60),
	
	// down
	NEW_BLOCK(54, -0xA80, 0x1500+0x0, NULL, 0x1800, 0x60, 0x60, 0x60),
	NEW_BLOCK(55, -0xD80, 0x1500+0x0, NULL, 0x1800, 0x30, 0x30, 0x30),
	
	// left
	NEW_BLOCK(56, -0x780, 0x1500+0, NULL, 0x1800, 0x30, 0x30, 0x30),
	NEW_BLOCK(57, -0x780, 0x1500+0x300, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	
	// left
	NEW_BLOCK(58, -0x480, 0x1500+0, NULL, 0x1800, 0x60, 0x60, 0x60),
	NEW_BLOCK(59, -0x480, 0x1500+0x300, NULL, 0x1800, 0xFF, 0xFF, 0xFF),
	
	// ramp
	NEW_BLOCK(60, -0xA80, 0x1500-0x300, NULL, 0x1800, 0xFF, 0xFF, 0xFF), // coll (1800)
	NEW_BLOCK(61, -0x180, 0x1500-0x300, NULL, 0x1800, 0xFF, 0xFF, 0xFF), // coll (1800)
	NEW_BLOCK(62, -0xA80, 0x1500-0x300, NULL, 0x1840, 0xFF, 0xFF, 0xFF), // turbo (1840)
	NEW_BLOCK(63, -0x180, 0x1500-0x300, NULL, 0x1840, 0xFF, 0xFF, 0xFF), // turbo (1840)
	
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
	
	// ========== VisData ======================
	
	.visData =
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
					.ptrVisDataArray_InstHitboxes = 0,
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
					.ptrVisDataArray_InstHitboxes = 0,
					.numQuads = 32,
					.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[0])-4
				}
			}
		},
	},
	
	.visFromQuadBlock =
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
	.VisMem_bspList_RenderListP1[2*1+1] = OFFSETOF(struct LevelFile, visData[1])-4,
	.VisMem_bspList_RenderListP2[2*1+1] = OFFSETOF(struct LevelFile, visData[1])-4,
	.VisMem_bspList_RenderListP3[2*1+1] = OFFSETOF(struct LevelFile, visData[1])-4,
	.VisMem_bspList_RenderListP4[2*1+1] = OFFSETOF(struct LevelFile, visData[1])-4,
	.VisMem_bspList_RenderListP1[2*2+1] = OFFSETOF(struct LevelFile, visData[2])-4,
	.VisMem_bspList_RenderListP2[2*2+1] = OFFSETOF(struct LevelFile, visData[2])-4,
	.VisMem_bspList_RenderListP3[2*2+1] = OFFSETOF(struct LevelFile, visData[2])-4,
	.VisMem_bspList_RenderListP4[2*2+1] = OFFSETOF(struct LevelFile, visData[2])-4,
	
	.map =
	{
		(30+NUM_BLOCKS*6)<<2,
		
		OFFSETOF(struct LevelFile, level.ptr_mesh_info)-4,
		OFFSETOF(struct LevelFile, level.visMem)-4,
		OFFSETOF(struct LevelFile, level.ptrSpawnType1)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrVertexArray)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrVisDataArray)-4,
		OFFSETOF(struct LevelFile, visData[1].data.leaf.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, visData[2].data.leaf.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, visFromQuadBlock.visLeafSrc)-4,
		OFFSETOF(struct LevelFile, visFromQuadBlock.visFaceSrc)-4,
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
