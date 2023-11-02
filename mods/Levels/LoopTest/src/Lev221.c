// Only for generating LEV files
#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Woverride-init"
#pragma GCC diagnostic ignored "-Woverflow"

#include <common.h>
#include "../../levelBuilder.h"

#define NUM_BLOCKS 66

struct LevelFile
{
	void* ptrMap;
	struct Level level;
	struct mesh_info mInfo;
	
	// NonScroll "High" textures
	struct IconGroup4 group4_ground;
	
	// SpawnData
	struct SpawnType1 ptrSpawnType1;
	
	// Geometry
	struct QuadBlock quadBlock[NUM_BLOCKS];
	struct LevVertex levVertex[NUM_BLOCKS*9];
	
	// Checkpoints
	struct CheckpointNode noderespawnsthing[NUM_BLOCKS]; // all empty, this is a battle map
	
	// Visibility
	struct BSP bsp[3];
	struct PVS pvs;
	int visBitIndex[4];
	struct VisMem visMem;
	
	// leave empty
	// DstMemcpy must be big for PVS to copy into,
	// RenderList must be big enough for 2 pointers to all BSP nodes
	int VisMem_bitIndex_DstMemcpyP1[8];
	int VisMem_bspList_RenderListP1[3*2];
	int VisMem_bitIndex_DstMemcpyP2[8];
	int VisMem_bspList_RenderListP2[3*2];
	int VisMem_bitIndex_DstMemcpyP3[8];
	int VisMem_bspList_RenderListP3[3*2];
	int VisMem_bitIndex_DstMemcpyP4[8];
	int VisMem_bspList_RenderListP4[3*2];
	
	int map[3];
};

struct LevelFile file =
{
	.ptrMap = LEV_OFFSETOF(map[0]),
	
	.level =
	{
		.ptr_mesh_info = LEV_OFFSETOF(mInfo),
		.visMem = LEV_OFFSETOF(visMem),
		
		// the game will add +0x400 to the yaw of spawn positions automatically
		// we should probably look into why this even happens...
		.DriverSpawn[0].pos = {0,0,0},
		.DriverSpawn[0].rot = {0,0-0x400,0},
		
		.DriverSpawn[1].pos = {-0xA80,0,0},
		.DriverSpawn[1].rot = {0,0-0x400,0},
		
		.DriverSpawn[2].pos = {-0xA80,0,0x1500+0xA80},
		.DriverSpawn[2].rot = {0,0x800-0x400,0},
		
		.DriverSpawn[3].pos = {0,0,0x1500+0xA80},
		.DriverSpawn[3].rot = {0,0x800-0x400,0},
		
		.ptrSpawnType1 = LEV_OFFSETOF(ptrSpawnType1),
		
		.clearColor[0].rgb = {0x0, 0x0, 0x28},
		.clearColor[0].enable = 1,
		
		// only non-zero for Race maps
		// battle maps need array, but still set CNT to zero
		.cnt_restart_points = 0,
		.ptr_restart_points = LEV_OFFSETOF(noderespawnsthing[0]),
	},
	
	.mInfo =
	{
		.numQuadBlock = NUM_BLOCKS,
		.numVertex = NUM_BLOCKS*9, // not really used
		.unk1 = 0, // idk, fine to leave null
		.ptrQuadBlockArray = LEV_OFFSETOF(quadBlock[0]),
		.ptrVertexArray = LEV_OFFSETOF(levVertex[0]),
		.unk2 = 0, // idk, fine to leave null
		.bspRoot = LEV_OFFSETOF(bsp[0]),
		.numBspNodes = 3, // can be anything non-zero
	},
	
	.group4_ground =
	{
		// 512_0_32_20_16_16_0.png		
		.far    = ImageName_Blend(512, 0, 32, 20, 16, 16, BPP_4, TRANS_50), // very far
		.middle = ImageName_Blend(512, 0, 32, 20, 16, 16, BPP_4, TRANS_50), // far
		.near   = ImageName_Blend(512, 0, 32, 20, 16, 16, BPP_4, TRANS_50), // close
		.mosaic = ImageName_Blend(512, 0, 32, 20, 16, 16, BPP_4, TRANS_50), // very close
	},
	
	// this must exist, or else camera fly-in
	// checks for "count" without nullptr check,
	// and crashes dereferencing nullptr on real PSX
	.ptrSpawnType1 =
	{
		.count = 0,
	},
	
	// +z is forward
	// +x is left, not right
	
	// spawn
	NEW_BLOCK(0, group4_ground, -0x180, 0, NULL, 0x1800, RGBtoBGR(0xFF0000)),
	NEW_BLOCK(1, group4_ground, 0x180, 0, NULL, 0x1800, RGBtoBGR(0xFF2000)),
	
	// forward
	NEW_BLOCK(2, group4_ground, -0x180, 0x300, NULL, 0x1800, RGBtoBGR(0xFF2000)),
	NEW_BLOCK(3, group4_ground, 0x180, 0x300, NULL, 0x1800, RGBtoBGR(0xFF4000)),
	
	// forward
	NEW_BLOCK(4, group4_ground, -0x180, 0x600, NULL, 0x1880, RGBtoBGR(0xFF4000)),
	NEW_BLOCK(5, group4_ground, 0x180, 0x600, NULL, 0x1880, RGBtoBGR(0xFF6000)),
	
	// ====== Start Ramp =========
	
	MAKE_RAMP(
		4, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	MAKE_RAMP(
		5, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	.levVertex[9*4+5].pos[1] = 0xC0,
	.levVertex[9*4+6].pos[1] = 0xC0,
	.levVertex[9*4+7].pos[1] = 0xC0,
	
	.levVertex[9*5+5].pos[1] = 0xC0,
	.levVertex[9*5+6].pos[1] = 0xC0,
	.levVertex[9*5+7].pos[1] = 0xC0,
	
	.levVertex[9*4+2].pos[1] = 0x240,
	.levVertex[9*4+8].pos[1] = 0x240,
	.levVertex[9*4+3].pos[1] = 0x240,
	
	.levVertex[9*5+2].pos[1] = 0x240,
	.levVertex[9*5+8].pos[1] = 0x240,
	.levVertex[9*5+3].pos[1] = 0x240,
	
	// ======== Wall ==========
	
	// forward
	// do NOT set Z, cause it'll overwrite in a few lines
	NEW_BLOCK(6, group4_ground, -0x180, 0, NULL, 0x1880, RGBtoBGR(0xFF6000)),
	NEW_BLOCK(7, group4_ground, 0x180, 0, NULL, 0x1880, RGBtoBGR(0xFF8000)),
	
	MAKE_RAMP(
		6, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	MAKE_RAMP(
		7, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	SET_POSY_RAMP(
		6, 0x240, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	SET_POSY_RAMP(
		7, 0x240, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	.levVertex[9*6+0].pos[2] = 0x780,
	.levVertex[9*6+4].pos[2] = 0x780,
	.levVertex[9*6+1].pos[2] = 0x780,
	.levVertex[9*6+5].pos[2] = 0x7E0,
	.levVertex[9*6+6].pos[2] = 0x7E0,
	.levVertex[9*6+7].pos[2] = 0x7E0,
	.levVertex[9*6+2].pos[2] = 0x840,
	.levVertex[9*6+8].pos[2] = 0x840,
	.levVertex[9*6+3].pos[2] = 0x840,
	
	.levVertex[9*7+0].pos[2] = 0x780,
	.levVertex[9*7+4].pos[2] = 0x780,
	.levVertex[9*7+1].pos[2] = 0x780,
	.levVertex[9*7+5].pos[2] = 0x7E0,
	.levVertex[9*7+6].pos[2] = 0x7E0,
	.levVertex[9*7+7].pos[2] = 0x7E0,
	.levVertex[9*7+2].pos[2] = 0x840,
	.levVertex[9*7+8].pos[2] = 0x840,
	.levVertex[9*7+3].pos[2] = 0x840,
	
	// forward
	// do NOT set Z, cause it'll overwrite in a few lines
	NEW_BLOCK(8, group4_ground, -0x180, 0, NULL, 0x1880, RGBtoBGR(0xFF8000)),
	NEW_BLOCK(9, group4_ground, 0x180, 0, NULL, 0x1880, RGBtoBGR(0xFF8000)),

	MAKE_RAMP(
		8, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	MAKE_RAMP(
		9, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	SET_POSY_RAMP(
		8, 0x540, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	SET_POSY_RAMP(
		9, 0x540, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	.levVertex[9*8+0].pos[2] = 0x840,
	.levVertex[9*8+4].pos[2] = 0x840,
	.levVertex[9*8+1].pos[2] = 0x840,
	.levVertex[9*8+5].pos[2] = 0x8A0,
	.levVertex[9*8+6].pos[2] = 0x8A0,
	.levVertex[9*8+7].pos[2] = 0x8A0,
	.levVertex[9*8+2].pos[2] = 0x900,
	.levVertex[9*8+8].pos[2] = 0x900,
	.levVertex[9*8+3].pos[2] = 0x900,
	
	.levVertex[9*9+0].pos[2] = 0x840,
	.levVertex[9*9+4].pos[2] = 0x840,
	.levVertex[9*9+1].pos[2] = 0x840,
	.levVertex[9*9+5].pos[2] = 0x8A0,
	.levVertex[9*9+6].pos[2] = 0x8A0,
	.levVertex[9*9+7].pos[2] = 0x8A0,
	.levVertex[9*9+2].pos[2] = 0x900,
	.levVertex[9*9+8].pos[2] = 0x900,
	.levVertex[9*9+3].pos[2] = 0x900,
	
	// right
	NEW_BLOCK(10, group4_ground, -0x480, 0, NULL, 0x1800, RGBtoBGR(0xFF8000)),
	NEW_BLOCK(11, group4_ground, -0x780, 0, NULL, 0x1800, RGBtoBGR(0x00FF00)),
	
	MAKE_RAMP(
		10, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	MAKE_RAMP(
		11, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	SET_POSY_RAMP(
		10, 0x240, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	SET_POSY_RAMP(
		11, 0x240, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	.levVertex[9*10+0].pos[2] = 0x780,
	.levVertex[9*10+4].pos[2] = 0x780,
	.levVertex[9*10+1].pos[2] = 0x780,
	.levVertex[9*10+5].pos[2] = 0x7E0,
	.levVertex[9*10+6].pos[2] = 0x7E0,
	.levVertex[9*10+7].pos[2] = 0x7E0,
	.levVertex[9*10+2].pos[2] = 0x840,
	.levVertex[9*10+8].pos[2] = 0x840,
	.levVertex[9*10+3].pos[2] = 0x840,
	
	.levVertex[9*11+0].pos[2] = 0x780,
	.levVertex[9*11+4].pos[2] = 0x780,
	.levVertex[9*11+1].pos[2] = 0x780,
	.levVertex[9*11+5].pos[2] = 0x7E0,
	.levVertex[9*11+6].pos[2] = 0x7E0,
	.levVertex[9*11+7].pos[2] = 0x7E0,
	.levVertex[9*11+2].pos[2] = 0x840,
	.levVertex[9*11+8].pos[2] = 0x840,
	.levVertex[9*11+3].pos[2] = 0x840,
	
	// right
	NEW_BLOCK(12, group4_ground, -0x480, 0, NULL, 0x1800, RGBtoBGR(0x00FF00)),
	NEW_BLOCK(13, group4_ground, -0x780, 0, NULL, 0x1800, RGBtoBGR(0x00FF20)),
	
	MAKE_RAMP(
		12, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	MAKE_RAMP(
		13, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	SET_POSY_RAMP(
		12, 0x540, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	SET_POSY_RAMP(
		13, 0x540, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	.levVertex[9*12+0].pos[2] = 0x840,
	.levVertex[9*12+4].pos[2] = 0x840,
	.levVertex[9*12+1].pos[2] = 0x840,
	.levVertex[9*12+5].pos[2] = 0x8A0,
	.levVertex[9*12+6].pos[2] = 0x8A0,
	.levVertex[9*12+7].pos[2] = 0x8A0,
	.levVertex[9*12+2].pos[2] = 0x900,
	.levVertex[9*12+8].pos[2] = 0x900,
	.levVertex[9*12+3].pos[2] = 0x900,
	
	.levVertex[9*13+0].pos[2] = 0x840,
	.levVertex[9*13+4].pos[2] = 0x840,
	.levVertex[9*13+1].pos[2] = 0x840,
	.levVertex[9*13+5].pos[2] = 0x8A0,
	.levVertex[9*13+6].pos[2] = 0x8A0,
	.levVertex[9*13+7].pos[2] = 0x8A0,
	.levVertex[9*13+2].pos[2] = 0x900,
	.levVertex[9*13+8].pos[2] = 0x900,
	.levVertex[9*13+3].pos[2] = 0x900,
	
	// right
	NEW_BLOCK(14, group4_ground, -0xA80, 0x900, NULL, 0x1800, RGBtoBGR(0x00FF20)),
	NEW_BLOCK(15, group4_ground, -0xD80, 0xC00, NULL, 0x1800, RGBtoBGR(0x00FF40)),
	
	MAKE_RAMP(
		14, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	MAKE_RAMP(
		15, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	SET_POSY_RAMP(
		14, 0x240, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	SET_POSY_RAMP(
		15, 0x240, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	.levVertex[9*14+0].pos[2] = 0x780,
	.levVertex[9*14+4].pos[2] = 0x780,
	.levVertex[9*14+1].pos[2] = 0x780,
	.levVertex[9*14+5].pos[2] = 0x7E0,
	.levVertex[9*14+6].pos[2] = 0x7E0,
	.levVertex[9*14+7].pos[2] = 0x7E0,
	.levVertex[9*14+2].pos[2] = 0x840,
	.levVertex[9*14+8].pos[2] = 0x840,
	.levVertex[9*14+3].pos[2] = 0x840,
	
	.levVertex[9*15+0].pos[2] = 0x780,
	.levVertex[9*15+4].pos[2] = 0x780,
	.levVertex[9*15+1].pos[2] = 0x780,
	.levVertex[9*15+5].pos[2] = 0x7E0,
	.levVertex[9*15+6].pos[2] = 0x7E0,
	.levVertex[9*15+7].pos[2] = 0x7E0,
	.levVertex[9*15+2].pos[2] = 0x840,
	.levVertex[9*15+8].pos[2] = 0x840,
	.levVertex[9*15+3].pos[2] = 0x840,
	
	// right
	NEW_BLOCK(16, group4_ground, -0xA80, 0x900, NULL, 0x1800, RGBtoBGR(0x00FF40)),
	NEW_BLOCK(17, group4_ground, -0xD80, 0xC00, NULL, 0x1800, RGBtoBGR(0x00FF60)),
	
	MAKE_RAMP(
		16, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	MAKE_RAMP(
		17, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	SET_POSY_RAMP(
		16, 0x540, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	SET_POSY_RAMP(
		17, 0x540, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	.levVertex[9*16+0].pos[2] = 0x840,
	.levVertex[9*16+4].pos[2] = 0x840,
	.levVertex[9*16+1].pos[2] = 0x840,
	.levVertex[9*16+5].pos[2] = 0x8A0,
	.levVertex[9*16+6].pos[2] = 0x8A0,
	.levVertex[9*16+7].pos[2] = 0x8A0,
	.levVertex[9*16+2].pos[2] = 0x900,
	.levVertex[9*16+8].pos[2] = 0x900,
	.levVertex[9*16+3].pos[2] = 0x900,
	
	.levVertex[9*17+0].pos[2] = 0x840,
	.levVertex[9*17+4].pos[2] = 0x840,
	.levVertex[9*17+1].pos[2] = 0x840,
	.levVertex[9*17+5].pos[2] = 0x8A0,
	.levVertex[9*17+6].pos[2] = 0x8A0,
	.levVertex[9*17+7].pos[2] = 0x8A0,
	.levVertex[9*17+2].pos[2] = 0x900,
	.levVertex[9*17+8].pos[2] = 0x900,
	.levVertex[9*17+3].pos[2] = 0x900,
	
	// down
	NEW_BLOCK(18, group4_ground, -0xA80, 0x600, NULL, 0x1800, RGBtoBGR(0x00FF60)),
	NEW_BLOCK(19, group4_ground, -0xD80, 0x600, NULL, 0x1800, RGBtoBGR(0x00FF80)),
	
	// down
	NEW_BLOCK(20, group4_ground, -0xA80, 0x300, NULL, 0x1800, RGBtoBGR(0x0000FF)),
	NEW_BLOCK(21, group4_ground, -0xD80, 0x300, NULL, 0x1800, RGBtoBGR(0x2000FF)),
	
	// down
	NEW_BLOCK(22, group4_ground, -0xA80, 0x0, NULL, 0x1800, RGBtoBGR(0x2000FF)),
	NEW_BLOCK(23, group4_ground, -0xD80, 0x0, NULL, 0x1800, RGBtoBGR(0x4000FF)),
	
	// left
	NEW_BLOCK(24, group4_ground, -0x780, 0, NULL, 0x1800, RGBtoBGR(0x4000FF)),
	NEW_BLOCK(25, group4_ground, -0x780, 0x300, NULL, 0x1800, RGBtoBGR(0x6000FF)),
	
	// left
	NEW_BLOCK(26, group4_ground, -0x480, 0, NULL, 0x1800, RGBtoBGR(0x6000FF)),
	NEW_BLOCK(27, group4_ground, -0x480, 0x300, NULL, 0x1800, RGBtoBGR(0x8000FF)),
	
	// ========== Other Side Of Map ======================
	
	// spawn
	NEW_BLOCK(28, group4_ground, -0x180, 0x1500+0, NULL, 0x1800, 0x303030),
	NEW_BLOCK(29, group4_ground, 0x180, 0x1500+0, NULL, 0x1800, 0x606060),
	
	// ========== bsp ======================
	
	.bsp =
	{
		// root node
		BSP_BRANCH(0, SPLIT_X, 0x1, 0x2),
		
		BSP_LEAF(1, 28, 2),
		BSP_LEAF(2, 0, 28),
	},
	
	.pvs =
	{
		.visLeafSrc = LEV_OFFSETOF(visBitIndex[0]),
		.visFaceSrc = LEV_OFFSETOF(visBitIndex[0]),
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
		.visLeafList[0] = LEV_OFFSETOF(VisMem_bitIndex_DstMemcpyP1[0]),
		.visFaceList[0] = LEV_OFFSETOF(VisMem_bitIndex_DstMemcpyP1[4]),
		.bspList[0] = LEV_OFFSETOF(VisMem_bspList_RenderListP1[0]),
		
		// P2
		.visLeafList[1] = LEV_OFFSETOF(VisMem_bitIndex_DstMemcpyP2[0]),
		.visFaceList[1] = LEV_OFFSETOF(VisMem_bitIndex_DstMemcpyP2[4]),
		.bspList[1] = LEV_OFFSETOF(VisMem_bspList_RenderListP2[0]),
		
		// P3
		.visLeafList[2] = LEV_OFFSETOF(VisMem_bitIndex_DstMemcpyP3[0]),
		.visFaceList[2] = LEV_OFFSETOF(VisMem_bitIndex_DstMemcpyP3[4]),
		.bspList[2] = LEV_OFFSETOF(VisMem_bspList_RenderListP3[0]),
		
		// P4
		.visLeafList[3] = LEV_OFFSETOF(VisMem_bitIndex_DstMemcpyP4[0]),
		.visFaceList[3] = LEV_OFFSETOF(VisMem_bitIndex_DstMemcpyP4[4]),
		.bspList[3] = LEV_OFFSETOF(VisMem_bspList_RenderListP4[0]),
	},
	
	.map =
	{
		(2)<<2,

		LEV_OFFSETOF(pvs.visLeafSrc),
		LEV_OFFSETOF(pvs.visFaceSrc),
	},
};
