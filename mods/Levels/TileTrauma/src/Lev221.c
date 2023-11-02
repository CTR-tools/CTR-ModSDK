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
	struct IconGroup4 group4_checkerEdge;
	struct IconGroup4 group4_checkerCenter;
	struct IconGroup4 group4_tileEdge;
	struct IconGroup4 group4_tileCenter;
	struct IconGroup4 group4_tileCorner;
	struct IconGroup4 group4_placeHolder;
	
	// NonScroll "Low" textures
	// TODO: See RoadToRainbow
	
	// Scroll textures, one "duplicate" per set,
	// Duplicate MUST have higher texY than original
	struct IconGroup4 turbo_pad[10];
	struct IconGroup4 super_turbo_pad[10];
	struct IconGroup4 turbo_pad_dup;
	struct IconGroup4 super_turbo_pad_dup;
	
	// CycleTex_LEV requires data in THIS order
	struct AnimTex turbo_pad_anim;
	struct IconGroup4* TPA_ptrarray[10];
	struct AnimTex super_turbo_pad_anim;
	struct IconGroup4* STPA_ptrarray[10];
	void* animTexTerminator;
	
	// SpawnData
	struct SpawnType1 ptrSpawnType1;
	void* spawnType1Pointers[3];
	short EndRaceCam[10];
	
	// Geometry
	struct QuadBlock quadBlock[NUM_BLOCKS];
	struct LevVertex levVertex[NUM_BLOCKS*9];
	
	// Checkpoints
	struct CheckpointNode checkpointNodes[NUM_CHECKPOINT];
	
	// Visibility
	struct BSP bsp[9];
	struct PVS pvs[NUM_PVS];
	int leafList[2*NUM_PVS];
	int faceList[5*NUM_PVS];
	struct VisMem visMem;
	
	// leave empty
	// DstMemcpy must be big for PVS to copy into,
	// RenderList must be big enough for 2 pointers to all BSP nodes
	int VisMem_bitIndex_DstMemcpyP1[8];
	int VisMem_bspList_RenderListP1[9*2];
	int VisMem_bitIndex_DstMemcpyP2[8];
	int VisMem_bspList_RenderListP2[9*2];
	int VisMem_bitIndex_DstMemcpyP3[8];
	int VisMem_bspList_RenderListP3[9*2];
	int VisMem_bitIndex_DstMemcpyP4[8];
	int VisMem_bspList_RenderListP4[9*2];
	
	struct NavHeader* navTable[3];
	struct NavHeader navHeader1;
	struct NavFrame navFrame[609];
	
	int map[(3)+1];
};

struct LevelFile file =
{
	.ptrMap = LEV_OFFSETOF(map[0]),
	
	.level =
	{
		.ptr_mesh_info = LEV_OFFSETOF(mInfo),
		.visMem = LEV_OFFSETOF(visMem),
		.ptr_anim_tex = LEV_OFFSETOF(turbo_pad_anim),
		
		// the game will add +0x400 to the yaw of spawn positions automatically
		// we should probably look into why this even happens...
		
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
		
		.configFlags = 1,
		
		.glowGradient =
		{
			// top, bottom
			0x20, 0x0,
			
			// top
			0x801020, // blue
			
			// bottom
			0x102080, // red
		},
		
		.ptrSpawnType1 = LEV_OFFSETOF(ptrSpawnType1),
		
		// red
		.clearColor[0].rgb = {0x80, 0x20, 0x10},
		.clearColor[0].enable = 1,
		
		// red
		.clearColor[1].rgb = {0x80, 0x20, 0x10},
		.clearColor[1].enable = 1,
		
		// blue
		.clearColor[2].rgb = {0x20, 0x10, 0x80},
		.clearColor[2].enable = 1,
		
		// only non-zero for Race maps
		// battle maps need array, but still set CNT to zero
		.cnt_restart_points = NUM_CHECKPOINT,
		.ptr_restart_points = LEV_OFFSETOF(checkpointNodes[0]),
		
		.LevNavTable = LEV_OFFSETOF(navTable[0]),
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
		.numBspNodes = 9,
	},
	
	.group4_checkerEdge =
	{
		.far =    ImageName_Blend(512, 0, 32, 128, 64, 64, BPP_4, TRANS_50),
		.middle = ImageName_Blend(512, 0, 32, 128, 64, 64, BPP_4, TRANS_50),
		.near =   ImageName_Blend(512, 0, 32, 128, 64, 64, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(512, 0, 32, 128, 64, 64, BPP_4, TRANS_50)
	},
	
	.group4_checkerCenter =
	{	
		.far =    ImageName_Blend(528, 0, 32, 129, 64, 64, BPP_4, TRANS_50),
		.middle = ImageName_Blend(528, 0, 32, 129, 64, 64, BPP_4, TRANS_50),
		.near =   ImageName_Blend(528, 0, 32, 129, 64, 64, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(528, 0, 32, 129, 64, 64, BPP_4, TRANS_50)
	},
	
	.group4_tileEdge =
	{	
		.far =    ImageName_Blend(544, 0, 32, 130, 64, 64, BPP_4, TRANS_50),
		.middle = ImageName_Blend(544, 0, 32, 130, 64, 64, BPP_4, TRANS_50),
		.near =   ImageName_Blend(544, 0, 32, 130, 64, 64, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(544, 0, 32, 130, 64, 64, BPP_4, TRANS_50)
	},
	
	.group4_tileCenter =
	{	
		.far =    ImageName_Blend(560, 0, 32, 131, 64, 64, BPP_4, TRANS_50),
		.middle = ImageName_Blend(560, 0, 32, 131, 64, 64, BPP_4, TRANS_50),
		.near =   ImageName_Blend(560, 0, 32, 131, 64, 64, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(560, 0, 32, 131, 64, 64, BPP_4, TRANS_50)
	},
	
	.group4_tileCorner =
	{
		.far =    ImageName_Blend(576, 0, 32, 135, 64, 64, BPP_4, TRANS_50),
		.middle = ImageName_Blend(576, 0, 32, 135, 64, 64, BPP_4, TRANS_50),
		.near =   ImageName_Blend(576, 0, 32, 135, 64, 64, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(576, 0, 32, 135, 64, 64, BPP_4, TRANS_50)
	},
	
	.group4_placeHolder =
	{
		.far =    ImageName_Blend(592, 0, 32, 132, 16, 16, BPP_4, TRANS_50),
		.middle = ImageName_Blend(592, 0, 32, 132, 16, 16, BPP_4, TRANS_50),
		.near =   ImageName_Blend(592, 0, 32, 132, 16, 16, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(592, 0, 32, 132, 16, 16, BPP_4, TRANS_50)
	},
	
	.turbo_pad =
	{
		// Dont move to LevelBuilder.h,
		// This changes depending on the level
		
		#define SAME_TURBO_SINGLE(XX) \
		ImageName_Scroll(596, 16, 32, 133, 32, 16, BPP_4, TRANS_50, XX)
		
		#define SAME_TURBO_GROUP(XX) \
		{ \
			.far    = SAME_TURBO_SINGLE(XX), \
			.middle = SAME_TURBO_SINGLE(XX), \
			.near   = SAME_TURBO_SINGLE(XX), \
			.mosaic = SAME_TURBO_SINGLE(XX), \
		}
		
		[0] = SAME_TURBO_GROUP(0),
		[1] = SAME_TURBO_GROUP(2),
		[2] = SAME_TURBO_GROUP(3),
		[3] = SAME_TURBO_GROUP(5),
		[4] = SAME_TURBO_GROUP(6),
		[5] = SAME_TURBO_GROUP(8),
		[6] = SAME_TURBO_GROUP(10),
		[7] = SAME_TURBO_GROUP(11),
		[8] = SAME_TURBO_GROUP(13),
		[9] = SAME_TURBO_GROUP(14),
	},
	
	.turbo_pad_dup =
	{
		.far    = ImageName_Blend(596, 0, 32, 133, 32, 16, BPP_4, TRANS_50),
		.middle = ImageName_Blend(596, 0, 32, 133, 32, 16, BPP_4, TRANS_50),
		.near   = ImageName_Blend(596, 0, 32, 133, 32, 16, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(596, 0, 32, 133, 32, 16, BPP_4, TRANS_50),	
	},
	
	// texture made by Avery (@TheMagicJam)
	.super_turbo_pad =
	{
		// Dont move to LevelBuilder.h,
		// This changes depending on the level
		
		#define SAME_SUPERTURBO_SINGLE(XX) \
		ImageName_Scroll(604, 16, 32, 134, 32, 16, BPP_4, TRANS_50, XX)
		
		#define SAME_SUPERTURBO_GROUP(XX) \
		{ \
			.far    = SAME_SUPERTURBO_SINGLE(XX), \
			.middle = SAME_SUPERTURBO_SINGLE(XX), \
			.near   = SAME_SUPERTURBO_SINGLE(XX), \
			.mosaic = SAME_SUPERTURBO_SINGLE(XX), \
		}
		
		[0] = SAME_SUPERTURBO_GROUP(0),
		[1] = SAME_SUPERTURBO_GROUP(2),
		[2] = SAME_SUPERTURBO_GROUP(3),
		[3] = SAME_SUPERTURBO_GROUP(5),
		[4] = SAME_SUPERTURBO_GROUP(6),
		[5] = SAME_SUPERTURBO_GROUP(8),
		[6] = SAME_SUPERTURBO_GROUP(10),
		[7] = SAME_SUPERTURBO_GROUP(11),
		[8] = SAME_SUPERTURBO_GROUP(13),
		[9] = SAME_SUPERTURBO_GROUP(14),
	},
	
	.super_turbo_pad_dup =
	{
		.far    = ImageName_Blend(604, 0, 32, 134, 32, 16, BPP_4, TRANS_50),
		.middle = ImageName_Blend(604, 0, 32, 134, 32, 16, BPP_4, TRANS_50),
		.near   = ImageName_Blend(604, 0, 32, 134, 32, 16, BPP_4, TRANS_50),
		.mosaic = ImageName_Blend(604, 0, 32, 134, 32, 16, BPP_4, TRANS_50),
	},

	.turbo_pad_anim =
	{
		.ptrActiveTex = LEV_OFFSETOF(turbo_pad[0]),
		.numFrames = 10,
		.frameDuration = 0,
		.shiftFactor = 0,
		.frameIndex = 0,
	},
	
	.TPA_ptrarray =
	{
		LEV_OFFSETOF(turbo_pad[0]),
		LEV_OFFSETOF(turbo_pad[1]),
		LEV_OFFSETOF(turbo_pad[2]),
		LEV_OFFSETOF(turbo_pad[3]),
		LEV_OFFSETOF(turbo_pad[4]),
		LEV_OFFSETOF(turbo_pad[5]),
		LEV_OFFSETOF(turbo_pad[6]),
		LEV_OFFSETOF(turbo_pad[7]),
		LEV_OFFSETOF(turbo_pad[8]),
		LEV_OFFSETOF(turbo_pad[9]),
	},

	.super_turbo_pad_anim =
	{
		.ptrActiveTex = LEV_OFFSETOF(super_turbo_pad[0]),
		.numFrames = 10,
		.frameDuration = 0,
		.shiftFactor = 0,
		.frameIndex = 0,
	},
	
	.STPA_ptrarray =
	{
		LEV_OFFSETOF(super_turbo_pad[0]),
		LEV_OFFSETOF(super_turbo_pad[1]),
		LEV_OFFSETOF(super_turbo_pad[2]),
		LEV_OFFSETOF(super_turbo_pad[3]),
		LEV_OFFSETOF(super_turbo_pad[4]),
		LEV_OFFSETOF(super_turbo_pad[5]),
		LEV_OFFSETOF(super_turbo_pad[6]),
		LEV_OFFSETOF(super_turbo_pad[7]),
		LEV_OFFSETOF(super_turbo_pad[8]),
		LEV_OFFSETOF(super_turbo_pad[9])
	},
	
	// CycleTex_LEV uses pointer to first AnimTex
	// to symbolize the end of the final ptrArray
	.animTexTerminator = 
		LEV_OFFSETOF(turbo_pad_anim),
	
	// this must exist, or else camera fly-in
	// checks for "count" without nullptr check,
	// and crashes dereferencing nullptr on real PSX
	.ptrSpawnType1 =
	{
		.count = 3,
	},
	
	.spawnType1Pointers =
	{
		0,					// map
		0,					// 231 spawns
		LEV_OFFSETOF(EndRaceCam)
		// camera path intro (fly-in)
		// n tropy ghost
		// n oxide ghost
	},
	
	.EndRaceCam =
	{
		// number of cameras
		2, 
		
		// camera1:
			1, // start on respawnPoint[1],
			4, // mode 4 (sit in pos, lookAt driver)
			0x800,0x400,0x900,
			
		// only camera1 happens cause NavFrame
		// has to encode which respawnPoint the AI is nearest to,
		// will come back to this when we have a full editor
			
		// camera2:
			2, // start on respawnPoint[6],
			4, // mode 4 (sit in pos, lookAt driver)
			0,0,0x1000,
	},
		
	// +z is forward
	// +x is left, not right
	
	// behind spawn
	NEW_BLOCK(Bsp0_BehindStart1, group4_placeHolder, -0x180, -0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_BehindStart2, group4_placeHolder, 0x180, -0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_BehindStart3, group4_placeHolder, -0x180, -0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_BehindStart4, group4_placeHolder, 0x180, -0x300, NULL, 0x1800, 0x808080),
	
	// BR, BL, TR, TL assuming you're rotation is 0,0,0
	TEX_2X2(Bsp0_BehindStart1, group4_tileCorner, group4_tileEdge, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_BehindStart2, group4_tileEdge, group4_tileCorner, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_BehindStart1].draw_order_low = 0x802100,
	.quadBlock[Bsp0_BehindStart2].draw_order_low = 0x1044100,
	
	TEX_2X2(Bsp0_BehindStart3, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_BehindStart4, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_BehindStart3].draw_order_low = 0x800000,
	.quadBlock[Bsp0_BehindStart4].draw_order_low = 0x1044000,
	
	// spawn
	NEW_BLOCK(Bsp0_StartLine1, group4_tileEdge, -0x180, 0, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_StartLine2, group4_tileEdge, 0x180, 0, NULL, 0x1800, 0x808080),
	
	// BR, BL, TR, TL assuming you're rotation is 0,0,0
	TEX_2X2(Bsp0_StartLine1, group4_tileEdge, group4_tileCenter, group4_checkerEdge, group4_checkerCenter),
	TEX_2X2(Bsp0_StartLine2, group4_tileCenter, group4_tileEdge, group4_checkerCenter, group4_checkerEdge),
	.quadBlock[Bsp0_StartLine1].draw_order_low = 0x800000, // rotate checker
	.quadBlock[Bsp0_StartLine2].draw_order_low = 0x1044000, // rotation
	
	// flat, in front of spawn
	NEW_BLOCK(Bsp0_AfterStart1, group4_placeHolder, -0x180, 0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_AfterStart2, group4_placeHolder, 0x180, 0x300, NULL, 0x1800, 0x808080),
	
	TEX_2X2(Bsp0_AfterStart1, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	TEX_2X2(Bsp0_AfterStart2, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp0_AfterStart1].draw_order_low = 0x800000,
	.quadBlock[Bsp0_AfterStart2].draw_order_low = 0x1044000,
	
	// ramp down (1/3)
	NEW_BLOCK(Bsp0_DownRamp1, group4_placeHolder, -0x180, 0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_DownRamp2, group4_placeHolder, 0x180, 0x600, NULL, 0x1800, 0x808080),
	
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
	NEW_BLOCK(Bsp0_DownRamp3, group4_placeHolder, -0x180, 0x900, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_DownRamp4, group4_placeHolder, 0x180, 0x900, NULL, 0x1800, 0x808080),
	
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
	NEW_BLOCK(Bsp0_DownRamp5, group4_placeHolder, -0x180, 0xC00, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_DownRamp6, group4_placeHolder, 0x180, 0xC00, NULL, 0x1800, 0x808080),
	
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
	NEW_BLOCK(Bsp0_FlatDip1, group4_placeHolder, -0x180, 0x1200, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_FlatDip2, group4_placeHolder, 0x180, 0xF00, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_FlatDip3, group4_placeHolder, 0x180, 0x1200, NULL, 0x1800, 0x808080),
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
	NEW_BLOCK(Bsp0_UpRamp1, group4_placeHolder, -0x180, 0x1500, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_UpRamp2_Turbo_9800, group4_placeHolder, 0x180, 0x1500, NULL, 0x9800, 0x808080),
	
	.quadBlock[Bsp0_UpRamp2_Turbo_9800].ptr_texture_mid[0] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[Bsp0_UpRamp2_Turbo_9800].ptr_texture_mid[1] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[Bsp0_UpRamp2_Turbo_9800].ptr_texture_mid[2] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[Bsp0_UpRamp2_Turbo_9800].ptr_texture_mid[3] = LEV_OFFSETOF(turbo_pad_anim)|1,
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
	NEW_BLOCK(Bsp0_UpRamp3, group4_placeHolder, -0x180, 0x1800, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp0_UpRamp4, group4_placeHolder, 0x180, 0x1800, NULL, 0x1800, 0x808080),
	
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
	NEW_BLOCK(Bsp0_UpRamp5_Turbo_9800, group4_placeHolder, -0x180, 0x1B00, NULL, 0x9800, 0x808080),
	NEW_BLOCK(Bsp0_UpRamp6, group4_placeHolder, 0x180, 0x1B00, NULL, 0x1800, 0x808080),
	.quadBlock[Bsp0_UpRamp5_Turbo_9800].ptr_texture_mid[0] = LEV_OFFSETOF(super_turbo_pad_anim)|1,
	.quadBlock[Bsp0_UpRamp5_Turbo_9800].ptr_texture_mid[1] = LEV_OFFSETOF(super_turbo_pad_anim)|1,
	.quadBlock[Bsp0_UpRamp5_Turbo_9800].ptr_texture_mid[2] = LEV_OFFSETOF(super_turbo_pad_anim)|1,
	.quadBlock[Bsp0_UpRamp5_Turbo_9800].ptr_texture_mid[3] = LEV_OFFSETOF(super_turbo_pad_anim)|1,
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
	NEW_BLOCK(Bsp0_UpRamp7_Turbo_1840, group4_placeHolder, -0x180, 0x1B00, NULL, 0x1840, 0x808080),
	NEW_BLOCK(Bsp0_UpRamp8_Turbo_1840, group4_placeHolder, 0x180, 0x1500, NULL, 0x1840, 0x808080),
	
	// turn into turbo, if flagsQ is 0x1840
	// 1 for normal, 2 for super turbo
	.quadBlock[Bsp0_UpRamp7_Turbo_1840].terrain_type = 2,
	.quadBlock[Bsp0_UpRamp8_Turbo_1840].terrain_type = 1,
	.quadBlock[Bsp0_UpRamp8_Turbo_1840].ptr_texture_mid[0] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[Bsp0_UpRamp8_Turbo_1840].ptr_texture_mid[1] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[Bsp0_UpRamp8_Turbo_1840].ptr_texture_mid[2] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[Bsp0_UpRamp8_Turbo_1840].ptr_texture_mid[3] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[Bsp0_UpRamp7_Turbo_1840].ptr_texture_mid[0] = LEV_OFFSETOF(super_turbo_pad_anim)|1,
	.quadBlock[Bsp0_UpRamp7_Turbo_1840].ptr_texture_mid[1] = LEV_OFFSETOF(super_turbo_pad_anim)|1,
	.quadBlock[Bsp0_UpRamp7_Turbo_1840].ptr_texture_mid[2] = LEV_OFFSETOF(super_turbo_pad_anim)|1,
	.quadBlock[Bsp0_UpRamp7_Turbo_1840].ptr_texture_mid[3] = LEV_OFFSETOF(super_turbo_pad_anim)|1,
	
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
	NEW_BLOCK(Bsp3_FlatTop1, group4_placeHolder, -0x180, 0x2100, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp3_FlatTop2, group4_placeHolder, 0x180, 0x2100, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp3_FlatTop3, group4_placeHolder, -0x180, 0x2400, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp3_FlatTop4, group4_placeHolder, 0x180, 0x2400, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp3_FlatTop5, group4_placeHolder, -0x180, 0x2700, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp3_FlatTop6, group4_placeHolder, 0x180, 0x2700, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp3_FlatTop7, group4_placeHolder, -0x180, 0x2A00, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp3_FlatTop8, group4_placeHolder, 0x180, 0x2A00, NULL, 0x1800, 0x808080),
	
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
	
	// BR, BL, TR, TL assuming you're rotation is 0,0,0
	TEX_2X2(Bsp3_FlatTop7, group4_tileEdge, group4_tileCenter, group4_tileCorner, group4_tileEdge),
	.quadBlock[Bsp3_FlatTop7].draw_order_low = 0x1800000,
	
	// ==== End of BSP block =====
	
	// flat, turn 90
	NEW_BLOCK(Bsp1_TurnLeft1, group4_placeHolder, 0x480, 0x2700, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp1_TurnLeft2, group4_placeHolder, 0x480, 0x2A00, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp1_TurnLeft3_Turbo_9800, group4_placeHolder, 0x780, 0x2700, NULL, 0x9800, 0x808080), // boost
	NEW_BLOCK(Bsp1_TurnLeft4_Turbo_9800, group4_placeHolder, 0x780, 0x2A00, NULL, 0x9800, 0x808080), // boost
	NEW_BLOCK(Bsp1_TurnLeft5_Turbo_1840, group4_placeHolder, 0x780, 0x2700, NULL, 0x1840, 0x808080), // boost
	NEW_BLOCK(Bsp1_TurnLeft6_Turbo_1840, group4_placeHolder, 0x780, 0x2A00, NULL, 0x1840, 0x808080), // boost
	NEW_BLOCK(Bsp1_TurnLeft7, group4_placeHolder, 0xA80, 0x2700, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp1_TurnLeft8, group4_placeHolder, 0xA80, 0x2A00, NULL, 0x1800, 0x808080),
	.quadBlock[Bsp1_TurnLeft3_Turbo_9800].draw_order_low = FACE_PosX,
	.quadBlock[Bsp1_TurnLeft4_Turbo_9800].draw_order_low = FACE_PosX,
	.quadBlock[Bsp1_TurnLeft5_Turbo_1840].terrain_type = 1,
	.quadBlock[Bsp1_TurnLeft6_Turbo_1840].terrain_type = 1,

	.quadBlock[Bsp1_TurnLeft3_Turbo_9800].ptr_texture_mid[0] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[Bsp1_TurnLeft3_Turbo_9800].ptr_texture_mid[1] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[Bsp1_TurnLeft3_Turbo_9800].ptr_texture_mid[2] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[Bsp1_TurnLeft3_Turbo_9800].ptr_texture_mid[3] = LEV_OFFSETOF(turbo_pad_anim)|1,

	.quadBlock[Bsp1_TurnLeft4_Turbo_9800].ptr_texture_mid[0] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[Bsp1_TurnLeft4_Turbo_9800].ptr_texture_mid[1] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[Bsp1_TurnLeft4_Turbo_9800].ptr_texture_mid[2] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[Bsp1_TurnLeft4_Turbo_9800].ptr_texture_mid[3] = LEV_OFFSETOF(turbo_pad_anim)|1,
	
	// BR, BL, TR, TL
	TEX_2X2(Bsp1_TurnLeft1, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp1_TurnLeft2, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp1_TurnLeft1].draw_order_low = 0x808100,
	.quadBlock[Bsp1_TurnLeft2].draw_order_low = 0x1984000,
	
	// BR, BL, TR, TL
	TEX_2X2(Bsp1_TurnLeft7, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp1_TurnLeft8, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp1_TurnLeft7].draw_order_low = 0x808100,
	.quadBlock[Bsp1_TurnLeft8].draw_order_low = 0x1984000,
	
	// flat, turn 180
	NEW_BLOCK(Bsp1_TurnBack1_Turbo_9800, group4_placeHolder, 0xD80, 0x2100, NULL, 0x9800, 0x808080),
	NEW_BLOCK(Bsp1_TurnBack2_Turbo_9800, group4_placeHolder, 0x1080, 0x2100, NULL, 0x9800, 0x808080),
	.quadBlock[Bsp1_TurnBack1_Turbo_9800].draw_order_low = FACE_NegZ,
	.quadBlock[Bsp1_TurnBack2_Turbo_9800].draw_order_low = FACE_NegZ,

	.quadBlock[Bsp1_TurnBack1_Turbo_9800].ptr_texture_mid[0] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[Bsp1_TurnBack1_Turbo_9800].ptr_texture_mid[1] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[Bsp1_TurnBack1_Turbo_9800].ptr_texture_mid[2] = LEV_OFFSETOF(turbo_pad_anim)|1,
	.quadBlock[Bsp1_TurnBack1_Turbo_9800].ptr_texture_mid[3] = LEV_OFFSETOF(turbo_pad_anim)|1,

	SetQuadBlockAnimTex(Bsp1_TurnBack2_Turbo_9800, turbo_pad_anim),
	
	NEW_BLOCK(Bsp1_TurnBack3_Turbo_1840, group4_placeHolder, 0xD80,  0x2100, NULL, 0x1840, 0x808080),
	NEW_BLOCK(Bsp1_TurnBack4_Turbo_1840, group4_placeHolder, 0x1080,0x2100, NULL, 0x1840, 0x808080),
	SetQuadBlockAnimTex(Bsp1_TurnBack3_Turbo_1840, turbo_pad_anim),
	SetQuadBlockAnimTex(Bsp1_TurnBack4_Turbo_1840, turbo_pad_anim),
	.quadBlock[Bsp1_TurnBack3_Turbo_1840].terrain_type = 1,
	.quadBlock[Bsp1_TurnBack4_Turbo_1840].terrain_type = 1,
	
	NEW_BLOCK(Bsp1_TurnBack5, group4_placeHolder, 0xD80,  0x2400, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp1_TurnBack6, group4_placeHolder, 0x1080,0x2400, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp1_TurnBack7, group4_placeHolder, 0xD80,  0x2700, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp1_TurnBack8, group4_placeHolder, 0x1080,0x2700, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp1_TurnBack9, group4_placeHolder, 0xD80,  0x2A00, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp1_TurnBack10, group4_placeHolder, 0x1080,0x2A00, NULL, 0x1800, 0x808080),
	
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
	
	// BR, BL, TR, TL assuming you're rotation is 0,0,0
	TEX_2X2(Bsp1_TurnBack10, group4_tileCenter, group4_tileEdge, group4_tileEdge, group4_tileCorner),
	.quadBlock[Bsp1_TurnBack10].draw_order_low = 0x18c4000,
	
	// ======= End of BSP block =========
	
	// fall back down,
	// here experiment with USF jump
	
	NEW_BLOCK(Bsp4_StraightWay1, group4_placeHolder, 0xD80, 0x1B00, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay2, group4_placeHolder, 0x1080, 0x1B00, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay3, group4_placeHolder, 0xD80, 0x1800, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay4, group4_placeHolder, 0x1080, 0x1800, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay5, group4_placeHolder, 0xD80, 0x1500, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay6, group4_placeHolder, 0x1080, 0x1500, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay7, group4_placeHolder, 0xD80, 0x1200, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay8, group4_placeHolder, 0x1080, 0x1200, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay9, group4_placeHolder, 0xD80, 0xF00, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay10, group4_placeHolder, 0x1080, 0xF00, NULL, 0x1800, 0x808080),
	
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
	
	NEW_BLOCK(Bsp4_StraightWay11_Turbo_9800, group4_placeHolder, 0xD80, 0xC00, NULL, 0x9800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay12_Turbo_1840, group4_placeHolder, 0xD80, 0xC00, NULL, 0x1840, 0x808080),
	SetQuadBlockAnimTex(Bsp4_StraightWay11_Turbo_9800, turbo_pad_anim),
	SetQuadBlockAnimTex(Bsp4_StraightWay12_Turbo_1840, turbo_pad_anim),
	.quadBlock[Bsp4_StraightWay12_Turbo_1840].terrain_type = 1,
	.quadBlock[Bsp4_StraightWay11_Turbo_9800].draw_order_low = FACE_NegZ,
	
	NEW_BLOCK(Bsp4_StraightWay13, group4_placeHolder, 0xD80, 0x900, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp4_StraightWay14, group4_placeHolder, 0x1080, 0x900, NULL, 0x1800, 0x808080),
	
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

	NEW_BLOCK(Bsp2_StraightWay15, group4_placeHolder, 0xD80, 0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_StraightWay16, group4_placeHolder, 0x1080, 0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_StraightWay17, group4_placeHolder, 0xD80, 0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_StraightWay18, group4_placeHolder, 0x1080, 0x300, NULL, 0x1800, 0x808080),
	
	SET_POSY_FLAT(Bsp2_StraightWay15,-0x300),
	SET_POSY_FLAT(Bsp2_StraightWay16,-0x300),
	SET_POSY_FLAT(Bsp2_StraightWay17,-0x300),
	SET_POSY_FLAT(Bsp2_StraightWay18,-0x300),
	
	TEX_2X2(Bsp2_StraightWay15, group4_tileEdge, group4_tileCenter, group4_tileEdge, group4_tileCenter),
	.quadBlock[Bsp2_StraightWay15].draw_order_low = 0x800000,
	
	TEX_2X2(Bsp2_StraightWay16, group4_tileCenter, group4_tileCenter, group4_tileCenter, group4_tileCenter),
	.quadBlock[Bsp2_StraightWay16].draw_order_low = 0x1044000,
	
	// BR, BL, TR, TL
	TEX_2X2(Bsp2_StraightWay17, group4_tileCorner, group4_tileEdge, group4_tileEdge, group4_tileCenter),
	.quadBlock[Bsp2_StraightWay17].draw_order_low = 0x808100,
	
	TEX_2X2(Bsp2_StraightWay18, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	.quadBlock[Bsp2_StraightWay18].draw_order_low = 0x808100,
	
	NEW_BLOCK(Bsp2_TurnRight1, group4_placeHolder, 0x1380, 0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TurnRight2, group4_placeHolder, 0x1380, 0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TurnRight3, group4_placeHolder, 0x1680, 0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TurnRight4, group4_placeHolder, 0x1680, 0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TurnRight5, group4_placeHolder, 0x1980, 0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TurnRight6, group4_placeHolder, 0x1980, 0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TurnRight7, group4_placeHolder, 0x1C80, 0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TurnRight8, group4_placeHolder, 0x1C80, 0x600, NULL, 0x1800, 0x808080),
	
	// BR, BL, TR, TL
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
	
	// BR, BL, TR, TL assuming you're rotation is 0,0,0
	TEX_2X2(Bsp2_TurnRight8, group4_tileCenter, group4_tileEdge, group4_tileEdge, group4_tileCorner),
	.quadBlock[Bsp2_TurnRight8].draw_order_low = 0x18c4000,
	
	NEW_BLOCK(Bsp2_Middle_Turbo_1840, group4_placeHolder, 0x1C80, 0, NULL, 0x1840, 0x808080),
	NEW_BLOCK(Bsp2_Middle_Turbo_9800, group4_placeHolder, 0x1C80, 0, NULL, 0x9800, 0x808080),
	SetQuadBlockAnimTex(Bsp2_Middle_Turbo_1840, turbo_pad_anim),
	SetQuadBlockAnimTex(Bsp2_Middle_Turbo_9800, turbo_pad_anim),
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
	
	NEW_BLOCK(Bsp2_GoBack0, group4_placeHolder, 0x1C80, -0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_GoBack1, group4_placeHolder, 0x1C80, -0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_GoBack2, group4_placeHolder, 0x1980, -0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_GoBack3, group4_placeHolder, 0x1980, -0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_GoBack4, group4_placeHolder, 0x1680, -0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_GoBack5, group4_placeHolder, 0x1680, -0x600, NULL, 0x1800, 0x808080),
	
	TEX_2X2(Bsp2_GoBack0, group4_tileCenter, group4_tileEdge, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp2_GoBack0].draw_order_low = 0x1044000,
	
	TEX_2X2(Bsp2_GoBack1, group4_tileEdge, group4_tileCorner, group4_tileCenter, group4_tileEdge),
	.quadBlock[Bsp2_GoBack1].draw_order_low = 0x1044100,
	
	TEX_2X2(Bsp2_GoBack3, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_GoBack2, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_GoBack3].draw_order_low = 0x808100,
	.quadBlock[Bsp2_GoBack2].draw_order_low = 0x1984000,
	TEX_2X2(Bsp2_GoBack5, group4_tileEdge, group4_tileEdge, group4_tileCenter, group4_tileCenter),
	TEX_2X2(Bsp2_GoBack4, group4_tileCenter, group4_tileCenter, group4_tileEdge, group4_tileEdge),
	.quadBlock[Bsp2_GoBack5].draw_order_low = 0x808100,
	.quadBlock[Bsp2_GoBack4].draw_order_low = 0x1984000,
	
	NEW_BLOCK(Bsp2_GoBack6, group4_placeHolder, 0x1380, -0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_GoBack7, group4_placeHolder, 0x1380, -0x600, NULL, 0x1800, 0x808080),
	
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
	
	NEW_BLOCK(Bsp2_TowardsRamp1, group4_placeHolder, 0xD80, -0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TowardsRamp2, group4_placeHolder, 0x1080, -0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TowardsRamp3, group4_placeHolder, 0xD80, -0x600, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_TowardsRamp4, group4_placeHolder, 0x1080, -0x600, NULL, 0x1800, 0x808080),

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
	
	NEW_BLOCK(Bsp2_RampUp1, group4_placeHolder, 0xA80, -0x300, NULL, 0x1800, 0x808080),
	NEW_BLOCK(Bsp2_RampUp2_Turbo_9800, group4_placeHolder, 0xA80, -0x600, NULL, 0x9800, 0x808080),
	SetQuadBlockAnimTex(Bsp2_RampUp2_Turbo_9800, super_turbo_pad_anim),
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
	
	NEW_BLOCK(Bsp2_RampUp3_Turbo_9800, group4_placeHolder, 0x780, -0x300, NULL, 0x9800, 0x808080),
	NEW_BLOCK(Bsp2_RampUp4, group4_placeHolder, 0x780, -0x600, NULL, 0x1800, 0x808080),
	SetQuadBlockAnimTex(Bsp2_RampUp3_Turbo_9800, turbo_pad_anim),
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
	
	NEW_BLOCK(Bsp2_RampUp5_Turbo_1840, group4_placeHolder, 0xA80, -0x600, NULL, 0x1840, 0x808080),
	SetQuadBlockAnimTex(Bsp2_RampUp5_Turbo_1840, super_turbo_pad_anim),
	
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
	
	NEW_BLOCK(Bsp2_RampUp6_Turbo_1840, group4_placeHolder, 0x780, -0x300, NULL, 0x1840, 0x808080),
	SetQuadBlockAnimTex(Bsp2_RampUp6_Turbo_1840, turbo_pad_anim),
	
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
	
	// These dont go on BSP, and dont use SetID
	NEW_BLOCK(BspINV_FirstBlock+0, turbo_pad[0], 		0x6FFF, 0x6FFF, NULL, 0, 0x808080),
	NEW_BLOCK(BspINV_FirstBlock+1, super_turbo_pad[0], 	0x6FFF, 0x6FFF, NULL, 0, 0x808080),
	NEW_BLOCK(BspINV_FirstBlock+2, turbo_pad_dup, 		0x6FFF, 0x6FFF, NULL, 0, 0x808080),
	NEW_BLOCK(BspINV_FirstBlock+3, super_turbo_pad_dup, 0x6FFF, 0x6FFF, NULL, 0, 0x808080),
	
	#define SET_CHECKPOINT(cpi, block) \
		.quadBlock[block].checkpointIndex = cpi
	
	// ERROR: NMZ Alert!
	// Checkpoint[last] is reserved for the quadblocks that touch the startline from behind,
	// Checkpoint[0]    is reserved for the quadblocks that touch the startline from the front
	// The game is rigged not to grab someone on either of these checkpoints for any reason
	
	// By putting BehindStart1-4 on Checkpoint[last],
	// jumping from DownRamp1 and landing on BehindStart1-4
	// will be too far to determine crossing the line backwards,
	// and checkpoint[last] can't mask-grab for illegal shortcut distance,
	// therefore the lap becomes valid and the race is won in 12 seconds,
	// same mistake as Papu Pyramid
	
	// To fix NMZ, make a new checkpoint for BehindStart1-4,
	// Dont fix it though, let this be a lesson for all future maps
	
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
	
	SET_CHECKPOINT(CPI_LandJump, Bsp3_FlatTop1),
	SET_CHECKPOINT(CPI_LandJump, Bsp3_FlatTop2),
	SET_CHECKPOINT(CPI_LandJump, Bsp3_FlatTop3),
	SET_CHECKPOINT(CPI_LandJump, Bsp3_FlatTop4),
	SET_CHECKPOINT(CPI_LandJump, Bsp3_FlatTop5),
	SET_CHECKPOINT(CPI_LandJump, Bsp3_FlatTop6),
	
	SET_CHECKPOINT(CPI_Turn90, Bsp3_FlatTop7),
	SET_CHECKPOINT(CPI_Turn90, Bsp3_FlatTop8),
	
	SET_CHECKPOINT(CPI_Turn90, Bsp1_TurnLeft1),
	SET_CHECKPOINT(CPI_Turn90, Bsp1_TurnLeft2),
	SET_CHECKPOINT(CPI_Turn90, Bsp1_TurnLeft3_Turbo_9800),
	SET_CHECKPOINT(CPI_Turn90, Bsp1_TurnLeft4_Turbo_9800),
	SET_CHECKPOINT(CPI_Turn90, Bsp1_TurnLeft5_Turbo_1840),
	SET_CHECKPOINT(CPI_Turn90, Bsp1_TurnLeft6_Turbo_1840),
	
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
	
	SET_CHECKPOINT(CPI_Corner, Bsp2_StraightWay15),
	SET_CHECKPOINT(CPI_Corner, Bsp2_StraightWay16),
	SET_CHECKPOINT(CPI_Corner, Bsp2_StraightWay17),
	SET_CHECKPOINT(CPI_Corner, Bsp2_StraightWay18),
	SET_CHECKPOINT(CPI_Corner, Bsp2_TurnRight1),
	SET_CHECKPOINT(CPI_Corner, Bsp2_TurnRight2),
	
	SET_CHECKPOINT(CPI_PreTurbo, Bsp2_TurnRight3),
	SET_CHECKPOINT(CPI_PreTurbo, Bsp2_TurnRight4),
	SET_CHECKPOINT(CPI_PreTurbo, Bsp2_TurnRight5),
	SET_CHECKPOINT(CPI_PreTurbo, Bsp2_TurnRight6),
	SET_CHECKPOINT(CPI_PreTurbo, Bsp2_TurnRight7),
	SET_CHECKPOINT(CPI_PreTurbo, Bsp2_TurnRight8),
	
	SET_CHECKPOINT(CPI_PostTurbo, Bsp2_Middle_Turbo_9800),
	SET_CHECKPOINT(CPI_PostTurbo, Bsp2_Middle_Turbo_1840),
	
	SET_CHECKPOINT(CPI_PostTurbo, Bsp2_GoBack0),
	SET_CHECKPOINT(CPI_PostTurbo, Bsp2_GoBack1),
	SET_CHECKPOINT(CPI_PostTurbo, Bsp2_GoBack2),
	SET_CHECKPOINT(CPI_PostTurbo, Bsp2_GoBack3),
	SET_CHECKPOINT(CPI_PostTurbo, Bsp2_GoBack4),
	SET_CHECKPOINT(CPI_PostTurbo, Bsp2_GoBack5),
	
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_GoBack6),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_GoBack7),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_TowardsRamp1),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_TowardsRamp2),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_TowardsRamp3),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_TowardsRamp4),
	
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp1),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp2_Turbo_9800),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp3_Turbo_9800),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp4),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp5_Turbo_1840),
	SET_CHECKPOINT(CPI_UpRamp2, Bsp2_RampUp6_Turbo_1840),
	
	.checkpointNodes =
	{
		// first node[0] is always the node
		// after crossing startline, used to get track length
		
		[CPI_AfterSpawn] =
		{
			.pos = {0, 0, 0x300},
			.distToFinish = 0x1C00,
			.nextIndex_forward = CPI_DownRamp1,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_OnSpawn,
			.nextIndex_right = -1,
		},
		
		[CPI_DownRamp1] =
		{
			.pos = {0, -0x200, 0x900},
			.distToFinish = 0x1800,
			.nextIndex_forward = CPI_FlatDip,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_AfterSpawn,
			.nextIndex_right = -1,
		},
		
		[CPI_FlatDip] =
		{
			.pos = {0x180, -0x480, 0xED4},
			.distToFinish = 0x1400,
			.nextIndex_forward = CPI_UpRamp1,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_DownRamp1,
			.nextIndex_right = -1,
		},
		
		[CPI_UpRamp1] =
		{
			.pos = {0, -0x200, 0x1800},
			.distToFinish = 0x1000,
			.nextIndex_forward = CPI_LandJump,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_FlatDip,
			.nextIndex_right = -1,
		},
		
		[CPI_LandJump] =
		{
			.pos = {0x180, 0, 0x2200},
			.distToFinish = 0xE00,
			.nextIndex_forward = CPI_Turn90,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_UpRamp1,
			.nextIndex_right = -1,
		},
		
		
		[CPI_Turn90] =
		{
			.pos = {0x180, 0, 0x2800},
			.distToFinish = 0xC00,
			.nextIndex_forward = CPI_Turn180,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_LandJump,
			.nextIndex_right = -1,
		},
		
		
		[CPI_Turn180] =
		{
			.pos = {0xF00, 0, 0x2800},
			.distToFinish = 0xA00,
			.nextIndex_forward = CPI_FlatRun,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_Turn90,
			.nextIndex_right = -1,
		},
		
		[CPI_FlatRun] =
		{
			.pos = {0xF00, -0x300, 0x1800},
			.distToFinish = 0x800,
			.nextIndex_forward = CPI_Corner,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_Turn180,
			.nextIndex_right = -1,
		},
		
		[CPI_Corner] =
		{
			.pos = {0xF00, -0x300, 0x480},
			.distToFinish = 0x7F0,
			.nextIndex_forward = CPI_PreTurbo,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_FlatRun,
			.nextIndex_right = -1,
		},
		
		[CPI_PreTurbo] =
		{
			.pos = {0x1800, -0x300, 0x480},
			.distToFinish = 0x5B0,
			.nextIndex_forward = CPI_OnTurbo,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_Corner,
			.nextIndex_right = -1,
		},
		
		// dont spawn on here, just use it for FORWARD/BACKWARD
		[CPI_OnTurbo] =
		{
			.pos = {0x1C80, -0x180, 0},
			.distToFinish = 0x520,
			.nextIndex_forward = CPI_PostTurbo,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_PreTurbo,
			.nextIndex_right = -1,
		},
		
		[CPI_PostTurbo] =
		{
			.pos = {0x1800, -0x300, -0x480},
			.distToFinish = 0x490,
			.nextIndex_forward = CPI_UpRamp2,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_OnTurbo,
			.nextIndex_right = -1,
		},
		
		[CPI_UpRamp2] =
		{
			.pos = {0xF00, -0x300, -0x480},
			.distToFinish = 0x400,
			.nextIndex_forward = CPI_OnSpawn,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_PostTurbo,
			.nextIndex_right = -1,
		},
		
		// last node,
		// must be the spawn, with dist=1
		[CPI_OnSpawn] =
		{
			.pos = {0, 0, 0},
			.distToFinish = 1,
			.nextIndex_forward = CPI_AfterSpawn,
			.nextIndex_left = -1,
			.nextIndex_backward = CPI_UpRamp2,
			.nextIndex_right = -1,
		}
	},
	
	// ========== bsp ======================
	
	.bsp =
	{
		// root node, SplitX
		// children: Straightway+EndUTurn+EndTrack, Startline+StartUTurn
		BSP_BRANCH(0, SPLIT_X, 0x1, 0x2),
		
		// Straightway+EndUTurn+EndTrack, SplitZ
		// children: Straightway+EndUTurn, EndTrack
		BSP_BRANCH(1, SPLIT_Z, 0x3, 0x4),
		
		// Startline+StartUTurn, SplitZ,
		// children: Startline, StartUTurn
		BSP_BRANCH(2, SPLIT_Z, 0x5, 0x6),
		
		// Straightway+EndUTurn, SplitZ,
		// children: Straightway, EndUTurn, 
		BSP_BRANCH(3, SPLIT_Z, 0x7, 0x8),
		
		// EndTrack
		BSP_LEAF(4, Bsp2_FirstBlock, Bsp2_BlockCount),
	
		// Startline
		BSP_LEAF(5, Bsp0_FirstBlock, Bsp0_BlockCount),
		
		// StartUTurn
		BSP_LEAF(6, Bsp3_FirstBlock, Bsp3_BlockCount),

		// Straightway
		BSP_LEAF(7, Bsp4_FirstBlock, Bsp4_BlockCount),
		
		// EndUTurn
		BSP_LEAF(8, Bsp1_FirstBlock, Bsp1_BlockCount),
	},
	
	.leafList =
	{
		// PVS_DROPNONE
		(1<<(31-0)) |
		(1<<(31-1)) |
		(1<<(31-2)) |
		(1<<(31-3)) |
		(1<<(31-4)) |
		(1<<(31-5)) |
		(1<<(31-6)) |
		(1<<(31-7)) |
		(1<<(31-8)),
		
		-1,
	},
	
	.faceList =
	{
		// PVS_DROPNONE (-1 = 0b11111111111111111111111111111111)
		-1,-1,-1,-1,-1,
	},
	
	.pvs =
	{
		[PVS_DROPNONE] =
		{
			.visLeafSrc = LEV_OFFSETOF(leafList[2*PVS_DROPNONE]),
			.visFaceSrc = LEV_OFFSETOF(faceList[5*PVS_DROPNONE]),
			.visInstSrc = 0,
			.visExtraSrc = 0,
		},
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
	
	.navTable = {LEV_OFFSETOF(navHeader1), 0, 0},
	
	.navHeader1 =
	{
		.magicNumber = -0x1303,
		.numPoints = 608,
		.posY_firstNode = 0,
		.last = LEV_OFFSETOF(navFrame[608]),
		
		// rampPhys
	},
		
	// generated from printf data in battle_runtime.c
	.navFrame =
	{
		#include "navData2.h"
	},
		
	.map =
	{
		// if a pointer is not patched by LevelPatcher,
		// add the pointer to the map like this:
		
		// 3 pointers
		(3)<<2,
		
		LEV_OFFSETOF(spawnType1Pointers[2]),
		LEV_OFFSETOF(pvs[0].visLeafSrc),
		LEV_OFFSETOF(pvs[0].visFaceSrc),
	},
};
