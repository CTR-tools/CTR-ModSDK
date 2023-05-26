#include <common.h>
#include "../../levelBuilder.h"

#define NUM_BLOCKS 54

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
	struct WarpballPathNode noderespawnsthing[NUM_BLOCKS]; // all empty, this is a battle map
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
	
	// spawn
	NEW_BLOCK(0, group4_tileEdge, -0x180, 0, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(1, group4_tileEdge, 0x180, 0, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	// top/bottom left/right assuming you're rotation is 0,0,0
	TEX_2X2(0, group4_tileEdge, group4_tileCenter, group4_checkerEdge, group4_checkerCenter),
	TEX_2X2(1, group4_tileCenter, group4_tileEdge, group4_checkerCenter, group4_checkerEdge),
	.quadBlock[0].draw_order_low = 0x800000, // rotate checker
	.quadBlock[1].draw_order_low = 0x1044000, // rotation
	
	// flat, in front of spawn
	NEW_BLOCK(2, group4_placeHolder, -0x180, 0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(3, group4_placeHolder, 0x180, 0x300, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	// ramp down (1/3)
	NEW_BLOCK(4, group4_placeHolder, -0x180, 0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(5, group4_placeHolder, 0x180, 0x600, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	MAKE_RAMP(
		4, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		5, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		4, -0x180, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		5, -0x180, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	// ramp down (2/3)
	NEW_BLOCK(6, group4_placeHolder, -0x180, 0x900, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(7, group4_placeHolder, 0x180, 0x900, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	MAKE_RAMP(
		6, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		7, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		6, -0x300, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		7, -0x300, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	// ramp down (3/3)
	NEW_BLOCK(8, group4_placeHolder, -0x180, 0xC00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(9, group4_placeHolder, 0x180, 0xC00, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	MAKE_RAMP(
		8, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		9, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		8, -0x480, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		9, -0x480, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	// === Edit LevVertex to put hole in left ==
	// Make it a triangular hole between two quadblocks
	
	// bottom between ramps
	NEW_BLOCK(10, group4_placeHolder, -0x180, 0xF00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(11, group4_placeHolder, 0x180, 0xF00, NULL, 0x1800, 0x80, 0x80, 0x80),
	SET_POSY_FLAT(10,-0x480),
	SET_POSY_FLAT(11,-0x480),
	
	// bottom between ramps
	NEW_BLOCK(12, group4_placeHolder, -0x180, 0x1200, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(13, group4_placeHolder, 0x180, 0x1200, NULL, 0x1800, 0x80, 0x80, 0x80),
	SET_POSY_FLAT(12,-0x480),
	SET_POSY_FLAT(13,-0x480),
	
	// move 12 to arrow sign
	
	// ===== need hole in bottom ======
	
	// ramp up (1/3)
	NEW_BLOCK(14, group4_placeHolder, -0x180, 0x1500, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(15, group4_turbopad_green, 0x180, 0x1500, NULL, 0x1800, 0x80, 0x80, 0x80),
	.quadBlock[15].draw_order_low = 0x380E000,
	
	MAKE_RAMP(
		14, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	MAKE_RAMP(
		15, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		14, -0x480, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		15, -0x480, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	// ramp up (2/3)
	NEW_BLOCK(16, group4_placeHolder, -0x180, 0x1800, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(17, group4_placeHolder, 0x180, 0x1800, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	MAKE_RAMP(
		16, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	MAKE_RAMP(
		17, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		16, -0x300, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		17, -0x300, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	// ramp up (3/3)
	NEW_BLOCK(18, group4_turbopad_gray, -0x180, 0x1B00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(19, group4_placeHolder, 0x180, 0x1B00, NULL, 0x1800, 0x80, 0x80, 0x80),
	.quadBlock[18].draw_order_low = 0x380E000,
	
	MAKE_RAMP(
		18, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	MAKE_RAMP(
		19, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		18, -0x180, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		19, -0x180, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	// flat, forward
	NEW_BLOCK(20, group4_placeHolder, -0x180, 0x1E00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(21, group4_placeHolder, 0x180, 0x1E00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(22, group4_placeHolder, -0x180, 0x2100, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(23, group4_placeHolder, 0x180, 0x2100, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(24, group4_placeHolder, -0x180, 0x2400, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(25, group4_placeHolder, 0x180, 0x2400, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(26, group4_placeHolder, -0x180, 0x2700, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(27, group4_placeHolder, 0x180, 0x2700, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(28, group4_placeHolder, -0x180, 0x2A00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(29, group4_placeHolder, 0x180, 0x2A00, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	// turbo on ramp-up(3/3)
	NEW_BLOCK(30, group4_turbopad_gray, -0x180, 0x1B00, NULL, 0x1840, 0x80, 0x80, 0x80),
	NEW_BLOCK(31, group4_turbopad_green, 0x180, 0x1500, NULL, 0x1840, 0x80, 0x80, 0x80),
	.quadBlock[30].draw_order_low = 0x380E000,
	.quadBlock[31].draw_order_low = 0x380E000,
	
	MAKE_RAMP(
		30, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	MAKE_RAMP(
		31, 0x180, // index, height
		2,8,3, // low 3 vertices
		5,6,7, // mid 3 vertices
		0,4,1 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		30, -0x180, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	SET_POSY_RAMP(
		31, -0x480, 0x180, // index, height
		0,4,1, // low 3 vertices
		5,6,7, // mid 3 vertices
		2,8,3 // high 3 vertices
	),
	
	// turn into turbo, if flagsQ is 0x1840
	// 1 for normal, 2 for super turbo
	.quadBlock[30].terrain_type = 2,
	.quadBlock[31].terrain_type = 1,
	
	// ==== End of BSP block =====
	
	// flat, turn 90
	NEW_BLOCK(32, group4_placeHolder, 0x480, 0x2700, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(33, group4_placeHolder, 0x480, 0x2A00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(34, group4_placeHolder, 0x780, 0x2700, NULL, 0x1800, 0x80, 0x80, 0x80), // boost
	NEW_BLOCK(35, group4_placeHolder, 0x780, 0x2A00, NULL, 0x1800, 0x80, 0x80, 0x80), // boost
	NEW_BLOCK(36, group4_placeHolder, 0xA80, 0x2700, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(37, group4_placeHolder, 0xA80, 0x2A00, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	// flat, turn 180
	NEW_BLOCK(38, group4_placeHolder, 0xD80, 0x1E00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(39, group4_placeHolder, 0x1080, 0x1E00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(40, group4_placeHolder, 0xD80,  0x2100, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(41, group4_placeHolder, 0x1080,0x2100, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(42, group4_placeHolder, 0xD80,  0x2400, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(43, group4_placeHolder, 0x1080,0x2400, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(44, group4_placeHolder, 0xD80,  0x2700, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(45, group4_placeHolder, 0x1080,0x2700, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(46, group4_placeHolder, 0xD80,  0x2A00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(47, group4_placeHolder, 0x1080,0x2A00, NULL, 0x1800, 0x80, 0x80, 0x80),
	
	// fall back down,
	// here experiment with USF jump
	
	NEW_BLOCK(48, group4_placeHolder, 0xD80, 0x1B00, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(49, group4_placeHolder, 0x1080, 0x1B00, NULL, 0x1800, 0x80, 0x80, 0x80),
	SET_POSY_FLAT(48,-0x300),
	SET_POSY_FLAT(49,-0x300),
	
	NEW_BLOCK(50, group4_placeHolder, 0xD80, 0x1800, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(51, group4_placeHolder, 0x1080, 0x1800, NULL, 0x1800, 0x80, 0x80, 0x80),
	SET_POSY_FLAT(50,-0x300),
	SET_POSY_FLAT(51,-0x300),
	
	NEW_BLOCK(52, group4_placeHolder, 0xD80, 0x1500, NULL, 0x1800, 0x80, 0x80, 0x80),
	NEW_BLOCK(53, group4_placeHolder, 0x1080, 0x1500, NULL, 0x1800, 0x80, 0x80, 0x80),
	SET_POSY_FLAT(52,-0x300),
	SET_POSY_FLAT(53,-0x300),
	
	
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
	
	.quadBlock[32].blockID = 54-32-1,
	.quadBlock[33].blockID = 54-33-1,
	.quadBlock[34].blockID = 54-34-1,
	.quadBlock[35].blockID = 54-35-1,
	.quadBlock[36].blockID = 54-36-1,
	.quadBlock[37].blockID = 54-37-1,
	.quadBlock[38].blockID = 54-38-1,
	.quadBlock[39].blockID = 54-39-1,
	.quadBlock[40].blockID = 54-40-1,
	.quadBlock[41].blockID = 54-41-1,
	.quadBlock[42].blockID = 54-42-1,
	.quadBlock[43].blockID = 54-43-1,
	.quadBlock[44].blockID = 54-44-1,
	.quadBlock[45].blockID = 54-45-1,
	.quadBlock[46].blockID = 54-46-1,
	.quadBlock[47].blockID = 54-47-1,
	.quadBlock[48].blockID = 54-48-1,
	.quadBlock[49].blockID = 54-49-1,
	.quadBlock[50].blockID = 54-50-1,
	.quadBlock[51].blockID = 54-51-1,
	.quadBlock[52].blockID = 54-50-1,
	.quadBlock[53].blockID = 54-51-1,
	
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
				.min = {-0x8000, -0x800, -0x8000},
				.max = {0x8000, 0x066E, 0x8000}
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
			.flag = 0x1,
			.id = 1,
			.box =
			{
				// random box that exists nowhere
				.min = {0x300, -0x800, -0x1100},
				.max = {0x2100, 0x400, 0x4500}
			},
			
			.data =
			{
				.leaf =
				{
					.unk1 = 0,
					.bspHitboxArray = 0,
					.numQuads = 22,
					.ptrQuadBlockArray = OFFSETOF(struct LevelFile, quadBlock[32])-4
				}
			}
		},
		
		// leaf with 1 quadblock
		[2] =
		{
			.flag = 0x1,
			.id = 2,
			.box =
			{
				// random box that exists nowhere
				.min = {-0x1100, -0x800, -0x1100},
				.max = {0x300, 0x400, 0x4500}
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
	},
};
