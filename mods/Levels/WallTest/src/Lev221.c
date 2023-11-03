// Only for generating LEV files
#pragma GCC diagnostic ignored "-Wint-conversion"
#pragma GCC diagnostic ignored "-Woverride-init"
#pragma GCC diagnostic ignored "-Woverflow"

#include <common.h>
#include "../../levelBuilder.h"
#include "trackSpecificData.h"

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
	struct BSP bsp[5];
	struct PVS pvs;
	int visBitIndex[4];
	struct VisMem visMem;
	
	// leave empty
	// DstMemcpy must be big for PVS to copy into,
	// RenderList must be big enough for 2 pointers to all BSP nodes
	int VisMem_bitIndex_DstMemcpyP1[8];
	int VisMem_bspList_RenderListP1[5*2];
	int VisMem_bitIndex_DstMemcpyP2[8];
	int VisMem_bspList_RenderListP2[5*2];
	int VisMem_bitIndex_DstMemcpyP3[8];
	int VisMem_bspList_RenderListP3[5*2];
	int VisMem_bitIndex_DstMemcpyP4[8];
	int VisMem_bspList_RenderListP4[5*2];
	
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
		.numVertex = NUM_BLOCKS*9,
		.unk1 = 0,
		.ptrQuadBlockArray = LEV_OFFSETOF(quadBlock[0]),
		.ptrVertexArray = LEV_OFFSETOF(levVertex[0]),
		.unk2 = 0,
		.bspRoot = LEV_OFFSETOF(bsp[0]),
		.numBspNodes = 5,
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
	
	NEW_BLOCK(Bsp0_Red1, group4_ground, -0x180, 0, NULL, 0x1800, RGBtoBGR(0xFF0000)),
	NEW_BLOCK(Bsp0_Red2, group4_ground, 0x180, 0, NULL, 0x1800, RGBtoBGR(0xFF2000)),
	NEW_BLOCK(Bsp0_Red3, group4_ground, -0x180, 0x300, NULL, 0x1800, RGBtoBGR(0xFF2000)),
	NEW_BLOCK(Bsp0_Red4, group4_ground, 0x180, 0x300, NULL, 0x1800, RGBtoBGR(0xFF4000)),
	
	NEW_BLOCK(Bsp0_Pink1, group4_ground, -0xA80, 0x300, NULL, 0x1800, RGBtoBGR(0x0000FF)),
	NEW_BLOCK(Bsp0_Pink2, group4_ground, -0xD80, 0x300, NULL, 0x1800, RGBtoBGR(0x2000FF)),
	NEW_BLOCK(Bsp0_Pink3, group4_ground, -0xA80, 0x0, NULL, 0x1800, RGBtoBGR(0x2000FF)),
	NEW_BLOCK(Bsp0_Pink4, group4_ground, -0xD80, 0x0, NULL, 0x1800, RGBtoBGR(0x4000FF)),
	
	NEW_BLOCK(Bsp0_Blue1, group4_ground, -0x780, 0, NULL, 0x1800, RGBtoBGR(0x4000FF)),
	NEW_BLOCK(Bsp0_Blue2, group4_ground, -0x780, 0x300, NULL, 0x1800, RGBtoBGR(0x6000FF)),
	NEW_BLOCK(Bsp0_Blue3, group4_ground, -0x480, 0, NULL, 0x1800, RGBtoBGR(0x6000FF)),
	NEW_BLOCK(Bsp0_Blue4, group4_ground, -0x480, 0x300, NULL, 0x1800, RGBtoBGR(0x8000FF)),
	
	NEW_BLOCK(Bsp0_Ocean1, group4_ground, -0xA80, -0x300, NULL, 0x1800, RGBtoBGR(0x4077FF)),
	NEW_BLOCK(Bsp0_Ocean2, group4_ground, -0xA80, -0x600, NULL, 0x1800, RGBtoBGR(0x6077FF)),
	NEW_BLOCK(Bsp0_Ocean3, group4_ground, -0xD80, -0x300, NULL, 0x1800, RGBtoBGR(0x6077FF)),
	NEW_BLOCK(Bsp0_Ocean4, group4_ground, -0xD80, -0x600, NULL, 0x1800, RGBtoBGR(0x8077FF)),
	
	// down ramp towards upramp
	NEW_BLOCK(Bsp0_DownRamp1, group4_ground, -0x180, -0x300, NULL, 0x1800, 0x303030),
	NEW_BLOCK(Bsp0_DownRamp2, group4_ground, 0x180, -0x300, NULL, 0x1800, 0x606060),
	
	MAKE_RAMP(
		Bsp0_DownRamp1, 0x180,
		2,8,3,
		5,6,7,
		0,4,1
	),
	
	MAKE_RAMP(
		Bsp0_DownRamp2, 0x180,
		2,8,3,
		5,6,7,
		0,4,1
	),
	
	// down ramp towards upramp
	NEW_BLOCK(Bsp0_DownRamp3, group4_ground, -0x180, -0x600, NULL, 0x1800, 0x303030),
	NEW_BLOCK(Bsp0_DownRamp4, group4_ground, 0x180, -0x600, NULL, 0x1800, 0x606060),
	
	MAKE_RAMP(
		Bsp0_DownRamp3, 0x180,
		2,8,3,
		5,6,7,
		0,4,1
	),
	
	MAKE_RAMP(
		Bsp0_DownRamp4, 0x180,
		2,8,3,
		5,6,7,
		0,4,1
	),
	
	SET_POSY_RAMP(
		Bsp0_DownRamp3, 0x180, 0x180,
		2,8,3,
		5,6,7,
		0,4,1
	),
	
	SET_POSY_RAMP(
		Bsp0_DownRamp4, 0x180, 0x180,
		2,8,3,
		5,6,7,
		0,4,1
	),
	
	// down ramp towards upramp
	NEW_BLOCK(Bsp0_DownRamp5, group4_ground, -0x180, -0x900, NULL, 0x1800, RGBtoBGR(0x603030)),
	NEW_BLOCK(Bsp0_DownRamp6, group4_ground, 0x180, -0x900, NULL, 0x1800, RGBtoBGR(0xC06060)),
	
	SET_POSY_FLAT(Bsp0_DownRamp5, 0x300),
	SET_POSY_FLAT(Bsp0_DownRamp6, 0x300),
	
	NEW_BLOCK(Bsp0_DownRamp7, group4_ground, -0x180, -0xC00, NULL, 0x1800, RGBtoBGR(0x603030)),
	NEW_BLOCK(Bsp0_DownRamp8, group4_ground, 0x180, -0xC00, NULL, 0x1800, RGBtoBGR(0xC06060)),
	
	SET_POSY_FLAT(Bsp0_DownRamp7, 0x300),
	SET_POSY_FLAT(Bsp0_DownRamp8, 0x300),
	
	// ====== Wall Section =========
	
	// forward
	NEW_BLOCK(Bsp1_RampUp1, group4_ground, -0x180, 0x600, NULL, 0x1880, RGBtoBGR(0xFF4000)),
	NEW_BLOCK(Bsp1_RampUp2, group4_ground, 0x180, 0x600, NULL, 0x1880, RGBtoBGR(0xFF6000)),
	
	MAKE_RAMP(
		Bsp1_RampUp1, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	MAKE_RAMP(
		Bsp1_RampUp2, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	.levVertex[9*Bsp1_RampUp1+5].pos[1] = 0xC0,
	.levVertex[9*Bsp1_RampUp1+6].pos[1] = 0xC0,
	.levVertex[9*Bsp1_RampUp1+7].pos[1] = 0xC0,
	
	.levVertex[9*Bsp1_RampUp2+5].pos[1] = 0xC0,
	.levVertex[9*Bsp1_RampUp2+6].pos[1] = 0xC0,
	.levVertex[9*Bsp1_RampUp2+7].pos[1] = 0xC0,
	
	.levVertex[9*Bsp1_RampUp1+2].pos[1] = 0x240,
	.levVertex[9*Bsp1_RampUp1+8].pos[1] = 0x240,
	.levVertex[9*Bsp1_RampUp1+3].pos[1] = 0x240,
	
	.levVertex[9*Bsp1_RampUp2+2].pos[1] = 0x240,
	.levVertex[9*Bsp1_RampUp2+8].pos[1] = 0x240,
	.levVertex[9*Bsp1_RampUp2+3].pos[1] = 0x240,
	
	// forward
	// do NOT set Z, cause it'll overwrite in a few lines
	NEW_BLOCK(Bsp1_Wall1, group4_ground, -0x180, 0, NULL, 0x1880, RGBtoBGR(0xFF6000)),
	NEW_BLOCK(Bsp1_Wall2, group4_ground, 0x180, 0, NULL, 0x1880, RGBtoBGR(0xFF8000)),
	
	MAKE_RAMP(
		Bsp1_Wall1, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	MAKE_RAMP(
		Bsp1_Wall2, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	SET_POSY_RAMP(
		Bsp1_Wall1, 0x240, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	SET_POSY_RAMP(
		Bsp1_Wall2, 0x240, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	.levVertex[9*Bsp1_Wall1+0].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall1+4].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall1+1].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall1+5].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall1+6].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall1+7].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall1+2].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall1+8].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall1+3].pos[2] = 0x840,
	
	.levVertex[9*Bsp1_Wall2+0].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall2+4].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall2+1].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall2+5].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall2+6].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall2+7].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall2+2].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall2+8].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall2+3].pos[2] = 0x840,
	
	// forward
	// do NOT set Z, cause it'll overwrite in a few lines
	NEW_BLOCK(Bsp1_Wall3, group4_ground, -0x180, 0, NULL, 0x1880, RGBtoBGR(0xFF8000)),
	NEW_BLOCK(Bsp1_Wall4, group4_ground, 0x180, 0, NULL, 0x1880, RGBtoBGR(0xFF8000)),

	MAKE_RAMP(
		Bsp1_Wall3, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	MAKE_RAMP(
		Bsp1_Wall4, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	SET_POSY_RAMP(
		Bsp1_Wall3, 0x540, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	SET_POSY_RAMP(
		Bsp1_Wall4, 0x540, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	.levVertex[9*Bsp1_Wall3+0].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall3+4].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall3+1].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall3+5].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall3+6].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall3+7].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall3+2].pos[2] = 0x900,
	.levVertex[9*Bsp1_Wall3+8].pos[2] = 0x900,
	.levVertex[9*Bsp1_Wall3+3].pos[2] = 0x900,
	
	.levVertex[9*Bsp1_Wall4+0].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall4+4].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall4+1].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall4+5].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall4+6].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall4+7].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall4+2].pos[2] = 0x900,
	.levVertex[9*Bsp1_Wall4+8].pos[2] = 0x900,
	.levVertex[9*Bsp1_Wall4+3].pos[2] = 0x900,
	
	// test perfectly 90-degree wall
	NEW_BLOCK(Bsp1_90deg, group4_ground, 0x180, 0, NULL, 0x1880, RGBtoBGR(0x707070)),
	
	MAKE_RAMP(
		Bsp1_90deg, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	SET_POSY_RAMP(
		Bsp1_90deg, 0x840, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	.levVertex[9*Bsp1_90deg+0].pos[2] = 0x900,
	.levVertex[9*Bsp1_90deg+4].pos[2] = 0x900,
	.levVertex[9*Bsp1_90deg+1].pos[2] = 0x900,
	.levVertex[9*Bsp1_90deg+5].pos[2] = 0x900,
	.levVertex[9*Bsp1_90deg+6].pos[2] = 0x900,
	.levVertex[9*Bsp1_90deg+7].pos[2] = 0x900,
	.levVertex[9*Bsp1_90deg+2].pos[2] = 0x900,
	.levVertex[9*Bsp1_90deg+8].pos[2] = 0x900,
	.levVertex[9*Bsp1_90deg+3].pos[2] = 0x900,
	
	// right
	NEW_BLOCK(Bsp1_Wall5, group4_ground, -0x480, 0, NULL, 0x1800, RGBtoBGR(0xFF8000)),
	NEW_BLOCK(Bsp1_Wall6, group4_ground, -0x780, 0, NULL, 0x1800, RGBtoBGR(0x00FF00)),
	
	MAKE_RAMP(
		Bsp1_Wall5, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	MAKE_RAMP(
		Bsp1_Wall6, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	SET_POSY_RAMP(
		Bsp1_Wall5, 0x240, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	SET_POSY_RAMP(
		Bsp1_Wall6, 0x240, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	.levVertex[9*Bsp1_Wall5+0].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall5+4].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall5+1].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall5+5].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall5+6].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall5+7].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall5+2].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall5+8].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall5+3].pos[2] = 0x840,
	
	.levVertex[9*Bsp1_Wall6+0].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall6+4].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall6+1].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall6+5].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall6+6].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall6+7].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall6+2].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall6+8].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall6+3].pos[2] = 0x840,
	
	// right
	NEW_BLOCK(Bsp1_Wall7, group4_ground, -0x480, 0, NULL, 0x1800, RGBtoBGR(0x00FF00)),
	NEW_BLOCK(Bsp1_Wall8, group4_ground, -0x780, 0, NULL, 0x1800, RGBtoBGR(0x00FF20)),
	
	MAKE_RAMP(
		Bsp1_Wall7, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	MAKE_RAMP(
		Bsp1_Wall8, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	SET_POSY_RAMP(
		Bsp1_Wall7, 0x540, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	SET_POSY_RAMP(
		Bsp1_Wall8, 0x540, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	.levVertex[9*Bsp1_Wall7+0].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall7+4].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall7+1].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall7+5].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall7+6].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall7+7].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall7+2].pos[2] = 0x900,
	.levVertex[9*Bsp1_Wall7+8].pos[2] = 0x900,
	.levVertex[9*Bsp1_Wall7+3].pos[2] = 0x900,
	
	.levVertex[9*Bsp1_Wall8+0].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall8+4].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall8+1].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall8+5].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall8+6].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall8+7].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall8+2].pos[2] = 0x900,
	.levVertex[9*Bsp1_Wall8+8].pos[2] = 0x900,
	.levVertex[9*Bsp1_Wall8+3].pos[2] = 0x900,
	
	// right
	NEW_BLOCK(Bsp1_Wall9, group4_ground, -0xA80, 0x900, NULL, 0x1800, RGBtoBGR(0x00FF20)),
	NEW_BLOCK(Bsp1_Wall10, group4_ground, -0xD80, 0xC00, NULL, 0x1800, RGBtoBGR(0x00FF40)),
	
	MAKE_RAMP(
		Bsp1_Wall9, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	MAKE_RAMP(
		Bsp1_Wall10, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	SET_POSY_RAMP(
		Bsp1_Wall9, 0x240, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	SET_POSY_RAMP(
		Bsp1_Wall10, 0x240, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	.levVertex[9*Bsp1_Wall9+0].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall9+4].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall9+1].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall9+5].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall9+6].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall9+7].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall9+2].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall9+8].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall9+3].pos[2] = 0x840,
	
	.levVertex[9*Bsp1_Wall10+0].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall10+4].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall10+1].pos[2] = 0x780,
	.levVertex[9*Bsp1_Wall10+5].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall10+6].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall10+7].pos[2] = 0x7E0,
	.levVertex[9*Bsp1_Wall10+2].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall10+8].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall10+3].pos[2] = 0x840,
	
	// right
	NEW_BLOCK(Bsp1_Wall11, group4_ground, -0xA80, 0x900, NULL, 0x1800, RGBtoBGR(0x00FF40)),
	NEW_BLOCK(Bsp1_Wall12, group4_ground, -0xD80, 0xC00, NULL, 0x1800, RGBtoBGR(0x00FF60)),
	
	MAKE_RAMP(
		Bsp1_Wall11, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	MAKE_RAMP(
		Bsp1_Wall12, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	SET_POSY_RAMP(
		Bsp1_Wall11, 0x540, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	SET_POSY_RAMP(
		Bsp1_Wall12, 0x540, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	.levVertex[9*Bsp1_Wall11+0].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall11+4].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall11+1].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall11+5].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall11+6].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall11+7].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall11+2].pos[2] = 0x900,
	.levVertex[9*Bsp1_Wall11+8].pos[2] = 0x900,
	.levVertex[9*Bsp1_Wall11+3].pos[2] = 0x900,
	
	.levVertex[9*Bsp1_Wall12+0].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall12+4].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall12+1].pos[2] = 0x840,
	.levVertex[9*Bsp1_Wall12+5].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall12+6].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall12+7].pos[2] = 0x8A0,
	.levVertex[9*Bsp1_Wall12+2].pos[2] = 0x900,
	.levVertex[9*Bsp1_Wall12+8].pos[2] = 0x900,
	.levVertex[9*Bsp1_Wall12+3].pos[2] = 0x900,
	
	// down
	NEW_BLOCK(Bsp1_RampDown1, group4_ground, -0xA80, 0x600, NULL, 0x1800, RGBtoBGR(0x00FF60)),
	NEW_BLOCK(Bsp1_RampDown2, group4_ground, -0xD80, 0x600, NULL, 0x1800, RGBtoBGR(0x00FF80)),
	
	MAKE_RAMP(
		Bsp1_RampDown1, 0x300,
		0,4,1, // low
		5,6,7, // mid
		2,8,3 // hi
	),
	
	MAKE_RAMP(
		Bsp1_RampDown2, 0x300,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	.levVertex[9*Bsp1_RampDown1+5].pos[1] = 0xC0,
	.levVertex[9*Bsp1_RampDown1+6].pos[1] = 0xC0,
	.levVertex[9*Bsp1_RampDown1+7].pos[1] = 0xC0,
	
	.levVertex[9*Bsp1_RampDown2+5].pos[1] = 0xC0,
	.levVertex[9*Bsp1_RampDown2+6].pos[1] = 0xC0,
	.levVertex[9*Bsp1_RampDown2+7].pos[1] = 0xC0,
	
	.levVertex[9*Bsp1_RampDown1+2].pos[1] = 0x240,
	.levVertex[9*Bsp1_RampDown1+8].pos[1] = 0x240,
	.levVertex[9*Bsp1_RampDown1+3].pos[1] = 0x240,
	
	.levVertex[9*Bsp1_RampDown2+2].pos[1] = 0x240,
	.levVertex[9*Bsp1_RampDown2+8].pos[1] = 0x240,
	.levVertex[9*Bsp1_RampDown2+3].pos[1] = 0x240,
	
	// ========== +X Side Of Map ======================

	NEW_BLOCK(Bsp2_Block_1_1, group4_ground, 0x480, 0x300, NULL, 0x1800, RGBtoBGR(0x303030)),
	NEW_BLOCK(Bsp2_Block_2_1, group4_ground, 0x780, 0x300, NULL, 0x1800, RGBtoBGR(0x606060)),	
	NEW_BLOCK(Bsp2_Block_1_2, group4_ground, 0x480, 0, NULL, 0x1800, RGBtoBGR(0x303030)),
	NEW_BLOCK(Bsp2_Block_2_2, group4_ground, 0x780, 0, NULL, 0x1800, RGBtoBGR(0x606060)),
	NEW_BLOCK(Bsp2_Block_1_3, group4_ground, 0x480, -0x300, NULL, 0x1800, 0x303030),
	NEW_BLOCK(Bsp2_Block_2_3, group4_ground, 0x780, -0x300, NULL, 0x1800, 0x606060),
	
	MAKE_RAMP(
		Bsp2_Block_1_3, 0x180,
		2,8,3,
		5,6,7,
		0,4,1
	),
	
	MAKE_RAMP(
		Bsp2_Block_2_3, 0x180,
		2,8,3,
		5,6,7,
		0,4,1
	),
	
	NEW_BLOCK(Bsp2_Block_3_1, group4_ground, 0xA80, 0x300, NULL, 0x1800, RGBtoBGR(0x303030)),
	NEW_BLOCK(Bsp2_Block_4_1, group4_ground, 0xD80, 0x300, NULL, 0x1800, RGBtoBGR(0x606060)),	
	NEW_BLOCK(Bsp2_Block_3_2, group4_ground, 0xA80, 0, NULL, 0x1800, RGBtoBGR(0x303030)),
	NEW_BLOCK(Bsp2_Block_4_2, group4_ground, 0xD80, 0, NULL, 0x1800, RGBtoBGR(0x606060)),
	NEW_BLOCK(Bsp2_Block_3_3, group4_ground, 0xA80, -0x300, NULL, 0x1800, 0x303030),
	NEW_BLOCK(Bsp2_Block_4_3, group4_ground, 0xD80, -0x300, NULL, 0x1800, 0x606060),
	
	MAKE_RAMP(
		Bsp2_Block_3_3, 0x180,
		2,8,3,
		5,6,7,
		0,4,1
	),
	
	MAKE_RAMP(
		Bsp2_Block_4_3, 0x180,
		2,8,3,
		5,6,7,
		0,4,1
	),
	
	NEW_BLOCK(Bsp2_Block_5_1, group4_ground, 0x1380, 0x300, NULL, 0x1800, RGBtoBGR(0x6060C0)),
	NEW_BLOCK(Bsp2_Block_6_1, group4_ground, 0x1080, 0x300, NULL, 0x1800, RGBtoBGR(0x303030)),	
	NEW_BLOCK(Bsp2_Block_5_2, group4_ground, 0x1380, 0, NULL, 0x1800, RGBtoBGR(0x6060C0)),
	NEW_BLOCK(Bsp2_Block_6_2, group4_ground, 0x1080, 0, NULL, 0x1800, RGBtoBGR(0x303030)),
	
	// U-Turn into WALL
	NEW_BLOCK(Bsp2_RampU1, group4_ground, 0xA80, 0x600, NULL, 0x1800, 0x303030),
	NEW_BLOCK(Bsp2_RampU2, group4_ground, 0xD80, 0x600, NULL, 0x1800, 0x606060),
	
	MAKE_RAMP(
		Bsp2_RampU1, 0x180,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	MAKE_RAMP(
		Bsp2_RampU2, 0x180,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	NEW_BLOCK(Bsp2_RampU3, group4_ground, 0xA80, 0x900, NULL, 0x1800, 0x303030),
	NEW_BLOCK(Bsp2_RampU4, group4_ground, 0xD80, 0x900, NULL, 0x1800, 0x606060),
	
	MAKE_RAMP(
		Bsp2_RampU3, 0x180,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	MAKE_RAMP(
		Bsp2_RampU4, 0x180,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	SET_POSY_RAMP(
		Bsp2_RampU3, 0x180, 0x180,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	SET_POSY_RAMP(
		Bsp2_RampU4, 0x180, 0x180,
		0,4,1,
		5,6,7,
		2,8,3
	),
	
	NEW_BLOCK(Bsp2_RampU5, group4_ground, 0xA80, 0xC00, NULL, 0x1800, 0x306030),
	NEW_BLOCK(Bsp2_RampU6, group4_ground, 0xD80, 0xC00, NULL, 0x1800, 0x60C060),
	
	SET_POSY_FLAT(Bsp2_RampU5, 0x300),
	SET_POSY_FLAT(Bsp2_RampU6, 0x300),
	
	NEW_BLOCK(Bsp2_RampU7, group4_ground, 0xA80, 0xF00, NULL, 0x1800, 0x306030),
	NEW_BLOCK(Bsp2_RampU8, group4_ground, 0xD80, 0xF00, NULL, 0x1800, 0x60C060),
	
	SET_POSY_FLAT(Bsp2_RampU7, 0x300),
	SET_POSY_FLAT(Bsp2_RampU8, 0x300),
	
	// ========== bsp ======================
	
	.bsp =
	{
		// root node
		BSP_BRANCH(0, SPLIT_Z, 0x1, 0x2),
		BSP_BRANCH(1, SPLIT_X, 0x3, 0x4),

		BSP_LEAF(2, Bsp2_FirstBlock, Bsp2_BlockCount),
		BSP_LEAF(3, Bsp1_FirstBlock, Bsp1_BlockCount),
		BSP_LEAF(4, Bsp0_FirstBlock, Bsp0_BlockCount)
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
