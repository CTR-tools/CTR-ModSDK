#include <common.h>
#include "../../levelBuilder.h"
#include "trackSpecificData.h"

struct LevelFile
{
	void* ptrMap;
	struct Level level;
	struct mesh_info mInfo;
	struct IconGroup4 group4_checkerEdge;
	struct IconGroup4 group4_checkerCenter;
	struct IconGroup4 group4_tileEdge;
	struct IconGroup4 group4_tileCenter;
	struct IconGroup4 group4_turbopad_green;
	struct IconGroup4 group4_turbopad_gray;
	struct IconGroup4 group4_placeHolder;
	struct SpawnType1 ptrSpawnType1;
	struct CheckpointNode checkpointNodes[NUM_CHECKPOINT];
	struct QuadBlock quadBlock[NUM_BLOCKS];
	struct LevVertex levVertex[NUM_BLOCKS*9];
	struct BSP bsp[9];
	struct PVS pvs[NUM_PVS];
	int leafList[2*NUM_PVS];
	int faceList[5*NUM_PVS];
	struct VisMem visMem;
	
	int VisMem_bitIndex_DstMemcpyP1[8]; // leave empty
	int VisMem_bspList_RenderListP1[9*2];
	int VisMem_bitIndex_DstMemcpyP2[8]; // leave empty
	int VisMem_bspList_RenderListP2[9*2];
	int VisMem_bitIndex_DstMemcpyP3[8]; // leave empty
	int VisMem_bspList_RenderListP3[9*2];
	int VisMem_bitIndex_DstMemcpyP4[8]; // leave empty
	int VisMem_bspList_RenderListP4[9*2];
	
	int map[(46+NUM_BLOCKS*6)+1];
};

struct LevelFile file =
{
	.ptrMap = OFFSETOF(struct LevelFile, map[0])-4,
	
	.level =
	{
		.ptr_mesh_info = OFFSETOF(struct LevelFile, mInfo)-4,
		.visMem = OFFSETOF(struct LevelFile, visMem)-4,
		
		// warning, game will edit rotY by 0x400 after spawn
		
		#if 0 // Arcade mode
		.DriverSpawn[0].pos = {0x180,0,-0xc0},
		.DriverSpawn[0].rot = {0,0-0x400,0},
		#else // Simulate Time Trial Spawn
		.DriverSpawn[0].pos = {0x80,0,-0xc0},
		.DriverSpawn[0].rot = {0,0-0x400,0},
		#endif
		
		.DriverSpawn[1].pos = {0x80,0,-0xc0},
		.DriverSpawn[1].rot = {0x40,0-0x400,0},
		
		.DriverSpawn[2].pos = {-0x80,0,-0xc0},
		.DriverSpawn[2].rot = {-0x40,0-0x400,0},
		
		.DriverSpawn[3].pos = {-0x180,0,-0xc0},
		.DriverSpawn[3].rot = {-0x80,0-0x400,0},
		
		.ptrSpawnType1 = OFFSETOF(struct LevelFile, ptrSpawnType1)-4,
		
		.clearColor[0].rgb = {0x20, 0x10, 0x80},
		.clearColor[0].enable = 1,
		
		.clearColor[1].rgb = {0x80, 0x20, 0x10},
		.clearColor[1].enable = 1,
		
		// only non-zero for Race maps
		// battle maps need array, but still set CNT to zero
		.cnt_restart_points = NUM_CHECKPOINT,
		.ptr_restart_points = OFFSETOF(struct LevelFile, checkpointNodes[0])-4,
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
		.numBspNodes = 9,
	},
	
	.group4_checkerEdge.texLayout =
	{
		ImageName_Blend(512, 0, 32, 128, 64, 64, 0, TRANS_50), // very far
		ImageName_Blend(512, 0, 32, 128, 64, 64, 0, TRANS_50), // far
		ImageName_Blend(512, 0, 32, 128, 64, 64, 0, TRANS_50), // close
		ImageName_Blend(512, 0, 32, 128, 64, 64, 0, TRANS_50)  // very close
	},
	
	.group4_checkerCenter.texLayout =
	{	
		ImageName_Blend(528, 0, 32, 129, 64, 64, 0, TRANS_50), // very far
		ImageName_Blend(528, 0, 32, 129, 64, 64, 0, TRANS_50), // far
		ImageName_Blend(528, 0, 32, 129, 64, 64, 0, TRANS_50), // close
		ImageName_Blend(528, 0, 32, 129, 64, 64, 0, TRANS_50)  // very close
	},
	
	.group4_tileEdge.texLayout =
	{	
		ImageName_Blend(544, 0, 32, 130, 64, 64, 0, TRANS_50), // very far
		ImageName_Blend(544, 0, 32, 130, 64, 64, 0, TRANS_50), // far
		ImageName_Blend(544, 0, 32, 130, 64, 64, 0, TRANS_50), // close
		ImageName_Blend(544, 0, 32, 130, 64, 64, 0, TRANS_50)  // very close
	},
	
	.group4_tileCenter.texLayout =
	{	
		ImageName_Blend(560, 0, 32, 131, 64, 64, 0, TRANS_50), // very far
		ImageName_Blend(560, 0, 32, 131, 64, 64, 0, TRANS_50), // far
		ImageName_Blend(560, 0, 32, 131, 64, 64, 0, TRANS_50), // close
		ImageName_Blend(560, 0, 32, 131, 64, 64, 0, TRANS_50)  // very close
	},
	
	.group4_placeHolder.texLayout =
	{
		ImageName_Blend(576, 0, 32, 132, 16, 16, 0, TRANS_50), // very far
		ImageName_Blend(576, 0, 32, 132, 16, 16, 0, TRANS_50), // far
		ImageName_Blend(576, 0, 32, 132, 16, 16, 0, TRANS_50), // close
		ImageName_Blend(576, 0, 32, 132, 16, 16, 0, TRANS_50)  // very close
	},
	
	.group4_turbopad_green.texLayout =
	{
		ImageName_Blend(640, 0, 32, 133, 32, 16, 0, TRANS_50), // very far
		ImageName_Blend(640, 0, 32, 133, 32, 16, 0, TRANS_50), // far
		ImageName_Blend(640, 0, 32, 133, 32, 16, 0, TRANS_50), // close
		ImageName_Blend(640, 0, 32, 133, 32, 16, 0, TRANS_50)  // very close
	},
	
	.group4_turbopad_gray.texLayout =
	{
		ImageName_Blend(704, 0, 32, 134, 32, 16, 0, TRANS_50), // very far
		ImageName_Blend(704, 0, 32, 134, 32, 16, 0, TRANS_50), // far
		ImageName_Blend(704, 0, 32, 134, 32, 16, 0, TRANS_50), // close
		ImageName_Blend(704, 0, 32, 134, 32, 16, 0, TRANS_50)  // very close
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
		0, group4_ground,	// index, texture
		0x0, 0x0			// posX, posY (size is always 0x300 x 0x300)
		NULL, 0x1800, 		// vertex flags, quadblock flags
		0xFF, 0x00, 0x00	// colorRGB
	),
*/
	
	// +z is forward
	// +x is left, not right
	
	// behind spawn
	NEW_BLOCK(Bsp0_BehindStart1, group4_placeHolder, -0x180, -0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp0_BehindStart2, group4_placeHolder, 0x180, -0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp0_BehindStart3, group4_placeHolder, -0x180, -0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp0_BehindStart4, group4_placeHolder, 0x180, -0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	// top/bottom left/right assuming you're rotation is 0,0,0
	//TEX_2X2(Bsp0_BehindStart1, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter), // TODO: CORNER
	//TEX_2X2(Bsp0_BehindStart2, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge), // TODO: CORNER
	.quadBlock[Bsp0_BehindStart1].draw_order_low = 0x800000,
	.quadBlock[Bsp0_BehindStart2].draw_order_low = 0x1044000,
	TEX_2X2(Bsp0_BehindStart3, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_BehindStart4, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_BehindStart3].draw_order_low = 0x800000,
	.quadBlock[Bsp0_BehindStart4].draw_order_low = 0x1044000,
	
	// spawn
	NEW_BLOCK(Bsp0_StartLine1, group4_tileEdge, -0x180, 0, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp0_StartLine2, group4_tileEdge, 0x180, 0, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	// TR, TL, BR, BL assuming you're rotation is 0,0,0
	TEX_2X2(Bsp0_StartLine1, group4_tileEdge, group4_tileCenter, group4_checkerEdge, group4_checkerCenter),
	TEX_2X2(Bsp0_StartLine2, group4_tileCenter, group4_tileEdge, group4_checkerCenter, group4_checkerEdge),
	.quadBlock[Bsp0_StartLine1].draw_order_low = 0x800000, // rotate checker
	.quadBlock[Bsp0_StartLine2].draw_order_low = 0x1044000, // rotation
	
	// flat, in front of spawn
	NEW_BLOCK(Bsp0_AfterStart1, group4_placeHolder, -0x180, 0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp0_AfterStart2, group4_placeHolder, 0x180, 0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	TEX_2X2(Bsp0_AfterStart1, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_AfterStart2, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_AfterStart1].draw_order_low = 0x800000,
	.quadBlock[Bsp0_AfterStart2].draw_order_low = 0x1044000,
	
	// ramp down (1/3)
	NEW_BLOCK(Bsp0_DownRamp1, group4_placeHolder, -0x180, 0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp0_DownRamp2, group4_placeHolder, 0x180, 0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	TEX_2X2(Bsp0_DownRamp1, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_DownRamp2, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_DownRamp1].draw_order_low = 0x800000,
	.quadBlock[Bsp0_DownRamp2].draw_order_low = 0x1044000,
	
	MAKE_RAMP(
		Bsp0_DownRamp1, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp0_DownRamp2, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_DownRamp1, -0x180, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_DownRamp2, -0x180, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	// ramp down (2/3)
	NEW_BLOCK(Bsp0_DownRamp3, group4_placeHolder, -0x180, 0x900, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp0_DownRamp4, group4_placeHolder, 0x180, 0x900, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	TEX_2X2(Bsp0_DownRamp3, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_DownRamp4, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_DownRamp3].draw_order_low = 0x800000,
	.quadBlock[Bsp0_DownRamp4].draw_order_low = 0x1044000,
	
	MAKE_RAMP(
		Bsp0_DownRamp3, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp0_DownRamp4, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_DownRamp3, -0x300, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_DownRamp4, -0x300, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	// ramp down (3/3)
	NEW_BLOCK(Bsp0_DownRamp5, group4_placeHolder, -0x180, 0xC00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp0_DownRamp6, group4_placeHolder, 0x180, 0xC00, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	TEX_2X2(Bsp0_DownRamp5, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_DownRamp6, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_DownRamp5].draw_order_low = 0x800000,
	.quadBlock[Bsp0_DownRamp6].draw_order_low = 0x1044000,
	
	MAKE_RAMP(
		Bsp0_DownRamp5, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp0_DownRamp6, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_DownRamp5, -0x480, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_DownRamp6, -0x480, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	// bottom between ramps (with intended hole)
	NEW_BLOCK(Bsp0_FlatDip1, group4_placeHolder, -0x180, 0x1200, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp0_FlatDip2, group4_placeHolder, 0x180, 0xF00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp0_FlatDip3, group4_placeHolder, 0x180, 0x1200, NULL, 0x1800, 0x80, 0x80, 0x80),
	SET_POSY_FLAT(Bsp0_FlatDip1,-0x480),
	SET_POSY_FLAT(Bsp0_FlatDip2,-0x480),
	SET_POSY_FLAT(Bsp0_FlatDip3,-0x480),
	
	TEX_2X2(Bsp0_FlatDip1, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_FlatDip2, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_FlatDip1].draw_order_low = 0x800000,
	.quadBlock[Bsp0_FlatDip2].draw_order_low = 0x1044000,
	TEX_2X2(Bsp0_FlatDip3, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_FlatDip3].draw_order_low = 0x1044000,
	
	// ramp up (1/3)
	NEW_BLOCK(Bsp0_UpRamp1, group4_placeHolder, -0x180, 0x1500, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp0_UpRamp2_Turbo_9800, group4_turbopad_green, 0x180, 0x1500, NULL, 0x9800, 0x80, 0x80, 0x80),
	.quadBlock[Bsp0_UpRamp2_Turbo_9800].draw_order_low = FACE_PosZ,
	
	TEX_2X2(Bsp0_UpRamp1, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	.quadBlock[Bsp0_UpRamp1].draw_order_low = 0x800000,

	MAKE_RAMP(
		Bsp0_UpRamp1, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp0_UpRamp2_Turbo_9800, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_UpRamp1, -0x480, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_UpRamp2_Turbo_9800, -0x480, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	// ramp up (2/3)
	NEW_BLOCK(Bsp0_UpRamp3, group4_placeHolder, -0x180, 0x1800, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp0_UpRamp4, group4_placeHolder, 0x180, 0x1800, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	TEX_2X2(Bsp0_UpRamp3, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_UpRamp4, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_UpRamp3].draw_order_low = 0x800000,
	.quadBlock[Bsp0_UpRamp4].draw_order_low = 0x1044000,
	
	MAKE_RAMP(
		Bsp0_UpRamp3, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp0_UpRamp4, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_UpRamp3, -0x300, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_UpRamp4, -0x300, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	// ramp up (3/3)
	NEW_BLOCK(Bsp0_UpRamp5_Turbo_9800, group4_turbopad_gray, -0x180, 0x1B00, NULL, 0x9800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp0_UpRamp6, group4_placeHolder, 0x180, 0x1B00, NULL, 0x1800, 0x80, 0x80, 0x80),
	.quadBlock[Bsp0_UpRamp5_Turbo_9800].draw_order_low = FACE_PosZ,
	
	TEX_2X2(Bsp0_UpRamp6, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_UpRamp6].draw_order_low = 0x1044000,
	
	MAKE_RAMP(
		Bsp0_UpRamp5_Turbo_9800, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp0_UpRamp6, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_UpRamp5_Turbo_9800, -0x180, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_UpRamp6, -0x180, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	// turbo on ramp-up(3/3)
	NEW_BLOCK(Bsp0_UpRamp7_Turbo_1840, group4_turbopad_gray, -0x180, 0x1B00, NULL, 0x1840, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp0_UpRamp8_Turbo_1840, group4_turbopad_green, 0x180, 0x1500, NULL, 0x1840, 0x80, 0x80, 0x80),
	
	// turn into turbo, if flagsQ is 0x1840
	// 1 for normal, 2 for super turbo
	.quadBlock[Bsp0_UpRamp7_Turbo_1840].terrain_type = 2,
	.quadBlock[Bsp0_UpRamp8_Turbo_1840].terrain_type = 1,
	
	MAKE_RAMP(
		Bsp0_UpRamp7_Turbo_1840, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp0_UpRamp8_Turbo_1840, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_UpRamp7_Turbo_1840, -0x180, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp0_UpRamp8_Turbo_1840, -0x480, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	// flat, forward
	NEW_BLOCK(Bsp3_FlatTop1, group4_placeHolder, -0x180, 0x2100, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp3_FlatTop2, group4_placeHolder, 0x180, 0x2100, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp3_FlatTop3, group4_placeHolder, -0x180, 0x2400, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp3_FlatTop4, group4_placeHolder, 0x180, 0x2400, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp3_FlatTop5, group4_placeHolder, -0x180, 0x2700, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp3_FlatTop6, group4_placeHolder, 0x180, 0x2700, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp3_FlatTop7, group4_placeHolder, -0x180, 0x2A00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp3_FlatTop8, group4_placeHolder, 0x180, 0x2A00, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	TEX_2X2(Bsp3_FlatTop1, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp3_FlatTop2, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp3_FlatTop1].draw_order_low = 0x800000,
	.quadBlock[Bsp3_FlatTop2].draw_order_low = 0x1044000,
	TEX_2X2(Bsp3_FlatTop3, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp3_FlatTop4, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp3_FlatTop3].draw_order_low = 0x800000,
	.quadBlock[Bsp3_FlatTop4].draw_order_low = 0x1044000,
	
	TEX_2X2(Bsp3_FlatTop5, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	.quadBlock[Bsp3_FlatTop5].draw_order_low = 0x800000,
	
	TEX_2X2(Bsp3_FlatTop6, group4_tileCenter, group4_tileCenter, group4_tileCenter, group4_tileCenter),
	.quadBlock[Bsp3_FlatTop6].draw_order_low = 0x1044000,
	
	TEX_2X2(Bsp3_FlatTop8, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp3_FlatTop8].draw_order_low = 0x1984000,
	
	// TODO: FlatTop7 Corner
	
	// ==== End of BSP block =====
	
	// flat, turn 90
	NEW_BLOCK(Bsp1_TurnLeft1, group4_placeHolder, 0x480, 0x2700, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp1_TurnLeft2, group4_placeHolder, 0x480, 0x2A00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp1_TurnLeft3_Turbo_9800, group4_turbopad_green, 0x780, 0x2700, NULL, 0x9800, 0x80, 0x80, 0x80), // boost
	NEW_BLOCK(Bsp1_TurnLeft4_Turbo_9800, group4_turbopad_green, 0x780, 0x2A00, NULL, 0x9800, 0x80, 0x80, 0x80), // boost
	NEW_BLOCK(Bsp1_TurnLeft5_Turbo_1840, group4_turbopad_green, 0x780, 0x2700, NULL, 0x1840, 0x80, 0x80, 0x80), // boost
	NEW_BLOCK(Bsp1_TurnLeft6_Turbo_1840, group4_turbopad_green, 0x780, 0x2A00, NULL, 0x1840, 0x80, 0x80, 0x80), // boost
	NEW_BLOCK(Bsp1_TurnLeft7, group4_placeHolder, 0xA80, 0x2700, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp1_TurnLeft8, group4_placeHolder, 0xA80, 0x2A00, NULL, 0x1800, 0x80, 0x80, 0x80),
	.quadBlock[Bsp1_TurnLeft3_Turbo_9800].draw_order_low = FACE_PosX,
	.quadBlock[Bsp1_TurnLeft4_Turbo_9800].draw_order_low = FACE_PosX,
	.quadBlock[Bsp1_TurnLeft5_Turbo_1840].terrain_type = 1,
	.quadBlock[Bsp1_TurnLeft6_Turbo_1840].terrain_type = 1,
	
	// TR, TL, BR, BL
	TEX_2X2(Bsp1_TurnLeft1, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp1_TurnLeft2, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp1_TurnLeft1].draw_order_low = 0x808100,
	.quadBlock[Bsp1_TurnLeft2].draw_order_low = 0x1984000,
	
	// TR, TL, BR, BL
	TEX_2X2(Bsp1_TurnLeft7, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp1_TurnLeft8, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp1_TurnLeft7].draw_order_low = 0x808100,
	.quadBlock[Bsp1_TurnLeft8].draw_order_low = 0x1984000,
	
	// flat, turn 180
	NEW_BLOCK(Bsp1_TurnBack1_Turbo_9800, group4_turbopad_green, 0xD80, 0x2100, NULL, 0x9800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp1_TurnBack2_Turbo_9800, group4_turbopad_green, 0x1080, 0x2100, NULL, 0x9800, 0x80, 0x80, 0x80),
	.quadBlock[Bsp1_TurnBack1_Turbo_9800].draw_order_low = FACE_NegZ,
	.quadBlock[Bsp1_TurnBack2_Turbo_9800].draw_order_low = FACE_NegZ,
	
	NEW_BLOCK(Bsp1_TurnBack3_Turbo_1840, group4_turbopad_green, 0xD80,  0x2100, NULL, 0x1840, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp1_TurnBack4_Turbo_1840, group4_turbopad_green, 0x1080,0x2100, NULL, 0x1840, 0x80, 0x80, 0x80),
	.quadBlock[Bsp1_TurnBack3_Turbo_1840].terrain_type = 1,
	.quadBlock[Bsp1_TurnBack4_Turbo_1840].terrain_type = 1,
	
	NEW_BLOCK(Bsp1_TurnBack5, group4_placeHolder, 0xD80,  0x2400, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp1_TurnBack6, group4_placeHolder, 0x1080,0x2400, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp1_TurnBack7, group4_placeHolder, 0xD80,  0x2700, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp1_TurnBack8, group4_placeHolder, 0x1080,0x2700, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp1_TurnBack9, group4_placeHolder, 0xD80,  0x2A00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp1_TurnBack10, group4_placeHolder, 0x1080,0x2A00, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	TEX_2X2(Bsp1_TurnBack5, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp1_TurnBack6, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp1_TurnBack5].draw_order_low = 0x800000,
	.quadBlock[Bsp1_TurnBack6].draw_order_low = 0x1044000,
	
	TEX_2X2(Bsp1_TurnBack7, group4_tileCenter, group4_tileCenter, group4_tileCenter, group4_tileCenter),
	.quadBlock[Bsp1_TurnBack7].draw_order_low = 0x1044000,
	
	TEX_2X2(Bsp1_TurnBack8, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp1_TurnBack8].draw_order_low = 0x1044000,
	
	TEX_2X2(Bsp1_TurnBack9, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp1_TurnBack9].draw_order_low = 0x1984000,
	
	// TODO: TurnBack10 corner
	
	// ======= End of BSP block =========
	
	// fall back down,
	// here experiment with USF jump
	
	NEW_BLOCK(Bsp4_StraightWay1, group4_placeHolder, 0xD80, 0x1B00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp4_StraightWay2, group4_placeHolder, 0x1080, 0x1B00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp4_StraightWay3, group4_placeHolder, 0xD80, 0x1800, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp4_StraightWay4, group4_placeHolder, 0x1080, 0x1800, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp4_StraightWay5, group4_placeHolder, 0xD80, 0x1500, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp4_StraightWay6, group4_placeHolder, 0x1080, 0x1500, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp4_StraightWay7, group4_placeHolder, 0xD80, 0x1200, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp4_StraightWay8, group4_placeHolder, 0x1080, 0x1200, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp4_StraightWay9, group4_placeHolder, 0xD80, 0xF00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp4_StraightWay10, group4_placeHolder, 0x1080, 0xF00, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	TEX_2X2(Bsp4_StraightWay1, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp4_StraightWay2, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp4_StraightWay1].draw_order_low = 0x800000,
	.quadBlock[Bsp4_StraightWay2].draw_order_low = 0x1044000,
	TEX_2X2(Bsp4_StraightWay3, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp4_StraightWay4, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp4_StraightWay3].draw_order_low = 0x800000,
	.quadBlock[Bsp4_StraightWay4].draw_order_low = 0x1044000,
	TEX_2X2(Bsp4_StraightWay5, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp4_StraightWay6, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp4_StraightWay5].draw_order_low = 0x800000,
	.quadBlock[Bsp4_StraightWay6].draw_order_low = 0x1044000,
	TEX_2X2(Bsp4_StraightWay7, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp4_StraightWay8, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp4_StraightWay7].draw_order_low = 0x800000,
	.quadBlock[Bsp4_StraightWay8].draw_order_low = 0x1044000,
	TEX_2X2(Bsp4_StraightWay9, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp4_StraightWay10, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp4_StraightWay9].draw_order_low = 0x800000,
	.quadBlock[Bsp4_StraightWay10].draw_order_low = 0x1044000,
	
	NEW_BLOCK(Bsp4_StraightWay11_Turbo_9800, group4_turbopad_green, 0xD80, 0xC00, NULL, 0x9800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp4_StraightWay12_Turbo_1840, group4_turbopad_green, 0xD80, 0xC00, NULL, 0x1840, 0x80, 0x80, 0x80),
	.quadBlock[Bsp4_StraightWay12_Turbo_1840].terrain_type = 1,
	.quadBlock[Bsp4_StraightWay11_Turbo_9800].draw_order_low = FACE_NegZ,
	
	NEW_BLOCK(Bsp4_StraightWay13, group4_placeHolder, 0xD80, 0x900, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp4_StraightWay14, group4_placeHolder, 0x1080, 0x900, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	TEX_2X2(Bsp4_StraightWay13, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp4_StraightWay14, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp4_StraightWay13].draw_order_low = 0x800000,
	.quadBlock[Bsp4_StraightWay14].draw_order_low = 0x1044000,
	
	SET_POSY_FLAT(Bsp4_StraightWay1,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay2,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay3,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay4,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay5,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay6,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay7,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay8,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay9,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay10,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay11_Turbo_9800,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay12_Turbo_1840,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay13,-0x300),
	SET_POSY_FLAT(Bsp4_StraightWay14,-0x300),
	
	// ====== End of BSP block =========

	NEW_BLOCK(Bsp2_StraightWay15, group4_placeHolder, 0xD80, 0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_StraightWay16, group4_placeHolder, 0x1080, 0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_StraightWay17, group4_placeHolder, 0xD80, 0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_StraightWay18, group4_placeHolder, 0x1080, 0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	SET_POSY_FLAT(Bsp2_StraightWay15,-0x300),
	SET_POSY_FLAT(Bsp2_StraightWay16,-0x300),
	SET_POSY_FLAT(Bsp2_StraightWay17,-0x300),
	SET_POSY_FLAT(Bsp2_StraightWay18,-0x300),
	
	NEW_BLOCK(Bsp2_TurnRight1, group4_placeHolder, 0x1380, 0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_TurnRight2, group4_placeHolder, 0x1380, 0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_TurnRight3, group4_placeHolder, 0x1680, 0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_TurnRight4, group4_placeHolder, 0x1680, 0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_TurnRight5, group4_placeHolder, 0x1980, 0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_TurnRight6, group4_placeHolder, 0x1980, 0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_TurnRight7, group4_placeHolder, 0x1C80, 0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_TurnRight8, group4_placeHolder, 0x1C80, 0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	// TR, TL, BR, BL
	TEX_2X2(Bsp2_TurnRight1, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_TurnRight2, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_TurnRight1].draw_order_low = 0x808100,
	.quadBlock[Bsp2_TurnRight2].draw_order_low = 0x1984000,
	
	TEX_2X2(Bsp2_TurnRight3, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_TurnRight4, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_TurnRight3].draw_order_low = 0x808100,
	.quadBlock[Bsp2_TurnRight4].draw_order_low = 0x1984000,
	
	TEX_2X2(Bsp2_TurnRight5, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_TurnRight6, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_TurnRight5].draw_order_low = 0x808100,
	.quadBlock[Bsp2_TurnRight6].draw_order_low = 0x1984000,
	
	SET_POSY_FLAT(Bsp2_TurnRight1,-0x300),
	SET_POSY_FLAT(Bsp2_TurnRight2,-0x300),
	SET_POSY_FLAT(Bsp2_TurnRight3,-0x300),
	SET_POSY_FLAT(Bsp2_TurnRight4,-0x300),
	SET_POSY_FLAT(Bsp2_TurnRight5,-0x300),
	SET_POSY_FLAT(Bsp2_TurnRight6,-0x300),
	
	MAKE_RAMP(
		Bsp2_TurnRight7, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp2_TurnRight8, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_TurnRight7, -0x300, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_TurnRight8, -0x300, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	TEX_2X2(Bsp2_TurnRight7, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp2_TurnRight7].draw_order_low = 0x1044000,
	
	// TODO: CORNER
	//TEX_2X2(Bsp2_TurnRight8, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	//.quadBlock[Bsp2_TurnRight8].draw_order_low = 0x1044000,
	
	NEW_BLOCK(Bsp2_Middle_Turbo_1840, group4_turbopad_green, 0x1C80, 0, NULL, 0x1840, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_Middle_Turbo_9800, group4_turbopad_green, 0x1C80, 0, NULL, 0x9800, 0x80, 0x80, 0x80),
	.quadBlock[Bsp2_Middle_Turbo_1840].terrain_type = 1,
	.quadBlock[Bsp2_Middle_Turbo_9800].draw_order_low = FACE_NegZ,
	
	MAKE_RAMP(
		Bsp2_Middle_Turbo_1840, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp2_Middle_Turbo_9800, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_Middle_Turbo_1840, -0x300, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_Middle_Turbo_9800, -0x300, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	NEW_BLOCK(Bsp2_GoBack0, group4_placeHolder, 0x1C80, -0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_GoBack1, group4_placeHolder, 0x1C80, -0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_GoBack2, group4_placeHolder, 0x1980, -0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_GoBack3, group4_placeHolder, 0x1980, -0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_GoBack4, group4_placeHolder, 0x1680, -0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_GoBack5, group4_placeHolder, 0x1680, -0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	TEX_2X2(Bsp2_GoBack0, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp2_GoBack0].draw_order_low = 0x1044000,
	
	//TEX_2X2(Bsp2_GoBack1, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge), // TODO: CORNER
	//.quadBlock[Bsp2_GoBack1].draw_order_low = 0x1984000,
	
	TEX_2X2(Bsp2_GoBack3, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_GoBack2, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_GoBack3].draw_order_low = 0x808100,
	.quadBlock[Bsp2_GoBack2].draw_order_low = 0x1984000,
	TEX_2X2(Bsp2_GoBack5, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_GoBack4, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_GoBack5].draw_order_low = 0x808100,
	.quadBlock[Bsp2_GoBack4].draw_order_low = 0x1984000,
	
	NEW_BLOCK(Bsp2_GoBack6, group4_placeHolder, 0x1380, -0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_GoBack7, group4_placeHolder, 0x1380, -0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	TEX_2X2(Bsp2_GoBack7, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_GoBack6, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_GoBack7].draw_order_low = 0x808100,
	.quadBlock[Bsp2_GoBack6].draw_order_low = 0x1984000,
	
	MAKE_RAMP(
		Bsp2_GoBack0, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp2_GoBack1, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_GoBack0, -0x300, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_GoBack1, -0x300, 0x180, // index, height
		2,5,0, // low 3 vertices
		8,6,4, // mid 3 vertices
		3,7,1 // high 3 vertices
	),

	SET_POSY_FLAT(Bsp2_GoBack2,-0x300),
	SET_POSY_FLAT(Bsp2_GoBack3,-0x300),
	SET_POSY_FLAT(Bsp2_GoBack4,-0x300),
	SET_POSY_FLAT(Bsp2_GoBack5,-0x300),
	SET_POSY_FLAT(Bsp2_GoBack6,-0x300),
	SET_POSY_FLAT(Bsp2_GoBack7,-0x300),
	
	NEW_BLOCK(Bsp2_TowardsRamp1, group4_placeHolder, 0xD80, -0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_TowardsRamp2, group4_placeHolder, 0x1080, -0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_TowardsRamp3, group4_placeHolder, 0xD80, -0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_TowardsRamp4, group4_placeHolder, 0x1080, -0x600, NULL, 0x1800, 0x80, 0x80, 0x80),

	TEX_2X2(Bsp2_TowardsRamp4, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_TowardsRamp2, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_TowardsRamp4].draw_order_low = 0x808100,
	.quadBlock[Bsp2_TowardsRamp2].draw_order_low = 0x1984000,
	TEX_2X2(Bsp2_TowardsRamp3, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_TowardsRamp1, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_TowardsRamp3].draw_order_low = 0x808100,
	.quadBlock[Bsp2_TowardsRamp1].draw_order_low = 0x1984000,

	SET_POSY_FLAT(Bsp2_TowardsRamp1,-0x300),
	SET_POSY_FLAT(Bsp2_TowardsRamp2,-0x300),
	SET_POSY_FLAT(Bsp2_TowardsRamp3,-0x300),
	SET_POSY_FLAT(Bsp2_TowardsRamp4,-0x300),
	
	// === Last turn, back to startline ===
	
	NEW_BLOCK(Bsp2_RampUp1, group4_placeHolder, 0xA80, -0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_RampUp2_Turbo_9800, group4_turbopad_gray, 0xA80, -0x600, NULL, 0x9800, 0x80, 0x80, 0x80),
	.quadBlock[Bsp2_RampUp2_Turbo_9800].draw_order_low = FACE_NegX,
	
	MAKE_RAMP(
		Bsp2_RampUp1, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp2_RampUp2_Turbo_9800, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_RampUp1, -0x300, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_RampUp2_Turbo_9800, -0x300, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	NEW_BLOCK(Bsp2_RampUp3_Turbo_9800, group4_turbopad_green, 0x780, -0x300, NULL, 0x9800, 0x80, 0x80, 0x80),
	NEW_BLOCK(Bsp2_RampUp4, group4_placeHolder, 0x780, -0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	.quadBlock[Bsp2_RampUp3_Turbo_9800].draw_order_low = FACE_NegX,
	
	MAKE_RAMP(
		Bsp2_RampUp3_Turbo_9800, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	MAKE_RAMP(
		Bsp2_RampUp4, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_RampUp3_Turbo_9800, -0x180, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_RampUp4, -0x180, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	NEW_BLOCK(Bsp2_RampUp5_Turbo_1840, group4_turbopad_gray, 0xA80, -0x600, NULL, 0x1840, 0x80, 0x80, 0x80),
	
	MAKE_RAMP(
		Bsp2_RampUp5_Turbo_1840, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_RampUp5_Turbo_1840, -0x300, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	NEW_BLOCK(Bsp2_RampUp6_Turbo_1840, group4_turbopad_green, 0x780, -0x300, NULL, 0x1840, 0x80, 0x80, 0x80),
	
	MAKE_RAMP(
		Bsp2_RampUp6_Turbo_1840, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		Bsp2_RampUp6_Turbo_1840, -0x180, 0x180, // index, height
		3,7,1, // low 3 vertices
		8,6,4, // mid 3 vertices
		2,5,0 // high 3 vertices
	),
	
	// turn into turbo, if flagsQ is 0x1840
	// 1 for normal, 2 for super turbo
	.quadBlock[Bsp2_RampUp5_Turbo_1840].terrain_type = 2,
	.quadBlock[Bsp2_RampUp6_Turbo_1840].terrain_type = 1,
	
	TEX_2X2(Bsp2_RampUp4, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_RampUp1, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_RampUp4].draw_order_low = 0x808100,
	.quadBlock[Bsp2_RampUp1].draw_order_low = 0x1984000,
	
	#define SET_ID(y, x) .quadBlock[x].blockID = y-x
	
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+0),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+1),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+2),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+3),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+4),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+5),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+6),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+7),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+8),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+9),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+10),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+11),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+12),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+13),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+14),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+15),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+16),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+17),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+18),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+19),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+20),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+21),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+22),
	SET_ID(Bsp0_Last,Bsp0_FirstBlock+23),
	
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+0),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+1),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+2),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+3),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+4),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+5),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+6),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+7),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+8),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+9),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+10),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+11),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+12),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+13),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+14),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+15),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+16),
	SET_ID(Bsp1_Last,Bsp1_FirstBlock+17),
	
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+0),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+1),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+2),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+3),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+4),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+5),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+6),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+7),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+8),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+9),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+10),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+11),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+12),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+13),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+14),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+15),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+16),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+17),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+18),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+19),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+20),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+21),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+22),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+23),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+24),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+25),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+26),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+27),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+28),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+29),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+30),
	SET_ID(Bsp2_Last,Bsp2_FirstBlock+31),
	
	SET_ID(Bsp3_Last,Bsp3_FirstBlock+0),
	SET_ID(Bsp3_Last,Bsp3_FirstBlock+1),
	SET_ID(Bsp3_Last,Bsp3_FirstBlock+2),
	SET_ID(Bsp3_Last,Bsp3_FirstBlock+3),
	SET_ID(Bsp3_Last,Bsp3_FirstBlock+4),
	SET_ID(Bsp3_Last,Bsp3_FirstBlock+5),
	SET_ID(Bsp3_Last,Bsp3_FirstBlock+6),
	SET_ID(Bsp3_Last,Bsp3_FirstBlock+7),

	SET_ID(Bsp4_Last,Bsp4_FirstBlock+0),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+1),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+2),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+3),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+4),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+5),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+6),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+7),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+8),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+9),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+10),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+11),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+12),
	SET_ID(Bsp4_Last,Bsp4_FirstBlock+13),
	
	#define SET_CHECKPOINT(cpi, block) \
		.quadBlock[block].checkpointIndex = cpi
	
	// startline must have last checkpoint (min dist)
	SET_CHECKPOINT(CPI_OnSpawn, Bsp0_BehindStart1),
	SET_CHECKPOINT(CPI_OnSpawn, Bsp0_BehindStart2),
	SET_CHECKPOINT(CPI_OnSpawn, Bsp0_BehindStart3),
	SET_CHECKPOINT(CPI_OnSpawn, Bsp0_BehindStart4),
	SET_CHECKPOINT(CPI_OnSpawn, Bsp0_StartLine1),
	SET_CHECKPOINT(CPI_OnSpawn, Bsp0_StartLine2),
	
	// right after startline must have first checkpoint (max dist)
	SET_CHECKPOINT(CPI_AfterSpawn, Bsp0_AfterStart1),
	SET_CHECKPOINT(CPI_AfterSpawn, Bsp0_AfterStart2),
	
	SET_CHECKPOINT(CPI_DownRamp1, Bsp0_DownRamp1),
	SET_CHECKPOINT(CPI_DownRamp1, Bsp0_DownRamp2),
	SET_CHECKPOINT(CPI_DownRamp1, Bsp0_DownRamp3),
	SET_CHECKPOINT(CPI_DownRamp1, Bsp0_DownRamp4),
	SET_CHECKPOINT(CPI_DownRamp1, Bsp0_DownRamp5),
	SET_CHECKPOINT(CPI_DownRamp1, Bsp0_DownRamp6),
	
	SET_CHECKPOINT(CPI_FlatDip, Bsp0_FlatDip1),
	SET_CHECKPOINT(CPI_FlatDip, Bsp0_FlatDip2),
	SET_CHECKPOINT(CPI_FlatDip, Bsp0_FlatDip3),
	
	SET_CHECKPOINT(CPI_UpRamp1, Bsp0_UpRamp1),
	SET_CHECKPOINT(CPI_UpRamp1, Bsp0_UpRamp2_Turbo_9800),
	SET_CHECKPOINT(CPI_UpRamp1, Bsp0_UpRamp3),
	SET_CHECKPOINT(CPI_UpRamp1, Bsp0_UpRamp4),
	SET_CHECKPOINT(CPI_UpRamp1, Bsp0_UpRamp5_Turbo_9800),
	SET_CHECKPOINT(CPI_UpRamp1, Bsp0_UpRamp6),
	SET_CHECKPOINT(CPI_UpRamp1, Bsp0_UpRamp7_Turbo_1840),
	SET_CHECKPOINT(CPI_UpRamp1, Bsp0_UpRamp8_Turbo_1840),
	
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnLeft1),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnLeft2),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnLeft3_Turbo_9800),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnLeft4_Turbo_9800),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnLeft5_Turbo_1840),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnLeft6_Turbo_1840),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnLeft7),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnLeft8),
	
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack1_Turbo_9800),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack2_Turbo_9800),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack3_Turbo_1840),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack4_Turbo_1840),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack5),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack6),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack7),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack8),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack9),
	SET_CHECKPOINT(CPI_Turn180, Bsp1_TurnBack10),
	
	SET_CHECKPOINT(CPI_Turn180, Bsp3_FlatTop1),
	SET_CHECKPOINT(CPI_Turn180, Bsp3_FlatTop2),
	SET_CHECKPOINT(CPI_Turn180, Bsp3_FlatTop3),
	SET_CHECKPOINT(CPI_Turn180, Bsp3_FlatTop4),
	SET_CHECKPOINT(CPI_Turn180, Bsp3_FlatTop5),
	SET_CHECKPOINT(CPI_Turn180, Bsp3_FlatTop6),
	SET_CHECKPOINT(CPI_Turn180, Bsp3_FlatTop7),
	SET_CHECKPOINT(CPI_Turn180, Bsp3_FlatTop8),
	
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay1),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay2),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay3),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay4),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay5),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay6),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay7),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay8),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay9),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay10),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay11_Turbo_9800),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay12_Turbo_1840),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay13),
	SET_CHECKPOINT(CPI_FlatRun, Bsp4_StraightWay14),
	
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_StraightWay15),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_StraightWay16),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_StraightWay17),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_StraightWay18),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_TurnRight1),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_TurnRight2),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_TurnRight3),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_TurnRight4),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_TurnRight5),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_TurnRight6),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_TurnRight7),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_TurnRight8),
	
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_Middle_Turbo_9800),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_Middle_Turbo_1840),
	
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_GoBack0),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_GoBack1),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_GoBack2),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_GoBack3),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_GoBack4),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_GoBack5),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_GoBack6),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_GoBack7),
	
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_TowardsRamp1),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_TowardsRamp2),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_TowardsRamp3),
	SET_CHECKPOINT(CPI_FlatRun, Bsp2_TowardsRamp4),
	
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp1),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp2_Turbo_9800),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp3_Turbo_9800),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp4),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp5_Turbo_1840),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp6_Turbo_1840),
	
	#define DIST_PER_NODE 0x400
	
	.checkpointNodes =
	{
		// first node[0] is always the node
		// after crossing startline, used to get track length
		
		[CPI_AfterSpawn] =
		{
			.pos = {0, 0, 0x300},
			.distToFinish = (NUM_CHECKPOINT-CPI_AfterSpawn-1)*DIST_PER_NODE+1,
			.nextIndex_forward = CPI_DownRamp1,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_OnSpawn,
			.nextIndex_right = -1,
		},
		
		[CPI_DownRamp1] =
		{
			.pos = {0, -0x200, 0x900},
			.distToFinish = (NUM_CHECKPOINT-CPI_DownRamp1-1)*DIST_PER_NODE+1,
			.nextIndex_forward = CPI_FlatDip,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_AfterSpawn,
			.nextIndex_right = -1,
		},
		
		[CPI_FlatDip] =
		{
			.pos = {0x180, -0x500, 0xED4},
			.distToFinish = (NUM_CHECKPOINT-CPI_FlatDip-1)*DIST_PER_NODE+1,
			.nextIndex_forward = CPI_UpRamp1,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_DownRamp1,
			.nextIndex_right = -1,
		},
		
		[CPI_UpRamp1] =
		{
			.pos = {0, -0x200, 0x1800},
			.distToFinish = (NUM_CHECKPOINT-CPI_UpRamp1-1)*DIST_PER_NODE+1,
			.nextIndex_forward = CPI_Turn180,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_FlatDip,
			.nextIndex_right = -1,
		},
		
		[CPI_Turn180] =
		{
			.pos = {0x1A0, 0, 0x28A0},
			.distToFinish = (NUM_CHECKPOINT-CPI_Turn180-1)*DIST_PER_NODE+1,
			.nextIndex_forward = CPI_FlatRun,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_UpRamp1,
			.nextIndex_right = -1,
		},
		
		[CPI_FlatRun] =
		{
			.pos = {0xF00, -0x300, 0x1800},
			.distToFinish = (NUM_CHECKPOINT-CPI_FlatRun-1)*DIST_PER_NODE+1,
			.nextIndex_forward = CPI_UpRamp2,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_Turn180,
			.nextIndex_right = -1,
		},
		
		[CPI_UpRamp2] =
		{
			.pos = {0xF00, -0x300, -0x480},
			.distToFinish = (NUM_CHECKPOINT-CPI_UpRamp2-1)*DIST_PER_NODE+1,
			.nextIndex_forward = CPI_OnSpawn,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_FlatRun,
			.nextIndex_right = -1,
		},
		
		// last node,
		// must be the spawn, with dist=1
		[CPI_OnSpawn] =
		{
			.pos = {0, 0, 0},
			.distToFinish = (NUM_CHECKPOINT-CPI_OnSpawn-1)*DIST_PER_NODE+1,
			.nextIndex_forward = CPI_AfterSpawn,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_UpRamp2,
			.nextIndex_right = -1,
		}
	},
	
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
				.min = {-0x8000, -0x490, -0x8000},
				.max = {0x8000, 0x066E, 0x8000}
			},
			
			.data =
			{
				.branch =
				{
					// need more info on this
					.axis = {0x1000, 0x0, 0x0, 0xFF40},
					
					// 0x4000 signifies leaf node
					.childID = {0x2, 0x1},
				}
			}
		},
		
		// branch for side of map opposite to startline
		[1] =
		{
			.flag = 0,
			.id = 1,
			.box =
			{
				.min = {0x300, -0x490, -0x800},
				.max = {0x2100, 0x100, 0x2E00}
			},
			
			.data =
			{
				.branch =
				{
					// need more info on this
					.axis = {0, 0x0, 0x1000, 0xFF40},
					
					// 0x4000 signifies leaf node
					.childID = {0x3, 0x4004},
				}
			}
		},
		
		// branch for startline side
		[2] =
		{
			.flag = 0,
			.id = 2,
			.box =
			{
				.min = {-0x300, -0x490, -0x800},
				.max = {0x300, 0x100, 0x2E00}
			},
			
			.data =
			{
				.branch =
				{
					// need more info on this
					.axis = {0, 0x0, 0x1000, 0xFF40},
					
					// 0x4000 signifies leaf node
					.childID = {0x4005, 0x4006},
				}
			}
		},
		
		// leaf with u-turn and drop
		[3] =
		{
			.flag = 0,
			.id = 3,
			.box =
			{
				.min = {0x300, -0x490, 0x781},
				.max = {0x2100, 0x100, 0x2E00}
			},
			
			.data =
			{
				.branch =
				{
					// need more info on this
					.axis = {0, 0x0, 0x1000, 0xFF40},
					
					// 0x4000 signifies leaf node
					.childID = {0x4007, 0x4008},
				}
			}
		},
		
		// leaf yet to come
		[4] =
		{
			.flag = 0x1,
			.id = 4,
			.box =
			{
				.min = {0x300, -0x490, -0x800},
				.max = {0x2100, 0x100, 0x77F}
			},
			
			.data =
			{
				.leaf =
				{
					// empty, should be [64]
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = Bsp2_BlockCount,
					.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[Bsp2_FirstBlock])-4
				}
			}
		},
	
		// leaf with startline
		[5] =
		{
			.flag = 0x1,
			.id = 5,
			.box =
			{
				.min = {-0x300, -0x490, -0x800},
				.max = {0x300, 0x100, 0x1D00} // see if that cuts it
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = Bsp0_BlockCount,
					.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[Bsp0_FirstBlock])-4
				}
			}
		},
		
		// leaf with start of 180 U-Turn
		[6] =
		{
			.flag = 0x1,
			.id = 6,
			.box =
			{
				.min = {-0x300, -0x300, 0x1D00},
				.max = {0x300, 0x100, 0x2E00}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = Bsp3_BlockCount,
					.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[Bsp3_FirstBlock])-4
				}
			}
		},

		[7] =
		{
			.flag = 0x1,
			.id = 7,
			.box =
			{
				.min = {0xB00, -0x490, 0x781},
				.max = {0x1300, -0x100, 0x1F00}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = Bsp4_BlockCount,
					.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[Bsp4_FirstBlock])-4
				}
			}
		},
		
		// leaf with end of 180 U-Turn
		[8] = 
		{
			.flag = 0x1,
			.id = 8,
			.box =
			{
				.min = {0x300, -0x300, 0x1F00},
				.max = {0x1300, 0x100, 0x2E00}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = Bsp1_BlockCount,
					.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[Bsp1_FirstBlock])-4
				}
			}
		}
	},
	
	.leafList =
	{
		// PVS_DROPNONE
		-1,-1,
	},
	
	.faceList =
	{
		// PVS_DROPNONE
		-1,-1,-1,-1,-1,
	},
	
	.pvs =
	{
		[PVS_DROPNONE] =
		{
			.visLeafSrc = OFFSETOF(struct LevelFile, leafList[2*PVS_DROPNONE]),
			.visFaceSrc = OFFSETOF(struct LevelFile, faceList[5*PVS_DROPNONE]),
			.visInstSrc = 0,
			.visExtraSrc = 0,
		},
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
	.VisMem_bspList_RenderListP1[2*4+1] = OFFSETOF(struct LevelFile, bsp[4])-4,
	.VisMem_bspList_RenderListP2[2*4+1] = OFFSETOF(struct LevelFile, bsp[4])-4,
	.VisMem_bspList_RenderListP3[2*4+1] = OFFSETOF(struct LevelFile, bsp[4])-4,
	.VisMem_bspList_RenderListP4[2*4+1] = OFFSETOF(struct LevelFile, bsp[4])-4,
	
	.VisMem_bspList_RenderListP1[2*5+1] = OFFSETOF(struct LevelFile, bsp[5])-4,
	.VisMem_bspList_RenderListP2[2*5+1] = OFFSETOF(struct LevelFile, bsp[5])-4,
	.VisMem_bspList_RenderListP3[2*5+1] = OFFSETOF(struct LevelFile, bsp[5])-4,
	.VisMem_bspList_RenderListP4[2*5+1] = OFFSETOF(struct LevelFile, bsp[5])-4,
	
	.VisMem_bspList_RenderListP1[2*6+1] = OFFSETOF(struct LevelFile, bsp[6])-4,
	.VisMem_bspList_RenderListP2[2*6+1] = OFFSETOF(struct LevelFile, bsp[6])-4,
	.VisMem_bspList_RenderListP3[2*6+1] = OFFSETOF(struct LevelFile, bsp[6])-4,
	.VisMem_bspList_RenderListP4[2*6+1] = OFFSETOF(struct LevelFile, bsp[6])-4,
	
	.VisMem_bspList_RenderListP1[2*7+1] = OFFSETOF(struct LevelFile, bsp[7])-4,
	.VisMem_bspList_RenderListP2[2*7+1] = OFFSETOF(struct LevelFile, bsp[7])-4,
	.VisMem_bspList_RenderListP3[2*7+1] = OFFSETOF(struct LevelFile, bsp[7])-4,
	.VisMem_bspList_RenderListP4[2*7+1] = OFFSETOF(struct LevelFile, bsp[7])-4,
	
	.VisMem_bspList_RenderListP1[2*8+1] = OFFSETOF(struct LevelFile, bsp[8])-4,
	.VisMem_bspList_RenderListP2[2*8+1] = OFFSETOF(struct LevelFile, bsp[8])-4,
	.VisMem_bspList_RenderListP3[2*8+1] = OFFSETOF(struct LevelFile, bsp[8])-4,
	.VisMem_bspList_RenderListP4[2*8+1] = OFFSETOF(struct LevelFile, bsp[8])-4,
	
	.map =
	{
		(46+NUM_BLOCKS*6)<<2,
		
		OFFSETOF(struct LevelFile, level.ptr_mesh_info)-4,
		OFFSETOF(struct LevelFile, level.visMem)-4,
		OFFSETOF(struct LevelFile, level.ptrSpawnType1)-4,
		OFFSETOF(struct LevelFile, level.ptr_restart_points)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, mInfo.ptrVertexArray)-4,
		OFFSETOF(struct LevelFile, mInfo.bspRoot)-4,
		OFFSETOF(struct LevelFile, bsp[4].data.leaf.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, bsp[5].data.leaf.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, bsp[6].data.leaf.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, bsp[7].data.leaf.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, bsp[8].data.leaf.ptrQuadBlockArray)-4,
		OFFSETOF(struct LevelFile, pvs[0].visLeafSrc)-4,
		OFFSETOF(struct LevelFile, pvs[0].visFaceSrc)-4,
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
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP1[2*4+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP2[2*4+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP3[2*4+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP4[2*4+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP1[2*5+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP2[2*5+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP3[2*5+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP4[2*5+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP1[2*6+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP2[2*6+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP3[2*6+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP4[2*6+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP1[2*7+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP2[2*7+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP3[2*7+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP4[2*7+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP1[2*8+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP2[2*8+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP3[2*8+1])-4,
		OFFSETOF(struct LevelFile, VisMem_bspList_RenderListP4[2*8+1])-4,
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
		PTR_MAP_QUADBLOCK(63),
		PTR_MAP_QUADBLOCK(64),
		PTR_MAP_QUADBLOCK(65),
		PTR_MAP_QUADBLOCK(66),
		PTR_MAP_QUADBLOCK(67),
		PTR_MAP_QUADBLOCK(68),
		PTR_MAP_QUADBLOCK(69),
		PTR_MAP_QUADBLOCK(70),
		PTR_MAP_QUADBLOCK(71),
		PTR_MAP_QUADBLOCK(72),
		PTR_MAP_QUADBLOCK(73),
		PTR_MAP_QUADBLOCK(74),
		PTR_MAP_QUADBLOCK(75),
		PTR_MAP_QUADBLOCK(76),
		PTR_MAP_QUADBLOCK(77),
		PTR_MAP_QUADBLOCK(78),
		PTR_MAP_QUADBLOCK(79),
		PTR_MAP_QUADBLOCK(80),
		PTR_MAP_QUADBLOCK(81),
		PTR_MAP_QUADBLOCK(82),
		PTR_MAP_QUADBLOCK(83),
		PTR_MAP_QUADBLOCK(84),
		PTR_MAP_QUADBLOCK(85),
		PTR_MAP_QUADBLOCK(86),
		PTR_MAP_QUADBLOCK(87),
		PTR_MAP_QUADBLOCK(88),
		PTR_MAP_QUADBLOCK(89),
		PTR_MAP_QUADBLOCK(90),
		PTR_MAP_QUADBLOCK(91),
		PTR_MAP_QUADBLOCK(92),
		PTR_MAP_QUADBLOCK(93),
		PTR_MAP_QUADBLOCK(94),
		PTR_MAP_QUADBLOCK(95),
		PTR_MAP_QUADBLOCK(97),
	},
};
